import QtQuick 2.3
import QtQuick.Window 2.1
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2
import QtQuick.Dialogs 1.2
import Gantt 1.0

Window{
    id: root
    title: "Edit Gantt Item"
    modality: Qt.ApplicationModal

    visible: false
    minimumWidth: 300
    minimumHeight: 200
    width: 400
    height: 200

    property variant ganttItem : null

    signal update(string color, string data)
    signal canceled()

    Rectangle{
        color: "#333"
        anchors.fill: parent
        focus: true

        Keys.onEscapePressed: {
            labelInput.text = ""
            root.close()
            root.canceled()
        }

        TextArea{
            id: colorInput
            anchors.top: parent.top
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            height: 25
            clip: true
            text: root.ganttItem ? root.ganttItem.color : ""
            selectByMouse: true
            font.pixelSize: 12
            font.family: "Courier New"
            style: TextAreaStyle {
                textColor: "#ccc"
                selectionColor: "#eee"
                selectedTextColor: "#333"
                backgroundColor: "#3c3c3c"
            }
        }

        TextArea{
            id: labelInput
            anchors.top: parent.top
            anchors.topMargin: 40
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            height: parent.height - 100
            clip: true
            text: root.ganttItem ? root.ganttItem.label : ""
            selectByMouse: true
            font.pixelSize: 12
            font.family: "Courier New"
            style: TextAreaStyle {
                textColor: "#ccc"
                selectionColor: "#eee"
                selectedTextColor: "#333"
                backgroundColor: "#3c3c3c"
            }
        }

        Rectangle{
            id: updateButton
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16
            color: createButtonArea.containsMouse ? "#222240" : "#222230"
            width: 100
            height: 30
            Text{
                anchors.centerIn: parent
                text: "Update"
                color: "#ccc"
                font.pixelSize: 12
                font.family: "Arial, Helvetica, sans-serif"
            }
            MouseArea{
                id: createButtonArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    colorInput.select(0, 0)
                    labelInput.select(0, 0)
                    if ( ganttItem ){
                        ganttItem.label = labelInput.text
                        ganttItem.color = colorInput.text
                    }
                    root.close()
                    root.update(colorInput.text, labelInput.text)
                    root.ganttItem = null
                }
            }
        }

        Rectangle{
            id: cancelButton
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16
            color: cancelButtonArea.containsMouse ? "#402222" : "#302222"
            width: 100
            height: 30
            Text{
                anchors.centerIn: parent
                text: "Cancel"
                color: "#ccc"
                font.pixelSize: 12
                font.family: "Arial, Helvetica, sans-serif"
            }
            MouseArea{
                id: cancelButtonArea
                anchors.fill: parent
                hoverEnabled: true
                onClicked: {
                    ganttItem = null
                    root.close()
                    root.canceled()
                }
            }
        }
    }
}