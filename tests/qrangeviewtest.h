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

#ifndef QRANGEVIEWTEST_H
#define QRANGEVIEWTEST_H

#include <QObject>
#include "qtestrunner.h"

class QQmlEngine;
class QQmlContext;
class QQmlComponent;
class QQuickItem;
class QRangeView;
class QRangeViewTest : public QObject{

    Q_OBJECT
    Q_TEST_RUNNER_SUITE

public:
    explicit QRangeViewTest(QObject *parent = 0);
    ~QRangeViewTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void lookupTest();
    void edgeLookupTest();
    void modelItemChangeTest();
    void modelItemPositionChangeTest();
    void modelItemLengthChangeTest();
    void modelItemDataChangeTest();

private:
    QQmlEngine*    m_engine;
    QQmlContext*   m_context;
    QQmlComponent* m_viewDelegate;
    QQuickItem*    m_container;

private:
    QRangeView* createView();
    QVariant    getModelData(QRangeView* view, qint64 startPos, qint64 endPos, int role);
};

#endif // QRANGEVIEWTEST_H
