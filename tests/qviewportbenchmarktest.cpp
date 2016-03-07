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

#include "qviewportbenchmarktest.h"
#include "qrangeview.h"
#include "qganttmodel.h"

#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QVariant>
#include <QEventLoop>
#include <QtTest/QtTest>

#include <QThread>

Q_TEST_RUNNER_REGISTER(QViewportBenchmarkTest);

// QViewportBenchmarkTestData
// --------------------------

class QViewportBenchmarkTestData{
public:
    QViewportBenchmarkTestData(const char* delegateData);
    ~QViewportBenchmarkTestData();

    QQmlEngine*    engine;
    QQmlContext*   context;
    QQmlComponent* viewDelegate;
    QQuickItem*    container;
    QGanttModel*   model;
    QRangeView*    view;

    static const char* MINIMAL_DELEGATE;
    static const char* COMPLEX_DELEGATE;

};

const char* QViewportBenchmarkTestData::MINIMAL_DELEGATE =
    "import QtQuick 2.1\n"
    "Rectangle{\n"
    "    x:position\n "
    "    width:length\n"
    "}\n";

const char* QViewportBenchmarkTestData::COMPLEX_DELEGATE =
    "import QtQuick 2.2\n"
    "Rectangle{\n"
    "    id: ganttDelegate\n"
    "    width: length \n"
    "    height: 20\n"
    "    clip: true\n"
    "    x: position * 1\n"
    "    Rectangle{\n"
    "        id: stretchLeft\n"
    "        anchors.left: parent.left\n"
    "        anchors.top: parent.top\n"
    "        width : 2\n"
    "        height : parent.height\n"
    "        color: \"#fff\"\n"
    "        MouseArea{\n"
    "            anchors.fill: parent\n"
    "            cursorShape: Qt.SizeHorCursor\n"
    "            property int oldMouseX\n"
    "            onPressed: { oldMouseX = mouseX }\n"
    "            onPositionChanged: {\n"
    "                if ( pressed ){\n"
    "                    var newWidth  = ganttDelegate.width + oldMouseX - mouseX\n"
    "                    var newX      = ganttDelegate.x + mouseX - oldMouseX\n"
    "                    var newLength = Math.round(newWidth / 1)\n"
    "                    if ( newLength > 0 && newX + newWidth < rangeView.width ){\n"
    "                        if ( newX > 0 ){\n"
    "                            ganttDelegate.width = newWidth\n"
    "                            ganttDelegate.x     = newX\n"
    "                        } else {\n"
    "                            ganttDelegate.width = ganttDelegate.x + ganttDelegate.width\n"
    "                            ganttDelegate.x     = 0\n"
    "                        }\n"
    "                    } else {\n"
    "                        ganttDelegate.x     =\n"
    "                                ganttDelegate.x + ganttDelegate.width - (1 * 1)\n"
    "                        ganttDelegate.width = 1 * 1\n"
    "                    }\n"
    "                }\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "    Rectangle{\n"
    "        id: centerMove\n"
    "        anchors.left: parent.left\n"
    "        anchors.leftMargin: 2\n"
    "        anchors.right: parent.right\n"
    "        anchors.rightMargin: 2\n"
    "        width : parent.width\n"
    "        height : parent.height\n"
    "        color : parent.color\n"
    "        MouseArea{\n"
    "            anchors.fill: parent\n"
    "            cursorShape: Qt.SizeAllCursor\n"
    "            onPressed: { ganttDelegate.forceActiveFocus() }\n"
    "        }\n"
    "    }\n"
    "    Rectangle{\n"
    "        id: strechRight\n"
    "        anchors.right: parent.right\n"
    "        anchors.top: parent.top\n"
    "        width : 2\n"
    "        height : parent.height\n"
    "        color: \"#fff\"\n"
    "        MouseArea{\n"
    "            anchors.fill: parent\n"
    "            cursorShape: Qt.SizeHorCursor\n"
    "            property int oldMouseX\n"
    "            onPressed: oldMouseX = mouseX\n"
    "            onPositionChanged: {\n"
    "                if ( pressed ){\n"
    "                    var newWidth  = ganttDelegate.width + (mouseX - oldMouseX)\n"
    "                    var newLength = Math.round(newWidth / 1)\n"
    "                    if ( newLength > 0 ){\n"
    "                        if ( position + newLength < root.ganttLength)\n"
    "                            ganttDelegate.width = newWidth\n"
    "                        else\n"
    "                            ganttDelegate.width = (root.ganttLength - position) * 1\n"
    "                    } else\n"
    "                        ganttDelegate.width = 1 * 1\n"
    "                }\n"
    "            }\n"
    "        }\n"
    "    }\n"
    "}\n";

QViewportBenchmarkTestData::QViewportBenchmarkTestData(const char* delegateData)
    : engine(new QQmlEngine)
    , context(new QQmlContext(engine))
    , viewDelegate(new QQmlComponent(engine))
    , container(new QQuickItem)
    , model(new QGanttModel)
    , view(new QRangeView(container))
{
    engine->setContextForObject(viewDelegate, context);
    viewDelegate->setData(delegateData, QUrl());

    view->setDelegate(viewDelegate);
    view->setModel(model);
}

QViewportBenchmarkTestData::~QViewportBenchmarkTestData(){
    delete container;
    delete viewDelegate;
    delete engine;
    delete context;
    delete model;
}


// QViewportBenchmarkTest
// ----------------------

QViewportBenchmarkTest::QViewportBenchmarkTest(QObject* parent) : QObject(parent){

}

QViewportBenchmarkTest::~QViewportBenchmarkTest(){

}

void QViewportBenchmarkTest::initTestCase(){
}

void QViewportBenchmarkTest::minimalDelegateInsertionTest(){
    QViewportBenchmarkTestData data(QViewportBenchmarkTestData::MINIMAL_DELEGATE);
    data.model->setContentWidth(CONTENT_WIDTH);
    data.view->setViewportWidth(VIEWPORT_WIDTH);
    data.view->setViewportX(0);

    QBENCHMARK_ONCE{
        for ( int i = 0; i < CONTENT_WIDTH - ITEM_WIDTH; i += ITEM_WIDTH + 1 )
            data.model->insertItem(i, 1);
    }
}

void QViewportBenchmarkTest::minimalDelegateViewTest(){
    QViewportBenchmarkTestData data(QViewportBenchmarkTestData::MINIMAL_DELEGATE);
    data.model->setContentWidth(CONTENT_WIDTH);
    data.view->setViewportWidth(VIEWPORT_WIDTH);
    data.view->setViewportX(0);
    for ( int i = 0; i < CONTENT_WIDTH - ITEM_WIDTH; i += ITEM_WIDTH + 1 )
        data.model->insertItem(i, 1);

    QBENCHMARK_ONCE{
        for ( int i = 0; i < SCROLL_ITERATIONS; ++i )
            data.view->setViewportX(i);
    }
}

void QViewportBenchmarkTest::complexDelegateInsertionTest(){
    QViewportBenchmarkTestData data(QViewportBenchmarkTestData::COMPLEX_DELEGATE);

    data.model->setContentWidth(CONTENT_WIDTH);
    data.view->setViewportWidth(VIEWPORT_WIDTH);
    data.view->setViewportX(0);

    QBENCHMARK_ONCE{
        for ( int i = 0; i < CONTENT_WIDTH - ITEM_WIDTH; i += ITEM_WIDTH + 1 )
            data.model->insertItem(i, 1);
    }
}

void QViewportBenchmarkTest::complexDelegateViewTest(){
    QViewportBenchmarkTestData data(QViewportBenchmarkTestData::COMPLEX_DELEGATE);
    data.model->setContentWidth(CONTENT_WIDTH);
    data.view->setViewportWidth(VIEWPORT_WIDTH);
    data.view->setViewportX(0);
    for ( int i = 0; i < CONTENT_WIDTH - ITEM_WIDTH; i += ITEM_WIDTH + 1 )
        data.model->insertItem(i, 1);

    QBENCHMARK_ONCE{
        for ( int i = 0; i < SCROLL_ITERATIONS; ++i )
            data.view->setViewportX(i);
    }
}
