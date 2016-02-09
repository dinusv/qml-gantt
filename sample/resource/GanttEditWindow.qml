/****************************************************************************
**
** Copyright (C) 2015-2016 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of QML Gantt library.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

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
        color: "#ddd"
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
                textColor: "#333"
                selectionColor: "#eee"
                selectedTextColor: "#333"
                backgroundColor: "#bbb"
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
                textColor: "#333"
                selectionColor: "#eee"
                selectedTextColor: "#333"
                backgroundColor: "#bbb"
            }
        }

        Rectangle{
            id: updateButton
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 16
            color: createButtonArea.containsMouse ? "#334499" : "#334466"
            width: 100
            height: 30
            Text{
                anchors.centerIn: parent
                text: "Update"
                color: "#fff"
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
            color: cancelButtonArea.containsMouse ? "#b14433" : "#884433"
            width: 100
            height: 30
            Text{
                anchors.centerIn: parent
                text: "Cancel"
                color: "#fff"
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
