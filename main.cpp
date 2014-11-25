#include <QApplication>
#include <QtQml>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "ClassDefinition.h"
#include "ClassMember.h"
#include "ClassListMember.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<ClassDefinition>("FreePos", 1, 0, "ClassDefinition");
    qmlRegisterType<ClassMember>("FreePos", 1, 0, "ClassMember");
    qmlRegisterType<ClassListMember>("FreePos", 1, 0, "ClassListMember");


    QApplication app(argc, argv);

    ClassDefinition definition(&app, "MyClass");

    definition.addClassMember(new ClassMember(&definition, "id", "quint32", true, true, true, false));
    definition.addClassMember(new ClassMember(&definition, "name", "QString", true, true, true, true));

    definition.addClassListMember(new ClassListMember(&definition, 0, "item", "items", "Type", true, true, true, true, true, true));



    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("definition", (QObject*)&definition);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
