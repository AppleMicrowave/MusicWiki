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
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    // Путь к файлу базы данных
    const QString dbPath = "instruments.db";

    // Создаем объект DBManager
    DBManager dbManager(dbPath);

    engine.rootContext()->setContextProperty("dbManager", &dbManager);

    engine.loadFromModule("MusicWiki", "Main");

    return app.exec();
}
