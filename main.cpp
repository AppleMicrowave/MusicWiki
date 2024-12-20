#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QQmlContext>
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
    // QList<ItemManager> items = dbManager.getAllItems();
    // qDebug() << "Список всех записей в базе данных:";
    // for (const auto& item : items) {
    //     qDebug() << item.getCategory();
    // }


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


    engine.rootContext()->setContextProperty("dbManager", &dbManager);
    engine.rootContext()->setContextProperty("itemModel", dbManager.itemModel());

    engine.loadFromModule("MusicWiki", "Main");

    return app.exec();
}
