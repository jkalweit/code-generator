#ifndef CLASSDEFINITION_H
#define CLASSDEFINITION_H

#include <QObject>
#include <QQmlListProperty>
#include "ClassMember.h"
#include "ClassListMember.h"

class ClassDefinition : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name MEMBER m_name NOTIFY nameChanged)
    Q_PROPERTY(QString baseClassName MEMBER m_baseClassName NOTIFY baseClassNameChanged)
    Q_PROPERTY(QString logPropertyName MEMBER m_logPropertyName NOTIFY logPropertyNameChanged)
    Q_PROPERTY(QQmlListProperty<ClassMember> classMembers READ classMembers NOTIFY classMembersChanged)
    Q_PROPERTY(QQmlListProperty<ClassListMember> classListMembers READ classListMembers NOTIFY classListMembersChanged)
public:
    explicit ClassDefinition(QObject *parent = 0, QString name = "", QString baseClassName = "SimpleSerializable", QString logPropertyName = "logPropertyChanged");

    void setName(QString name);

    QQmlListProperty<ClassMember> classMembers();
    Q_INVOKABLE ClassMember* newClassMember();

    QQmlListProperty<ClassListMember> classListMembers();
    Q_INVOKABLE ClassListMember* newClassListMember();

    Q_INVOKABLE QString generateHeader();
    Q_INVOKABLE QString generateSource();

signals:
    void nameChanged(QString);
    void baseClassNameChanged(QString);
    void logPropertyNameChanged(QString);
    void classMembersChanged(QQmlListProperty<ClassMember>);
    void classListMembersChanged(QQmlListProperty<ClassListMember>);

public slots:

private:
    QString m_name;
    QString m_baseClassName;
    QString m_logPropertyName;
    QList<ClassMember*> m_classMembers;
    QList<ClassListMember*> m_classListMembers;

};

#endif // CLASSDEFINITION_H
