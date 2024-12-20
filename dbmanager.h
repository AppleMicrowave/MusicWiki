#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QList>
#include <QVariant>
#include "ItemManager.h"
#include "itemmodel.h"

class DBManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(ItemModel* itemModel READ itemModel CONSTANT)

public:
    explicit DBManager(const QString& dbPath, QObject* parent = nullptr);
    ~DBManager();

    bool addItem(const QString& category, const QString& type, const QString& kind, const QString& name, double price,
                 const QString& description, const QString& manufacturers, const QString& imagePath);
    bool deleteItem(const QString& name);
    QList<ItemManager> getAllItems();
    ItemModel* itemModel();
    void clearTable() {
        QSqlQuery query;
        if (!query.exec("DELETE FROM items")) {
            qDebug() << "Ошибка при очистке таблицы:" << query.lastError().text();
        } else {
            qDebug() << "Таблица успешно очищена.";
        }
    }

private:
    QSqlDatabase m_db;
    ItemModel m_itemModel;
    void initializeDatabase();
};

#endif // DBMANAGER_H
