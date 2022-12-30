#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <gmap.h>
#include <QQmlContext>
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext *context1 = engine.rootContext();
    gmap locator;

    context1->setContextProperty("gmap",&locator);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
