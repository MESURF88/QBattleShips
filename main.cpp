#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <DisplayLogic.hpp>
#include <GameBoardTest.hpp>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    //qmlRegisterType<GameBoardTest>("gbt", 1, 0, "GameBoardTest");

    QQmlApplicationEngine engine;
    DisplayLogic dspl;
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("dspl", &dspl);

    qRegisterMetaType<GameBoardTest*>("GameBoardTest");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
