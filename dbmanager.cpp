#include "DBManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

DBManager::DBManager(const QString& dbPath) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbPath);

    if (!m_db.open()) {
        qDebug() << "Не удалось открыть базу данных:" << m_db.lastError().text();
    } else {
        qDebug() << "База данных успешно открыта.";
        initializeDatabase();
    }
}

DBManager::~DBManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DBManager::addItem(const QString& type, const QString& kind, const QString& name, double price,
                        const QString& description, const QString& manufacturers, const QString& imagePath) {
    QSqlQuery query;
    query.prepare("INSERT INTO items (type, kind, name, price, description, manufacturers, imagePath) "
                  "VALUES (:type, :kind, :name, :price, :description, :manufacturers, :imagePath)");
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
