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

#ifndef QGANTTMODELTEST_HPP
#define QGANTTMODELTEST_HPP

#include <QObject>
#include "qtestrunner.h"

class QGanttModelTest : public QObject{

    Q_OBJECT
    Q_TEST_RUNNER_SUITE

public:
    explicit QGanttModelTest(QObject *parent = 0);
    ~QGanttModelTest();

private slots:
    void initTestCase();
    void descendingTest();
    void alternateTest();
    void sameLengthTest();
    void sameLengthTest2();

};

#endif // QGANTTMODELTEST_HPP
