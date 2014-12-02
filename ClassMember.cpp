#include "ClassMember.h"

ClassMember::ClassMember(QObject *parent, QString name, QString type, bool generateMember, bool generateProperty, bool generateRead, bool generateWrite) :
    QObject(parent), m_name(name), m_type(type), m_generateMember(generateMember), m_generateProperty(generateProperty), m_generateRead(generateRead), m_generateWrite(generateWrite)
{
}

QString ClassMember::name() {
    return m_name;
}

QString ClassMember::type() {
    return m_type;
}

QString ClassMember::memberName() {
    return "m_" + m_name;
}

QString ClassMember::capitalName() {
    return m_name.left(1).toUpper() + m_name.right(m_name.length() - 1);
}

QString ClassMember::getMemberDeclaration() {
    if(!m_generateMember) {
        return "";
    }

    return "    " + m_type + " " + memberName() + ";\n";
}

QString ClassMember::getPropertyDeclaration() {
    if(!m_generateProperty) {
        return "";
    }

    QString result = "    Q_PROPERTY(" + m_type + " " + m_name;
    if(m_generateMember) {
        result += " MEMBER " + memberName();
    }
    if(m_generateRead) {
        result += " READ " + m_name;
    }
    if(m_generateWrite) {
        result += " WRITE set" + capitalName();
    }

    result += " NOTIFY " + m_name + "Changed)\n";

    return result;
}

QString ClassMember::getNotifyDeclaration() {
    if(!m_generateProperty) {
        return "";
    }

    return "    void " + m_name + "Changed(" + m_type + ");\n";
}

QString ClassMember::getReadMethodDeclaration() {
    if(!m_generateRead) {
        return "";
    }

    return "    " + m_type + " " + m_name + "();\n";
}

QString ClassMember::getWriteMethodDeclaration() {
    if(!m_generateWrite) {
        return "";
    }

    return "    void set" + capitalName() + "(" + m_type + " value);\n";
}


QString ClassMember::getReadMethod(QString className) {
    if(!m_generateRead) {
        return "";
    }

    QString result = "";
    result += m_type + " " + className + "::" + m_name + "() {\n";
    if(m_generateMember) {
        result += "    return " + memberName() + ";\n";
    } else {
        result += "    // TODO: Implement Read\n";
    }
    result += "}\n";
    result += "\n";
    return result;
}



QString ClassMember::getWriteMethod(QString className, QString logPropertyName) {
    if(!m_generateWrite) {
        return "";
    }

    QString result = "";

    result += "void " + className + "::set" + capitalName() + "(" +     m_type + " value) {\n";
    if(m_generateMember) {
        result += "    if(" + memberName() + " != value) {\n";
        result += "        " + memberName() + " = value;\n";
        if(logPropertyName != "") {
            result += "        " + logPropertyName + "(" + memberName() + ", \"" + m_name + "\");\n";
        }
        result += "        " + m_name + "Changed(" + memberName() + ");\n";
        result += "    }\n";
    } else {
        result += "    // TODO: Implement Write\n";
    }

    result += "}\n";
    result += "\n";

    return result;
}

QStringList ClassMember::serialize() {
    QStringList vals;
    vals << "ClassMember" << m_name << m_type
        << QString::number(m_generateMember)
        << QString::number(m_generateProperty)
        << QString::number(m_generateRead)
        << QString::number(m_generateWrite);
    return vals;
}
