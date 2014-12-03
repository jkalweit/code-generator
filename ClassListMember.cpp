#include "ClassListMember.h"

#include <QMetaProperty>
#include <QDebug>

ClassListMember::ClassListMember(QObject *parent, quint32 id, QString name, QString namePlural, QString className, bool generateProperty, bool generateMember, bool generateAdd, bool generateGet, bool generateRemove, bool generateQList) :
    QObject(parent), m_id(id), m_name(name), m_namePlural(namePlural), m_className(className), m_generateProperty(generateProperty), m_generateMember(generateMember), m_generateAdd(generateAdd), m_generateGet(generateGet), m_generateRemove(generateRemove), m_generateQList(generateQList)
{
}

QString ClassListMember::type() {
    return "QQmlListProperty<" + m_className + ">";
}

QString ClassListMember::memberName() {
    return "m_" + m_namePlural;
}

QString ClassListMember::capitalName() {
    return m_name.left(1).toUpper() + m_name.right(m_name.length() - 1);
}

QString ClassListMember::notifyName() {
    return m_namePlural + "Changed";
}

QString ClassListMember::currIdName() {
    return "m_" + m_name + "CurrId";
}


QString ClassListMember::getMemberDeclaration() {
    if(!m_generateMember) {
        return "";
    }

    QString result = "";
    result += "    QList<" + m_className + "*> " + memberName() + ";\n";
    result += "    quint32 " + currIdName() + ";\n";

    return result;
}

QString ClassListMember::getPropertyDeclaration() {
    if(!m_generateProperty) {
        return "";
    }

    return "    Q_PROPERTY(" + type() + " " + m_namePlural + " READ " + m_namePlural + " NOTIFY " + m_namePlural + "Changed)\n";
}

QString ClassListMember::getNotifyDeclaration() {
    if(!m_generateProperty) {
        return "";
    }

    return "    void " + notifyName() + "(" + type() + ");\n";
}

QString ClassListMember::getAccessorsDeclaration() {
    QString result = "";

    result += "    " + type() + " " + m_namePlural + "();\n";

    if(m_generateQList) {
        result += "    QList<" + m_className + "*> " + m_namePlural + "List();\n";
    }

    if(m_generateAdd) {
        result += "    Q_INVOKABLE " + m_className + "* add" + capitalName() + "();\n";
        result += "    void add" + capitalName() + "(" + m_className + " *value);\n";
    }
    if(m_generateGet) {
        result += "    Q_INVOKABLE " + m_className + "* get" + capitalName() + "(quint32 id);\n";
    }
    if(m_generateRemove) {
        result += "    Q_INVOKABLE void remove" + capitalName() + "(quint32 id);\n";
    }

    return result;
}

QString ClassListMember::getAccessorsSource(QString memberOf) {
    QString result = "";

    result += type() + " " + memberOf + "::" + m_namePlural + "() {\n";
    result += "    return " + type() + "(this, " + memberName() + ");\n";
    result += "}\n";
    result += "\n";

    if(m_generateQList) {
        result += "QList<" + m_className + "*> " + memberOf + "::" + m_namePlural + "List() {\n";
        result += "    return " + memberName() + ";\n";
        result += "}\n";
        result += "\n";
    }

    if(m_generateAdd) {
        result += m_className + "* " + memberOf + "::add" + capitalName() + "() {\n";
        result += "    // TODO: Implement Add\n";
        result += "    " + m_className + " *obj = new " + m_className + "(this, ++" + currIdName() + ");\n";
        result += "    add" + capitalName() + "(obj);\n";
        result += "    return obj;\n";
        result += "}\n";
        result += "\n";
        result += "void " + memberOf + "::add" + capitalName() + "(" + m_className + " *value) {\n";
        result += "    if(value->id() > " + currIdName() + ") " + currIdName() + " = value->id();\n";
        result += "    " + memberName() + ".append(value);\n";
        result += "    " + notifyName() + "(" + m_namePlural + "());\n";
        result += "}\n";
        result += "\n";
    }
    if(m_generateGet) {
        result += m_className + "* " + memberOf + "::get" + capitalName() + "(quint32 id) {\n";
        result += "    for(" + m_className + " *value : " + memberName() + ") {\n";
        result += "        if(value->property(\"id\").toUInt() == id) {\n";
        result += "            return value;\n";
        result += "        }\n";
        result += "    }\n";
        result += "    return nullptr;\n";
        result += "}\n";
        result += "\n";
    }

    if(m_generateRemove) {
        result += "void " + memberOf + "::remove" + capitalName() + "(quint32 id) {\n";
        result += "    for(int i = 0; i < " + memberName() + ".length(); i++) {\n";
        result += "        if(" + memberName() + "[i]->property(\"id\").toUInt() == id) {\n";
        result += "            " + m_className + " *item = " + memberName() + "[i];\n";
        result += "            " + memberName() + ".removeAt(i);\n";
        result += "            " + notifyName() + "(" + m_namePlural + "());\n";
        result += "             return;\n";
        result += "        }\n";
        result += "    }\n";
        result += "}\n";
        result += "\n";
    }

    return result;
}


QStringList ClassListMember::serialize() {
    QStringList vals;
    vals << "ClassListMember"
        << m_name << m_namePlural << m_className
        << QString::number(m_generateProperty)
        << QString::number(m_generateMember)
        << QString::number(m_generateAdd)
        << QString::number(m_generateGet)
        << QString::number(m_generateRemove)
        << QString::number(m_generateQList);

    return vals;
}
