#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "PenController.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    app.setApplicationName(QStringLiteral("Sexy S-Pen"));
    app.setOrganizationName(QStringLiteral("Sexy S-Pen Community"));
    app.setApplicationVersion(QStringLiteral("0.3.0"));

    PenController controller;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("penController"), &controller);
    engine.loadFromModule("SexySPen", "Main");
    if (engine.rootObjects().isEmpty()) return 1;
    return app.exec();
}
