import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 640
    height: 780
    title: qsTr("Code Generator")

    Column {
        id: mainColumn
        spacing: 5
        width: 200
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 10

        Row {
            TextField {
                text: definition.name
                onFocusChanged: if(this.focus) this.selectAll()
                onTextChanged: definition.name = this.text
            }
            TextField {
                text: definition.baseClassName
                onFocusChanged: if(this.focus) this.selectAll()
                onTextChanged: definition.baseClassName = this.text
            }
            TextField {
                text: definition.logPropertyName
                onFocusChanged: if(this.focus) this.selectAll()
                onTextChanged: definition.logPropertyName = this.text
            }
//            TextField {
//                id: logNameText
//                text: "logFixedCostsPropertyChanged"
//                onFocusChanged: if(this.focus) this.selectAll();
//            }
        }

        Repeater {
            model: definition.classMembers
            Row {
                ComboBox {
                    id: typeSelect
                    model: ["QString", "quint32", "float", "bool"]
//                    onCurrentTextChanged: {
//                        if(this.status === Component.Ready) {
//                            console.log(this.currentText);
//                            modelData.type = this.currentText
//                            console.log(modelData.type);
//                        }
//                    }
                    onActivated: {
                        modelData.type = this.textAt(index);
                    }
                    Component.onCompleted: {
                        if(modelData.type === "QString") {
                            this.currentIndex = 0;
                        } else if(modelData.type === "quint32") {
                            this.currentIndex = 1;
                        } else if(modelData.type === "float") {
                            this.currentIndex = 2;
                        } else if(modelData.type === "bool") {
                            this.currentIndex = 3;
                        }
                    }
                }
                TextField {
                    id: fieldNameText
                    text: modelData.name
                    onFocusChanged: if(this.focus) this.selectAll();
                    onTextChanged: modelData.name = this.text
                }
                CheckBox {
                    id: propertyOption
                    text: "Property"
                    checked: modelData.generateProperty
                    onCheckedChanged: modelData.generateProperty = this.checked
                }
                CheckBox {
                    id: readOption
                    text: "Read"
                    checked: modelData.generateRead
                    onCheckedChanged: modelData.generateRead = this.checked
                }
                CheckBox {
                    id: writeOption
                    text: "Write"
                    checked: modelData.generateWrite
                    onCheckedChanged: modelData.generateWrite = this.checked
                }
            }
        }

        Button {
            text: "Add Member"
            onClicked: definition.newClassMember()
        }

        Button {
            text: "Generate"
            onClicked: {
//                var qproperty = "";
//                var readMethod = "";
//                var writeMethod = "";

//                var className = classNameText.text;

//                var type = typeSelect.currentText;
//                var name = fieldNameText.text;
//                var capitalName = name.toString().substring(0, 1).toUpperCase() + name.toString().substring(1, name.length);
//                var memberName = "m_" + name;

//                qproperty += "Q_PROPERTY(" + type + " " + name + " MEMBER " + memberName;

//                if(readOption.checked) {
//                    qproperty += " READ " + name;

//                    readMethod += type + " " + className + "::" + name + "() {\n";
//                    readMethod += "    return " + memberName + ";\n";
//                    readMethod += "}\n\n";
//                }

//                if(writeOption.checked) {
//                    qproperty += " WRITE set" + capitalName;

//                    writeMethod += "void " + className + "::set" + capitalName + "(" + type + " value) {\n";
//                    writeMethod += "    if(" + memberName + " != value) {\n";
//                    writeMethod += "        " + memberName + " = value;\n";
//                    writeMethod += "        " + logNameText.text + "(" + memberName + ", \"" + name + "\");\n";
//                    writeMethod += "        " + name + "Changed();\n";
//                    writeMethod += "    }\n";
//                    writeMethod += "}\n\n";
//                }

//                qproperty += " NOTIFY " + name + "Changed)\n\n";

//                var result = "";
//                if(propertyOption.checked) {
//                    result += qproperty;
//                }
//                if(readOption.checked) {
//                    result += readMethod;
//                }
//                if(writeOption.checked) {
//                    result += writeMethod;
//                }

//                if(propertyOption.checked) {
//                    result += "void " + name + "Changed(" + type + ");\n\n";
//                }

//                result += type + " " + memberName + ";\n\n";


                resultText.text = definition.generateHeader();
                resultText.text += "\n\n\n";
                resultText.text += definition.generateSource();
                resultText.forceActiveFocus();
                resultText.selectAll();
            }
        }
    }



    TextArea {
        id: resultText
        anchors.top: mainColumn.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }
}
