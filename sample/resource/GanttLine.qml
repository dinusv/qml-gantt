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

import QtQuick 2.2
import QtQuick.Controls 1.1
import Gantt 1.0

Rectangle{
    id: root

    signal editItem(variant item)

    property variant model: GanttModel{}

    property int zoomScale: 1
    property int ganttLength: ganttModel.contentWidth

    property alias viewportX: rangeView.viewportX
    property alias viewportWidth: rangeView.viewportWidth

    property color elementBorderColor: "#ccc"
    property color elementBorderFocusColor: "#fff"

    color: "#ccc"
    width: rangeView.width * zoomScale

    RangeView {
        id: rangeView

        model: ganttModel
        height: root.height

        MouseArea {
            anchors.fill: parent
            onDoubleClicked: {
                var itemPosition = mouse.x - 10 >= 0 ? mouse.x - 10 : 0
                if (itemPosition + 20 >= ganttModel.contentWidth)
                    itemPosition = ganttModel.contentWidth - 20
                ganttModel.insertItem(itemPosition, 20)
            }
        }

        delegate: Component {

            Rectangle {
                id: ganttDelegate

                width: length * root.zoomScale
                height: rangeView.height

                clip: true
                color: modelData.color

                x: position * root.zoomScale

                Keys.onPressed: {
                    if (event.key === Qt.Key_Delete) {
                        event.accepted = true
                        rangeView.removeItemViaDelegate(ganttDelegate)
                    } else if (event.key === Qt.Key_Left) {

                        if (event.modifiers & Qt.ShiftModifier) {
                            var newLength = length - 1
                            if (newLength > 0) {
                                rangeView.setLengthViaDelegate(ganttDelegate,
                                                               newLength)
                                ganttDelegate.width = newLength * root.zoomScale
                            }
                        } else {
                            var newPosition = position - 1
                            if (newPosition >= 0) {
                                rangeView.setPositionViaDelegate(ganttDelegate,
                                                                 newPosition)
                                ganttDelegate.x = newPosition * root.zoomScale
                            }
                        }
                        event.accepted = true
                    } else if (event.key === Qt.Key_Right) {

                        if (event.modifiers & Qt.ShiftModifier) {
                            var newLength = length + 1
                            if (position + length < ganttModel.contentWidth) {
                                rangeView.setLengthViaDelegate(ganttDelegate,
                                                               newLength)
                                ganttDelegate.width = newLength * root.zoomScale
                            }
                        } else {
                            var newPosition = position + 1
                            if (position + length < ganttModel.contentWidth) {
                                rangeView.setPositionViaDelegate(ganttDelegate,
                                                                 newPosition)
                                ganttDelegate.x = newPosition * root.zoomScale
                            }
                        }

                        event.accepted = true
                    }
                }

                Rectangle {
                    id: stretchLeft
                    anchors.left: parent.left
                    anchors.top: parent.top
                    width: 2
                    height: parent.height
                    color: ganttDelegate.activeFocus ? root.elementBorderFocusColor : root.elementBorderColor

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.SizeHorCursor

                        property int oldMouseX

                        onPressed: {
                            oldMouseX = mouseX
                        }
                        onPositionChanged: {
                            if (pressed) {
                                var newWidth = ganttDelegate.width + oldMouseX - mouseX
                                var newX = ganttDelegate.x + mouseX - oldMouseX
                                var newLength = Math.round(
                                            newWidth / root.zoomScale)
                                if (newLength > 0
                                        && newX + newWidth < rangeView.width) {
                                    if (newX > 0) {
                                        ganttDelegate.width = newWidth
                                        ganttDelegate.x = newX
                                    } else {
                                        ganttDelegate.width = ganttDelegate.x + ganttDelegate.width
                                        ganttDelegate.x = 0
                                    }
                                } else {
                                    ganttDelegate.x = ganttDelegate.x
                                            + ganttDelegate.width - (1 * root.zoomScale)
                                    ganttDelegate.width = 1 * root.zoomScale
                                }
                            }
                        }

                        onReleased: {
                            rangeView.setLengthViaDelegate(
                                        ganttDelegate, Math.round(
                                            ganttDelegate.width / root.zoomScale))
                            rangeView.setPositionViaDelegate(
                                        ganttDelegate, Math.round(
                                            ganttDelegate.x / root.zoomScale))
                            ganttDelegate.width = length * root.zoomScale
                            ganttDelegate.x = position * root.zoomScale
                        }
                    }
                }
                Rectangle {
                    id: centerMove
                    anchors.left: parent.left
                    anchors.leftMargin: 2
                    anchors.right: parent.right
                    anchors.rightMargin: 2
                    width: parent.width
                    height: parent.height
                    color: parent.color
                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.SizeAllCursor
                        drag.target: ganttDelegate
                        drag.axis: Drag.XAxis
                        drag.minimumX: 0
                        drag.maximumX: rangeView.width - ganttDelegate.width
                        onPressed: {
                            ganttDelegate.forceActiveFocus()
                        }
                        onDoubleClicked: {
                            if (mouse.modifiers & Qt.ControlModifier) {
                                var leftDistance = root.currentFrame - position
                                var rightDistance = root.currentFrame - (position + length)
                                if (Math.abs(rightDistance) > Math.abs(
                                            leftDistance)) {
                                    length -= leftDistance
                                    position += leftDistance
                                    ganttDelegate.width = length * root.zoomScale
                                    ganttDelegate.x = position * root.zoomScale
                                } else {
                                    length += rightDistance
                                    if (length < 1)
                                        length = 1
                                    ganttDelegate.width = length * root.zoomScale
                                }
                            } else {
                                root.editItem(modelData)
                            }
                        }
                        onReleased: {
                            rangeView.setPositionViaDelegate(
                                        ganttDelegate, Math.round(
                                            ganttDelegate.x / root.zoomScale))
                            ganttDelegate.x = position * root.zoomScale
                        }
                    }
                }
                Rectangle {
                    id: strechRight
                    anchors.right: parent.right
                    anchors.top: parent.top
                    width: 2
                    height: parent.height
                    color: ganttDelegate.activeFocus ? root.elementBorderFocusColor : root.elementBorderColor

                    MouseArea {
                        anchors.fill: parent
                        cursorShape: Qt.SizeHorCursor

                        property int oldMouseX

                        onPressed: oldMouseX = mouseX
                        onPositionChanged: {
                            if (pressed) {
                                var newWidth = ganttDelegate.width + (mouseX - oldMouseX)
                                var newLength = Math.round(
                                            newWidth / root.zoomScale)
                                if (newLength > 0) {
                                    if (position + newLength < root.ganttLength)
                                        ganttDelegate.width = newWidth
                                    else
                                        ganttDelegate.width = (root.ganttLength - position)
                                                * root.zoomScale
                                } else
                                    ganttDelegate.width = 1 * root.zoomScale
                            }
                        }
                        onReleased: {
                            rangeView.setLengthViaDelegate(
                                        ganttDelegate, Math.round(
                                            ganttDelegate.width / root.zoomScale))
                            ganttDelegate.width = length * root.zoomScale
                        }
                    }
                }

                Text {
                    anchors.left: parent.left
                    anchors.leftMargin: 5
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#fff"
                    text: modelData.label
                    font.family: "sans-serif"
                    font.pixelSize: 10
                }
            }
        }
    }
}
