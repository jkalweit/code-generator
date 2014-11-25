#include "ClassListMember.h"

#include <QMetaProperty>
#include <QDebug>

ClassListMember::ClassListMember(QObject *parent, quint32 id, QString name, QString className, bool generateProperty, bool generateMember, bool generateAdd, bool generateGet, bool generateRemove, bool generateQList) :
    QObject(parent), m_id(id), m_name(name), m_className(className), m_generateProperty(generateProperty), m_generateMember(generateMember), m_generateAdd(generateAdd), m_generateGet(generateGet), m_generateRemove(generateRemove), m_generateQList(generateQList)
{
}

QString ClassListMember::type() {
    return "QQmlListProperty<" + m_className + ">";
}

QString ClassListMember::memberName() {
    return "m_" + m_name;
}

QString ClassListMember::capitalName() {
    return m_name.left(1).toUpper() + m_name.right(m_name.length() - 1);
}

QString ClassListMember::getMemberDeclaration() {
    if(!m_generateMember) {
        return "";
    }

    return "     QList<" + m_className + "*> " + memberName() + ";\n";
}

QString ClassListMember::getPropertyDeclaration() {
    if(!m_generateProperty) {
        return "";
    }

    return "    Q_PROPERTY(" + type() + " " + m_name + " READ " + m_name + " NOTIFY " + m_name + "Changed)\n";
}

QString ClassListMember::getNotifyDeclaration() {
    if(!m_generateProperty) {
        return "";
    }

    return "    void " + m_name + "Changed(" + type() + ");\n";
}

QString ClassListMember::getAccessorsDeclaration() {
    QString result = "";

    result += "     " + type() + " " + m_name + "();\n";

    if(m_generateQList) {
        result += "     QList<" + m_className + "*> " + m_name + "List();\n";
    }

    if(m_generateAdd) {
        result += "     Q_INVOKABLE " + m_className + "* add" + capitalName() + "();\n";
        result += "     void add" + capitalName() + "(" + m_name + " *value);\n";
    }
    if(m_generateGet) {
        result += "     Q_INVOKABLE " + m_className + "* get" + capitalName() + "(quint32 id);\n";
    }
    if(m_generateRemove) {
        result += "     Q_INVOKABLE void remove" + capitalName() + "(quint32 id);\n";
    }

    return result;
}

QString ClassListMember::getAccessorsSource() {
    QString result = "";

//    result += "     " + type() + " " + m_name + "();\n";

//    if(m_generateQList) {
//        result += "     QList<" + m_className + "*> " + m_name + "List();\n";
//    }

//    if(m_generateAdd) {
//        result += "     Q_INVOKABLE " + m_className + "* add" + capitalName() + "();\n";
//        result += "     void add" + capitalName() + "(" + m_name + " *value);\n";
//    }
//    if(m_generateGet) {
//        result += "     Q_INVOKABLE " + m_className + "* get" + capitalName() + "(quint32 id);\n";
//    }
//    if(m_generateRemove) {
//        result += "     Q_INVOKABLE void remove" + capitalName() + "(quint32 id);\n";
//    }

    return result;
}
