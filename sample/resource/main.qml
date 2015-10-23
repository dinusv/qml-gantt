/****************************************************************************
**
** Copyright (C) 2015 Dinu SV.
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

import QtQuick 2.2
import QtQuick.Controls 1.1
import Gantt 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QML Gantt Sample")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle{
        height: parent.height - 14
        clip: true
        width: 150

        ListView{
            id: ganttNameView

            anchors.fill: parent

            interactive: false
            contentY: ganttView.contentY

            model: ganttModelList
            delegate: Rectangle{
                width: parent.width
                height: 40
                Rectangle{
                    color: "#ccc"
                    width: parent.width
                    height: 38
                    Text{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        text: name
                        font.family: "Arial, Helvetica, open-sans"
                        font.pixelSize: 13
                        color: "#000"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onDoubleClicked: {
                            trackEditBox.visible = true
                            trackEdit.selectAll()
                            trackEdit.forceActiveFocus()
                        }
                    }
                    Rectangle{
                        id: trackEditBox
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.fill: parent
                        anchors.margins: 5
                        visible: false
                        color: "#aaa"
                        border.color: "#6666cc"
                        border.width: 1
                        TextInput{
                            id: trackEdit
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: parent.left
                            anchors.leftMargin: 5
                            width: parent.width - 10
                            text: name
                            color: "#000"
                            font.pixelSize: 13
                            font.bold: false
                            font.family: "Arial, Helvetica, sans-serif"
                            selectByMouse: true
                            selectionColor: "#444499"
                            onActiveFocusChanged: {
                                if ( !activeFocus ){
                                    name = text
                                    trackEditBox.visible = false
                                }
                            }
                            Keys.onReturnPressed: {
                                name = text
                                event.accepted = true
                                trackEditBox.visible = false
                            }
                            Keys.onEnterPressed: {
                                name = text
                                event.accepted = true
                                trackEditBox.visible = false
                            }

                            Keys.onEscapePressed: {
                                text = name
                                event.accepted = true
                                trackEditBox.visible = false
                            }
                            MouseArea{
                                anchors.fill: parent
                                acceptedButtons: Qt.NoButton
                                cursorShape: Qt.IBeamCursor
                            }
                        }
                    }
                }
            }

            MouseArea{
                anchors.fill: parent
                onWheel: {
                    wheel.accepted = true
                    var newContentY = ganttView.contentY -= wheel.angleDelta.y / 6
                    if ( newContentY > ganttView.contentHeight - ganttView.height )
                        ganttView.contentY = ganttView.contentHeight - ganttView.height
                    else if ( newContentY < 0 )
                        ganttView.contentY = 0
                    else
                        ganttView.contentY = newContentY
                }
                onClicked: mouse.accepted = false;
                onPressed: mouse.accepted = false;
                onReleased: mouse.accepted = false
                onDoubleClicked: mouse.accepted = false;
                onPositionChanged: mouse.accepted = false;
                onPressAndHold: mouse.accepted = false;
            }
        }
    }

    Rectangle{
        height: parent.height
        width: parent.width - 152
        x: 152

        ScrollView{
            id: mainScroll
            anchors.fill: parent

            ListView{
                id: ganttView

                height: parent.height
                contentWidth:  ganttModelList.contentWidth
                model: ganttModelList
                delegate: Rectangle{
                    height: 40
                    width: ganttLine.width
                    color: "#fff"

                    Rectangle{
                        height: 38
                        width: ganttLine.width
                        color: "#ccc"
                        GanttLine{
                            id: ganttLine
                            color: "#ccc"
                            height: 24
                            anchors.centerIn: parent

                            viewportX: ganttView.contentX
                            viewportWidth: ganttView.width
                            model: ganttModel
                            onEditItem: {
                                ganttEditWindow.ganttItem = item
                                ganttEditWindow.visible = true
                            }
                        }
                    }
                }
            }
        }
    }


    GanttEditWindow{
        id: ganttEditWindow
    }
}
