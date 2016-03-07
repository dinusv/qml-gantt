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

Window {
    id: root
    title: "Gantt Interactions"
    modality: Qt.ApplicationModal

    visible: false
    minimumWidth: 300
    minimumHeight: 200
    width: 400
    height: 200

    ScrollView {
        anchors.fill: parent

        Rectangle {
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            width: root.width - 30
            color: 'transparent'
            height: helpGrid.height + 20

            Grid {
                id: helpGrid
                columns: 2
                spacing: 10
                width: root.width - 30

                Image {
                    width: 100
                    height: 80
                    source: "/img/help-add-item.png"
                }

                Rectangle {
                    width: root.width - 140
                    height: 80
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: root.width - 140
                        text: "To add a new item to a row, double click in the empty area inside the row."
                        color: "#333"
                        wrapMode: Text.WordWrap
                        font.family: "sans-serif"
                        font.pixelSize: 12
                    }
                }

                Image {
                    width: 100
                    height: 80
                    source: "/img/help-move-item.png"
                }

                Rectangle {
                    width: root.width - 140
                    height: 80
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: root.width - 140
                        text: "To move an item, click inside the item and drag while holding the mouse button pressed."
                        color: "#333"
                        wrapMode: Text.WordWrap
                        font.family: "sans-serif"
                        font.pixelSize: 12
                    }
                }

                Image {
                    width: 100
                    height: 80
                    source: "/img/help-stretch-item.png"
                }

                Rectangle {
                    width: root.width - 140
                    height: 80
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: parent.width
                        text: "Stretch the item by dragging its edges."
                        color: "#333"
                        wrapMode: Text.WordWrap
                        font.family: "sans-serif"
                        font.pixelSize: 12
                    }
                }

                Image {
                    width: 100
                    height: 80
                    source: "/img/help-edit-item.png"
                }

                Rectangle {
                    width: root.width - 140
                    height: 80
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: root.width - 140
                        text: "Double click an item to edit its color and label."
                        color: "#333"
                        wrapMode: Text.WordWrap
                        font.family: "sans-serif"
                        font.pixelSize: 12
                    }
                }

                Image {
                    width: 100
                    height: 80
                    source: "/img/help-edit-row.png"
                }

                Rectangle {
                    width: root.width - 140
                    height: 80
                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        width: root.width - 140
                        text: "Double click a row label to edit its name, press return once you're done."
                        color: "#333"
                        wrapMode: Text.WordWrap
                        font.family: "sans-serif"
                        font.pixelSize: 12
                    }
                }
            }
        }
    }
}
