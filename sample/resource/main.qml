/****************************************************************************
**
** Copyright (C) 2015 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of QML Gantt Timeline library.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
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
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Delete Stuff")
                onTriggered: ;
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Rectangle{

        id: root
        property int zoomScale : 1
        property int timelineLength : timelineModel.contentWidth
        property color elementColor: "#aa0000"
        property color elementBorderColor: "#aaa"
        property color elementFocusColor: "#bb0000"

        width: parent.width
        anchors.fill: parent
        color: "#333"

        Text{
            text: rangeView.viewportX
            color: "#ff00ff"
        }

        ScrollView{
            id : scrollView
            height: parent.height
            width: parent.width

            flickableItem.onContentXChanged: rangeView.viewportX = flickableItem.contentX
            flickableItem.onWidthChanged: rangeView.viewportWidth = flickableItem.width

            RangeView{
                id : rangeView
                model: timelineModel
                height : root.height

                delegate: Component{

                    Rectangle{
                        id: timelineDelegate

                        width: length * root.zoomScale
                        height: rangeView.height

                        clip: true
                        color: root.elementColor

                        x: position * root.zoomScale

                        Keys.onPressed: {
                            if ( event.key === Qt.Key_Delete ){
                                event.accepted = true
                                root.model.removeSequence(sequence)

                            } else if ( event.key === Qt.Key_Left ){

                                if ( event.modifiers & Qt.ShiftModifier ){
                                    var newLength = length - 1
                                    if ( newLength > 0){
                                        length = newLength
                                        timelineDelegate.width = length * root.zoomScale
                                    }
                                } else if ( event.modifiers & Qt.ControlModifier ){
                                    var newPosition = root.currentFrame - length
                                    if ( newPosition < 0 )
                                        newPosition = 0
                                    position = newPosition
                                    timelineDelegate.x = position * root.zoomScale

                                } else {
                                    var newPosition = position - 1
                                    if ( newPosition >= 0 ){
                                        position = newPosition
                                        timelineDelegate.x = position * root.zoomScale
                                    }
                                }
                                event.accepted = true

                            } else if ( event.key === Qt.Key_Right ){

                                if ( event.modifiers & Qt.ShiftModifier ){
                                    var newLength = length + 1
                                    if ( position + length < root.videoLength ){
                                        length = newLength
                                        timelineDelegate.width = length * root.zoomScale
                                    }
                                } else if ( event.modifiers & Qt.ControlModifier ){

                                    var newPosition = root.currentFrame
                                    if ( newPosition + length > root.videoLength )
                                        newPosition = root.videoLength - length
                                    position = newPosition
                                    timelineDelegate.x = position * root.zoomScale

                                } else {
                                    var newPosition = position + 1
                                    if ( position + length < root.videoLength ){
                                        position = newPosition
                                        timelineDelegate.x = position * root.zoomScale
                                    }
                                }

                                position = Math.round(timelineDelegate.x / root.zoomScale)
                                timelineDelegate.x = position * root.zoomScale

                                event.accepted = true
                            }
                        }

                        Rectangle{
                            id: stretchLeft
                            anchors.left: parent.left
                            anchors.top: parent.top
                            width : 2
                            height : parent.height
                            color: timelineDelegate.activeFocus ? "#666" : root.elementBorderColor

                            MouseArea{
                                anchors.fill: parent
                                cursorShape: Qt.SizeHorCursor

                                property int oldMouseX

                                onPressed: {
                                    oldMouseX = mouseX
                                }
                                onPositionChanged: {
                                    if ( pressed ){
                                        var newWidth  = timelineDelegate.width + oldMouseX - mouseX
                                        var newX      = timelineDelegate.x + mouseX - oldMouseX
                                        var newLength = Math.round(newWidth / root.zoomScale)
                                        if ( newLength > 0 && newX + newWidth < rangeView.width ){
                                            if ( newX > 0 ){
                                                timelineDelegate.width = newWidth
                                                timelineDelegate.x     = newX
                                            } else {
                                                timelineDelegate.width = timelineDelegate.x + timelineDelegate.width
                                                timelineDelegate.x     = 0
                                            }
                                        } else {
                                            timelineDelegate.x     =
                                                    timelineDelegate.x + timelineDelegate.width - (1 * root.zoomScale)
                                            timelineDelegate.width = 1 * root.zoomScale
                                        }
                                    }
                                }

                                onReleased: {
                                    rangeView.setItemLength(timelineDelegate, Math.round(timelineDelegate.width / root.zoomScale))
                                    rangeView.setItemPosition(timelineDelegate, Math.round(timelineDelegate.x / root.zoomScale))
                                    timelineDelegate.width = length * root.zoomScale
                                    timelineDelegate.x     = position * root.zoomScale
                                }
                            }
                        }
                        Rectangle{
                            id: centerMove
                            anchors.left: parent.left
                            anchors.leftMargin: 2
                            anchors.right: parent.right
                            anchors.rightMargin: 2
                            width : parent.width
                            height : parent.height
                            color : timelineDelegate.activeFocus ? root.elementFocusColor : parent.color
                            MouseArea{
                                anchors.fill: parent
                                cursorShape: Qt.SizeAllCursor
                                drag.target: timelineDelegate
                                drag.axis: Drag.XAxis
                                drag.minimumX: 0
                                drag.maximumX: rangeView.width - timelineDelegate.width
                                onPressed: {
                                    timelineDelegate.forceActiveFocus()
                                }
                                onDoubleClicked: {
                                    if ( mouse.modifiers & Qt.ControlModifier ){
                                        var leftDistance = root.currentFrame - position
                                        var rightDistance = root.currentFrame - (position + length)
                                        if ( Math.abs(rightDistance) > Math.abs(leftDistance) ){
                                            length -= leftDistance
                                            position += leftDistance
                                            timelineDelegate.width = length * root.zoomScale
                                            timelineDelegate.x     = position * root.zoomScale
                                        } else {
                                            length += rightDistance
                                            if ( length < 1 )
                                                length = 1
                                            timelineDelegate.width = length * root.zoomScale
                                        }
                                    } else {
                                        root.sequenceEdit(sequence)
                                    }
                                }
                                onReleased :{
                                    rangeView.setItemPosition(timelineDelegate, Math.round(timelineDelegate.x / root.zoomScale))
                                    timelineDelegate.x = position * root.zoomScale
                                }
                            }
                        }
                        Rectangle{
                            id: strechRight
                            anchors.right: parent.right
                            anchors.top: parent.top
                            width : 2
                            height : parent.height
                            color: timelineDelegate.activeFocus ? "#666" : root.elementBorderColor

                            MouseArea{
                                anchors.fill: parent
                                cursorShape: Qt.SizeHorCursor

                                property int oldMouseX

                                onPressed: oldMouseX = mouseX
                                onPositionChanged: {
                                    if ( pressed ){
                                        var newWidth  = timelineDelegate.width + (mouseX - oldMouseX)
                                        var newLength = Math.round(newWidth / root.zoomScale)
                                        if ( newLength > 0 ){
                                            if ( position + newLength < root.timelineLength)
                                                timelineDelegate.width = newWidth
                                            else
                                                timelineDelegate.width = (root.timelineLength - position) * root.zoomScale
                                        } else
                                            timelineDelegate.width = 1 * root.zoomScale
                                    }
                                }
                                onReleased: {
                                    rangeView.setItemLength(timelineDelegate, Math.round(timelineDelegate.width / root.zoomScale))
                                    timelineDelegate.width = length * root.zoomScale
                                }
                            }
                        }
                }

                }
            }
        }
    }
}
