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

#ifndef QVIEWPORTBENCHMARKTEST_HPP
#define QVIEWPORTBENCHMARKTEST_HPP

#include <QObject>
#include "qtestrunner.h"

class QViewportBenchmarkTest : public QObject{

    Q_OBJECT
    Q_TEST_RUNNER_SUITE

public:
    static const int CONTENT_WIDTH     = 20000;
    static const int VIEWPORT_WIDTH    = 2000;
    static const int ITEM_WIDTH        = 1;
    static const int SCROLL_ITERATIONS = 6000;

public:
    QViewportBenchmarkTest(QObject* parent = 0);
    ~QViewportBenchmarkTest();

private slots:
    void initTestCase();
    void minimalDelegateInsertionTest();
    void minimalDelegateViewTest();
    void complexDelegateInsertionTest();
    void complexDelegateViewTest();

};

#endif // QVIEWPORTBENCHMARKTEST_HPP
