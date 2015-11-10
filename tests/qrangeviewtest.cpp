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

#include "qrangeviewtest.h"
#include "qganttmodel.h"
#include "qrangeview.h"

#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QVariant>
#include <QtTest/QtTest>

Q_TEST_RUNNER_REGISTER(QRangeViewTest);

QRangeViewTest::QRangeViewTest(QObject *parent)
    : QObject(parent)
    , m_engine(0)
    , m_context(0)
    , m_viewDelegate(0)
{
}

QRangeViewTest::~QRangeViewTest(){
}

void QRangeViewTest::initTestCase(){
    m_engine       = new QQmlEngine;
    m_context      = new QQmlContext(m_engine);
    m_viewDelegate = new QQmlComponent(m_engine);
    m_container    = new QQuickItem;

    m_engine->setContextForObject(m_viewDelegate, m_context);
    m_viewDelegate->setData("import QtQuick 2.1\nRectangle{x:position; width:length}", QUrl());
}

void QRangeViewTest::cleanupTestCase(){
    delete m_container;
    delete m_viewDelegate;
    delete m_engine;
    delete m_context;
}

void QRangeViewTest::lookupTest(){
    QRangeView* view = createView();

    view->model()->setContentWidth(200);
    for ( int i = 10; i < 200; i += 10 )
        view->model()->insertItem(i, 10);
    view->setViewportWidth(100);

    view->setViewportX(0);
    QCOMPARE(m_container->childItems().size(), 10);

    view->setViewportX(100);
    QCOMPARE(m_container->childItems().size(), 11);

    view->setViewportX(150);
    QCOMPARE(m_container->childItems().size(), 6);

    view->setViewportWidth(15);
    QCOMPARE(m_container->childItems().size(), 3);

    view->setViewportWidth(10);
    QCOMPARE(m_container->childItems().size(), 2);

    view->setViewportWidth(11);
    QCOMPARE(m_container->childItems().size(), 3);

    view->setViewportX(159);
    QCOMPARE(m_container->childItems().size(), 3);

    delete view->model();
    delete view;
}

void QRangeViewTest::edgeLookupTest(){
    QRangeView* view = createView();

    view->model()->setContentWidth(200);
    view->setViewportWidth(100);

    view->model()->insertItem(10, 30);
    view->model()->insertItem(5, 40);
    view->model()->insertItem(10, 40);

    view->setViewportX(60);
    QCOMPARE(m_container->childItems().size(), 1);
    view->setViewportX(45);
    QCOMPARE(m_container->childItems().size(), 2);
    view->setViewportX(0);
    QCOMPARE(m_container->childItems().size(), 4);

    view->model()->insertItem(20, 10);
    QCOMPARE(m_container->childItems().size(), 5);

    // keep all items, due to the first segment (5, 40) that covers the rest
    view->setViewportX(40);
    QCOMPARE(m_container->childItems().size(), 5);

    delete view->model();
    delete view;
}

void QRangeViewTest::modelItemChangeTest(){
    QRangeView* view = createView();

    view->model()->setContentWidth(200);
    for ( int i = 10; i < 200; i += 10 )
        view->model()->insertItem(i, 10);

    view->setViewportWidth(100);
    view->setViewportX(0);
    QCOMPARE(m_container->childItems().size(), 10);

    view->model()->removeItem(10, 10, 0);
    QCOMPARE(m_container->childItems().size(), 9);

    view->model()->removeItem(20, 10, 0);
    view->model()->removeItem(30, 10, 0);
    view->model()->removeItem(40, 10, 0);
    view->model()->removeItem(50, 10, 0);
    QCOMPARE(m_container->childItems().size(), 5);

    view->model()->insertItem(33, 5);
    view->model()->insertItem(99, 10);
    view->model()->insertItem(99, 10);
    view->model()->insertItem(99, 10);
    view->model()->insertItem(98, 10);
    QCOMPARE(m_container->childItems().size(), 10);

    view->model()->removeItem(99, 10, 1);
    QCOMPARE(m_container->childItems().size(), 9);

    view->model()->removeItem(98, 10, 0);
    QCOMPARE(m_container->childItems().size(), 8);

    view->setViewportX(100);
    QCOMPARE(m_container->childItems().size(), 13);

    view->model()->insertItem(99, 1);
    QCOMPARE(m_container->childItems().size(), 13);

    delete view->model();
    delete view;
}

