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
                    text: "Member"
                    checked: modelData.generateMember
                    onCheckedChanged: modelData.generateMember = this.checked
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

        Repeater {
            model: definition.classListMembers
            Row {
                TextField {
                    id: ckassNameText
                    text: modelData.className
                    onFocusChanged: if(this.focus) this.selectAll();
                    onTextChanged: modelData.className = this.text
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
                    text: "Member"
                    checked: modelData.generateMember
                    onCheckedChanged: modelData.generateMember = this.checked
                }
                CheckBox {
                    text: "Add"
                    checked: modelData.generateAdd
                    onCheckedChanged: modelData.generateAdd = this.checked
                }
                CheckBox {
                    text: "Get"
                    checked: modelData.generateGet
                    onCheckedChanged: modelData.generateGet = this.checked
                }
                CheckBox {
                    text: "Remove"
                    checked: modelData.generateRemove
                    onCheckedChanged: modelData.generateRemove = this.checked
                }
                CheckBox {
                    text: "QList"
                    checked: modelData.generateQList
                    onCheckedChanged: modelData.generateQList = this.checked
                }
            }
        }

        Button {
            text: "Add List Member"
            onClicked: definition.newClassListMember()
        }
        Button {
            text: "Generate"
            onClicked: {
                headerText.text = definition.generateHeader();
                sourceText.text = definition.generateSource();
            }
        }
    }



    TextArea {
        id: headerText
        anchors.top: mainColumn.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.rightMargin: parent.width / 2
        onFocusChanged: if(this.focus) this.selectAll()
    }

    TextArea {
        id: sourceText
        anchors.top: mainColumn.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: parent.width / 2
        anchors.right: parent.right
        onFocusChanged: if(this.focus) this.selectAll()
    }
}
