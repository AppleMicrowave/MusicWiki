#include "DBManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DBManager::DBManager(const QString& dbPath, QObject* parent)
    : QObject(parent) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "Не удалось открыть базу данных:" << m_db.lastError().text();
    } else {
        qDebug() << "База данных успешно открыта.";
        initializeDatabase();
    }

    // Устанавливаем данные в модель
    m_itemModel.setItems(getAllItems());
}

DBManager::~DBManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

ItemModel* DBManager::itemModel() {
    m_itemModel.setItems(getAllItems());
    return &m_itemModel;
}

bool DBManager::addItem(const QString& category, const QString& type, const QString& kind, const QString& name, double price,
                        const QString& description, const QString& manufacturers, const QString& imagePath) {
    QSqlQuery query;
    query.prepare("INSERT INTO items (category, type, kind, name, price, description, manufacturers, imagePath) "
                  "VALUES (:category, :type, :kind, :name, :price, :description, :manufacturers, :imagePath)");
    query.bindValue("category", category);
    query.bindValue(":type", type);
    query.bindValue(":kind", kind);
    query.bindValue(":name", name);
    query.bindValue(":price", price);
    query.bindValue(":description", description);
    query.bindValue(":manufacturers", manufacturers);
    query.bindValue(":imagePath", imagePath);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления записи:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DBManager::deleteItem(const QString& name) {
    QSqlQuery query;
    query.prepare("DELETE FROM items WHERE name = :name");
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Ошибка удаления записи:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DBManager::addItemToFavorites(const QString& itemName) {
    QSqlQuery query;

    qDebug() << "Попытка добавить в избранное:" << itemName;

    // Проверка, есть ли уже этот элемент в избранных
    query.prepare("SELECT COUNT(*) FROM favorites WHERE name = :name");
    query.addBindValue(itemName);

    qDebug() << "Запрос на проверку существования: " << query.executedQuery();
    if (!query.exec()) {
        qDebug() << "Ошибка проверки существования элемента в избранном:" << query.lastError().text();
        return false;
    }

    query.next();
    if (query.value(0).toInt() > 0) {
        // Если элемент уже есть в избранном, не добавляем
        qDebug() << "Этот элемент уже в избранном.";
        return false;
    }

    // Добавление элемента в избранное
    query.prepare("INSERT INTO favorites (name) VALUES (:name)");
    query.bindValue(":name", itemName);

    if (!query.exec()) {
        qDebug() << "Ошибка добавления элемента в избранное:" << query.lastError().text();
        return false;
    }

    qDebug() << "Элемент успешно добавлен в избранное.";
    return true;
}

bool DBManager::removeItemFromFavorites(const QString& itemName) {
    QSqlQuery query;

    // // Логирование попытки удаления
    // qDebug() << "Попытка удалить элемент из избранного:" << itemName;

    // Подготовка запроса на удаление элемента
    query.prepare("DELETE FROM favorites WHERE name = ?");
    query.addBindValue(itemName);  // Привязываем имя элемента

    // // Логируем запрос
    // qDebug() << "Запрос на удаление элемента:" << query.executedQuery();

    if (!query.exec()) {
        qDebug() << "Ошибка удаления элемента из избранного:" << query.lastError().text();
        return false;
    }

    qDebug() << "Элемент успешно удален из избранного.";
    return true;
}

void DBManager::filterItemsByFavorites(bool onlyFavorites) {
    QSqlQuery query;

    if (onlyFavorites) {
        query.prepare("SELECT * FROM items WHERE name IN (SELECT name FROM favorites)");
    } else {
        query.prepare("SELECT * FROM items");
    }

    if (!query.exec()) {
        qDebug() << "Ошибка при фильтрации элементов:" << query.lastError().text();
        return;
    }

    QVector<ItemManager> items;
    while (query.next()) {
        ItemManager item(
            query.value("category").toString(),
            query.value("type").toString(),
            query.value("kind").toString(),
            query.value("name").toString(),
            query.value("price").toDouble(),
            query.value("description").toString(),
            query.value("manufacturers").toString().split(","),
            query.value("imagePath").toString()
            );
        items.append(item);
    }

    m_itemModel.setItems(items);
}


QList<ItemManager> DBManager::getAllItems() {
    QList<ItemManager> items;
    QSqlQuery query("SELECT category, type, kind, name, price, description, manufacturers, imagePath FROM items");

    while (query.next()) {
        QString category = query.value(0).toString();
        QString type = query.value(1).toString();
        QString kind = query.value(2).toString();
        QString name = query.value(3).toString();
        double price = query.value(4).toDouble();
        QString description = query.value(5).toString();
        QList<QString> manufacturers = query.value(6).toString().split(","); // Разделяем строку в список
        QString imagePath = query.value(7).toString();

        items.append(ItemManager(category, type, kind, name, price, description, manufacturers, imagePath));
    }
    return items;
}


void DBManager::initializeDatabase() {
    QSqlQuery query;
    QString createTableQuery =
        "CREATE TABLE IF NOT EXISTS items ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "type TEXT,"
        "kind TEXT,"
        "name TEXT UNIQUE,"
        "price REAL,"
        "description TEXT,"
        "manufacturers TEXT,"
        "imagePath TEXT"
        ");";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Ошибка создания таблицы:" << query.lastError().text();
    }
}
