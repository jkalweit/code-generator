#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ClassDefinition.h"
#include "ClassMember.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<ClassDefinition>("FreePos", 1, 0, "ClassDefinition");
    qmlRegisterType<ClassMember>("FreePos", 1, 0, "ClassMember");

    ClassDefinition definition(0, "MyClass");

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("definition", (QObject*)&definition);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
