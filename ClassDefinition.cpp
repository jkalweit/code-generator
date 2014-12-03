#include "ClassDefinition.h"
#include <QDebug>
#include <QDir>
#include <QFile>

ClassDefinition::ClassDefinition(QObject *parent, QString name, QString baseClassName, QString logPropertyName) :
    QObject(parent), m_name(name), m_baseClassName(baseClassName), m_logPropertyName(logPropertyName)
{
}


QQmlListProperty<ClassMember> ClassDefinition::classMembers() {
    return QQmlListProperty<ClassMember>(this, m_classMembers);
}

ClassMember* ClassDefinition::newClassMember() {
    ClassMember *member = new ClassMember(this, "field", "QString", true, true, true, true);
    addClassMember(member);
    return member;
}

void ClassDefinition::addClassMember(ClassMember *value) {
    m_classMembers.append(value);
    classMembersChanged(classMembers());
}





QQmlListProperty<ClassListMember> ClassDefinition::classListMembers() {
    return QQmlListProperty<ClassListMember>(this, m_classListMembers);
}

ClassListMember* ClassDefinition::newClassListMember() {
    ClassListMember *member = new ClassListMember(this, 0, "item", "items", "itemType", true, true, true, true, true, true);
    addClassListMember(member);
    return member;
}

void ClassDefinition::addClassListMember(ClassListMember *value) {
    m_classListMembers.append(value);
    classListMembersChanged(classListMembers());
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

    QStringList includes;
    for(ClassMember *member : m_classMembers) {
        QString type = member->type();
        if(!(type == "QString" || type == "bool" || type == "quint32" || type == "float")) {

            if(type.right(1) == "*") {
                type = type.left(type.length() - 1);
            }

            if(!includes.contains(type)) {
                result += "#include \"" + type + ".h\"\n";
                includes.append(type);
            }
        }
    }
    for(ClassListMember *member : m_classListMembers) {
        result += "#include \"" + member->property("className").toString() + ".h\"\n";
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
    result += "\n";
    for(ClassListMember *member : m_classListMembers) {
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
            } else if(member->type() == "quint32" || member->type() == "float") {
                result += "0";
            } else {
                result += "nullptr";
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
    result += "\n";

    for(ClassListMember *member : m_classListMembers) {
        result += member->getAccessorsDeclaration();
        result += "\n";
    }


    result += "\n";
    result += "signals:\n";
    for(ClassMember *member : m_classMembers) {
        result += member->getNotifyDeclaration();
    }    
    result += "\n";
    for(ClassListMember *member : m_classListMembers) {
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
    for(ClassListMember *member : m_classListMembers) {
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
    for(ClassListMember *member : m_classListMembers) {
        if(member->property("generateMember").toBool()) {
            result += ", " + member->currIdName() + "(0)";
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
    for(ClassListMember *member : m_classListMembers) {
        result += member->getAccessorsSource(m_name);
    }
    result += "\n";
    return result;
}

void ClassDefinition::readFile() {

    m_classMembers.clear();
    classMembersChanged(classMembers());

    m_classListMembers.clear();
    classListMembersChanged(classListMembers());

    QFile file("./data/" + m_name + ".txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);


    while(!in.atEnd()) {
        QString line = in.readLine();
        int delimit = line.indexOf(":");
        QString command = line.mid(0, delimit);
        QString payload = line.mid(delimit+1, line.length() - delimit);
        QStringList split = deserializeList(payload);

        qDebug() << command << ": " << payload;

        if(command == "ClassDefinition") {
            m_name = split[0];
            m_baseClassName = split[1];
            m_logPropertyName = split[2];
        } else if(command == "ClassMember") {
            addClassMember(new ClassMember(this, split[0], split[1], split[2].toUInt(), split[3].toUInt(), split[4].toUInt(), split[5].toUInt()));
        } else if(command == "ClassListMember") {
            addClassListMember(new ClassListMember(this, 0, split[0], split[1], split[2], split[3].toUInt(), split[4].toUInt(), split[5].toUInt(), split[6].toUInt(), split[7].toUInt(), split[8].toUInt()));
        } else {
            qDebug() << "   UNKNOWN COMMAND: " << command << payload;
        }
    }
}

void ClassDefinition::writeFile() {

    QDir().mkdir("data");

    QFile file("./data/" + m_name + ".txt");

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    QStringList vals;
    vals << "ClassDefinition" << m_name << m_baseClassName << m_logPropertyName;
    out << serializeList(vals) << endl;

    for(ClassMember *member : m_classMembers) {
        out << serializeList(member->serialize()) << endl;
    }

    for(ClassListMember *member : m_classListMembers) {
        out << serializeList(member->serialize()) << endl;
    }

    file.close();

}

QString ClassDefinition::serializeList(QStringList vals) {
    QString result = "";
    for(QString val : vals) {
        if(result != "")
            result += ":";
        result += escapeString(val);
    }
    return result;
}

QStringList ClassDefinition::deserializeList(QString vals) {
    QStringList input = vals.split(":");
    QStringList result;
    for(QString val : input) {
        result << unEscapeString(val);
    }
    return result;
}

QString ClassDefinition::escapeString(QString val) {
    return val.replace("\n", "\\n").replace(":", "\\!");
}

QString ClassDefinition::unEscapeString(QString val) {
    return val.replace("\\n", "\n").replace("\\!", ":");
}

