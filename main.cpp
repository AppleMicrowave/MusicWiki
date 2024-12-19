#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTreeView>

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
    engine.loadFromModule("MusicWiki", "Main");

    return app.exec();
}
