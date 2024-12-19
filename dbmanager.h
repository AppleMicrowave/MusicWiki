#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QList>
#include <QVariant>

#include "itemmanager.h"

class DBManager {
public:
    // Конструктор
    explicit DBManager(const QString& dbPath);

    // Деструктор
    ~DBManager();

    // Метод для добавления записи
    bool addItem(const QString& type, const QString& kind, const QString& name, double price,
                 const QString& description, const QString& manufacturers, const QString& imagePath);

    // Метод для удаления записи по имени
    bool deleteItem(const QString& name);

    // Метод для чтения всех записей
    QList<ItemManager> getAllItems();

private:
    QSqlDatabase m_db;

    // Метод для инициализации таблицы, если она не существует
    void initializeDatabase();
};

#endif // DBMANAGER_H
