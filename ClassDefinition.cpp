#include "ClassDefinition.h"
#include <QDebug>

ClassDefinition::ClassDefinition(QObject *parent, QString name, QString baseClassName, QString logPropertyName) :
    QObject(parent), m_name(name), m_baseClassName(baseClassName), m_logPropertyName(logPropertyName)
{
}


QQmlListProperty<ClassMember> ClassDefinition::classMembers() {
    return QQmlListProperty<ClassMember>(this, m_classMembers);
}

ClassMember* ClassDefinition::newClassMember() {
    ClassMember *member = new ClassMember(this, "field", "QString");
    m_classMembers.append(member);
    classMembersChanged(classMembers());
    return member;
}

QString ClassDefinition::generateHeader() {
    QString result = "";
    result += "#ifndef " + m_name.toUpper() + "_H\n";
    result += "#define " + m_name.toUpper() + "_H\n";
    result += "\n";
    result += "#include <QObject>\n";
    result += "#include <QQmlListProperty>\n";
    if(m_baseClassName != "QObject") {
        result += "#include \"" + m_baseClassName + ".h\"\n";
    }
    result += "\n";
    result += "class " + m_name;
    if(m_baseClassName != "") {
        result += " : public " + m_baseClassName;
    }
    result += "\n";
    result += "{\n";
    result += "\n";
    result += "    Q_OBJECT\n";
    for(ClassMember *member : m_classMembers) {
        result += member->getPropertyDeclaration();
    }
    result += "public:\n";
    result += "    explicit " + m_name + "(QObject *parent = 0";
    for(ClassMember *member : m_classMembers) {
        if(member->property("generateMember").toBool()) {
            result += ", " + member->type() + " " + member->name() + " = ";
            if(member->type() == "QString") {
                result += "\"\"";
            } else if(member->type() == "bool") {
                result += "false";
            } else {
                result += "0";
            }
        }
    }
    result += ");\n";
    result += "\n";

    for(ClassMember *member : m_classMembers) {
        result += member->getReadMethodDeclaration();
    }

    result += "\n";

    for(ClassMember *member : m_classMembers) {
        result += member->getWriteMethodDeclaration();
    }
    result += "\n";
    result += "signals:\n";
    for(ClassMember *member : m_classMembers) {
        result += member->getNotifyDeclaration();
    }
    result += "\n";

    result += "public slots:\n";
    result += "\n";
    result += "private:\n";
    for(ClassMember *member : m_classMembers) {
        result += member->getMemberDeclaration();
    }

    result += "\n";
    result += "};\n";
    result += "\n";
    result += "#endif // " + m_name.toUpper() + "_H\n";
    return result;
}


QString ClassDefinition::generateSource() {
    QString result = "";
    result += "#include \"" + m_name + ".h\"\n";
    result += "\n";
    result += "#include <QMetaProperty>\n";
    result += "#include <QDebug>\n";
    result += "\n";
    result += m_name + "::" + m_name + "(QObject *parent";
    for(ClassMember *member : m_classMembers) {
        if(member->property("generateMember").toBool()) {
            result += ", " + member->type() + " " + member->name();
        }
    }
    result += ") : \n";
    result += "    " + m_baseClassName + "(parent)";
    for(ClassMember *member : m_classMembers) {
        if(member->property("generateMember").toBool()) {
            result += ", " + member->memberName() + "(" + member->name() + ")";
        }
    }
    result += "\n";
    result += "{\n";
    result += "}\n";
    result += "\n";
    for(ClassMember *member : m_classMembers) {
        result += member->getReadMethod(m_name);
    }
    result += "\n";
    for(ClassMember *member : m_classMembers) {
        result += member->getWriteMethod(m_name, m_logPropertyName);
    }
    result += "\n";
    return result;
}