void QRangeViewTest::modelItemPositionChangeTest(){
    QRangeView* view = createView();

    view->model()->setContentWidth(200);
    for ( int i = 10; i < 200; i += 10 )
        view->model()->insertItem(i, 10);

    view->setViewportWidth(100);
    view->setViewportX(0);
    QCOMPARE(m_container->childItems().size(), 10);

    view->model()->setItemPosition(10, 10, 0, 100);
    QCOMPARE(m_container->childItems().size(), 9);

    view->model()->setItemPosition(150, 10, 0, 99);
    QCOMPARE(m_container->childItems().size(), 10);

    view->model()->insertItem(99, 10);
    view->model()->insertItem(99, 10);
    QCOMPARE(m_container->childItems().size(), 12);

    view->model()->setItemPosition(99, 10, 2, 101);
    QCOMPARE(m_container->childItems().size(), 11);

    view->model()->setItemPosition(101, 10, 0, 99);
    QCOMPARE(m_container->childItems().size(), 12);

    delete view->model();
    delete view;
}

void QRangeViewTest::modelItemLengthChangeTest(){
    QRangeView* view = createView();

    view->model()->setContentWidth(200);
    for ( int i = 10; i < 200; i += 10 )
        view->model()->insertItem(i, 10);

    view->setViewportWidth(100);
    view->setViewportX(15);
    QCOMPARE(m_container->childItems().size(), 12);

    view->model()->setItemLength(10, 10, 0, 5);
    QCOMPARE(m_container->childItems().size(), 11);

    view->model()->setItemLength(20, 10, 0, 5);
    QCOMPARE(m_container->childItems().size(), 11);

    view->model()->insertItem(5, 10);
    QCOMPARE(m_container->childItems().size(), 11);

    view->model()->setItemLength(5, 10, 0, 15);
    QCOMPARE(m_container->childItems().size(), 12);

    delete view->model();
    delete view;
}

void QRangeViewTest::modelItemDataChangeTest(){
    QRangeView* view = createView();

    view->model()->setContentWidth(200);
    for ( int i = 10; i < 200; i += 10 )
        view->model()->insertItem(i, 10);

    view->setViewportWidth(100);
    view->setViewportX(0);

    QCOMPARE(m_container->childItems().size(), 10);

    view->setDataViaDelegate(m_container->childItems()[2], "modelData", "200");
    QCOMPARE(getModelData(view, 30, 31, QGanttModel::modelData), QVariant("200"));
    QCOMPARE(qmlContext(m_container->childItems()[2])->contextProperty("modelData"), QVariant("200"));

    view->setDataViaDelegate(m_container->childItems()[1], "modelData", "3300");
    QCOMPARE(getModelData(view, 20, 21, QGanttModel::modelData), QVariant("3300"));
    QCOMPARE(qmlContext(m_container->childItems()[1])->contextProperty("modelData"), QVariant("3300"));

    view->setDataViaDelegate(m_container->childItems()[9], "modelData", "100");
    QCOMPARE(getModelData(view, 100, 101, QGanttModel::modelData), QVariant("100"));
    QCOMPARE(qmlContext(m_container->childItems()[9])->contextProperty("modelData"), QVariant("100"));

    delete view->model();
    delete view;
}

QRangeView *QRangeViewTest::createView(){
    QRangeView* view = new QRangeView(m_container);
    view->setDelegate(m_viewDelegate);
    view->setModel(new QGanttModel);
    return view;
}

QVariant QRangeViewTest::getModelData(QRangeView* view, qint64 startPos, qint64 endPos, int role){
    QAbstractRangeModelIterator* modelIt = view->model()->dataBetween(startPos, endPos);
    if ( modelIt->isEnd() )
        return QVariant();
    QVariant value = modelIt->data(role);
    delete modelIt;
    return value;
}
