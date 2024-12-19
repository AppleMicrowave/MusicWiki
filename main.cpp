#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "dbmanager.h"
#include "itemmanager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreationFailed,
    //     &app,
    //     []() { QCoreApplication::exit(-1); },
    //     Qt::QueuedConnection);

    // Путь к файлу базы данных
    const QString dbPath = "instruments.db";

    // Создаем объект DBManager
    DBManager dbManager(dbPath);

    // // Добавление записей
    // if (dbManager.addItem("Смычковые", "Скрипка", "Yamaha Violin", 1500.0, "Качественная скрипка для начинающих", "Yamaha", "path/to/image1.png")) {
    //     qDebug() << "Запись добавлена успешно.";
    // }

    // if (dbManager.addItem("Щипковые", "Акустическая гитара", "Fender Acoustic", 2000.0, "Популярная гитара", "Fender", "path/to/image2.png")) {
    //     qDebug() << "Запись добавлена успешно.";
    // }

    // Чтение всех записей
    // Чтение всех записей
    QList<ItemManager> items = dbManager.getAllItems();
    qDebug() << "Список всех записей в базе данных:";
    for (const auto& item : items) {
        qDebug() << "Тип:" << item.getType()
            << ", Разновидность:" << item.getKind()
            << ", Название:" << item.getName()
            << ", Цена:" << item.getPrice()
            << ", Описание:" << item.getDescription()
            << ", Производители:" << item.getManufacturers().join(", ")
            << ", Путь к изображению:" << item.getImagePath();
    }


    // // Удаление записи по имени
    // if (dbManager.deleteItem("Yamaha Violin")) {
    //     qDebug() << "Запись удалена успешно.";
    // }

    // // Чтение всех записей после удаления
    // items = dbManager.getAllItems();
    // qDebug() << "Список записей после удаления:";
    // for (const auto& item : items) {
    //     qDebug() << item;
    // }

    engine.loadFromModule("MusicWiki", "Main");

    return app.exec();
}
