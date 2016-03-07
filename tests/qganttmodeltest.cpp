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

#include "qganttmodeltest.h"
#include "qganttmodel.h"

#include <QScopedPointer>
#include <QtTest/QtTest>
#include <QVariant>


Q_TEST_RUNNER_REGISTER(QGanttModelTest);

class QGanttModelTestHelper{

public:
    typedef QPair<int, int> Range;
    typedef QList<Range>    RangeList;

public:
    static bool compare(QGanttModel& model, const RangeList& ranges);

};

QGanttModelTest::QGanttModelTest(QObject *parent) : QObject(parent){

}

QGanttModelTest::~QGanttModelTest(){

}

void QGanttModelTest::initTestCase(){
}

void QGanttModelTest::descendingTest(){
    QGanttModel model;
    model.setContentWidth(100);
    model.insertItem(60, 10);
    model.insertItem(50, 10);
    model.insertItem(40, 10);
    model.insertItem(30, 10);
    QCOMPARE(QGanttModelTestHelper::compare(
        model,
        QGanttModelTestHelper::RangeList() <<
             QGanttModelTestHelper::Range(30, 10) <<
             QGanttModelTestHelper::Range(40, 10) <<
             QGanttModelTestHelper::Range(50, 10) <<
             QGanttModelTestHelper::Range(60, 10)
    ), true);
}

void QGanttModelTest::alternateTest(){
    QGanttModel model;
    model.setContentWidth(100);
    model.insertItem(10, 10);
    model.insertItem(5, 10);
    model.insertItem(20, 10);
    model.insertItem(4, 10);
    QCOMPARE(QGanttModelTestHelper::compare(
        model,
        QGanttModelTestHelper::RangeList() <<
             QGanttModelTestHelper::Range(4, 10) <<
             QGanttModelTestHelper::Range(5, 10) <<
             QGanttModelTestHelper::Range(10, 10) <<
             QGanttModelTestHelper::Range(20, 10)
    ), true);
}

void QGanttModelTest::sameLengthTest(){
    QGanttModel model;
    model.setContentWidth(100);
    model.insertItem(10, 10);
    model.insertItem(10, 10);
    model.insertItem(10, 12);
    model.insertItem(10, 11);
    QCOMPARE(QGanttModelTestHelper::compare(
        model,
        QGanttModelTestHelper::RangeList() <<
             QGanttModelTestHelper::Range(10, 10) <<
             QGanttModelTestHelper::Range(10, 10) <<
             QGanttModelTestHelper::Range(10, 11) <<
             QGanttModelTestHelper::Range(10, 12)
    ), true);
}

void QGanttModelTest::sameLengthTest2(){
    QGanttModel model;
    model.setContentWidth(100);
    model.insertItem(10, 10);
    model.insertItem(10, 10);
    model.insertItem(9, 11);
    model.insertItem(9, 11);
    model.insertItem(9, 10);
    model.insertItem(10, 12);
    model.insertItem(10, 10);
    model.insertItem(10, 11);
    model.insertItem(14, 2);
    model.insertItem(14, 1);
    QCOMPARE(QGanttModelTestHelper::compare(
        model,
        QGanttModelTestHelper::RangeList() <<
             QGanttModelTestHelper::Range(9, 10) <<
             QGanttModelTestHelper::Range(9, 11) <<
             QGanttModelTestHelper::Range(9, 11) <<
             QGanttModelTestHelper::Range(10, 10) <<
             QGanttModelTestHelper::Range(10, 10) <<
             QGanttModelTestHelper::Range(10, 10) <<
             QGanttModelTestHelper::Range(10, 11) <<
             QGanttModelTestHelper::Range(10, 12) <<
             QGanttModelTestHelper::Range(14, 1) <<
             QGanttModelTestHelper::Range(14, 2)
    ), true);
}

bool QGanttModelTestHelper::compare(QGanttModel& model, const QGanttModelTestHelper::RangeList& ranges){
    QScopedPointer<QAbstractRangeModelIterator> modelIt(model.dataBetween(0, model.contentWidth()));
    QGanttModelTestHelper::RangeList::const_iterator it = ranges.begin();
    while ( !modelIt->isEnd() ){
        if ( it == ranges.end() )
            return false;
        qint64 position = modelIt->data(QAbstractRangeModel::PositionRole).toLongLong();
        qint64 length   = modelIt->data(QAbstractRangeModel::LengthRole).toLongLong();
        if ( position != it->first || length != it->second )
            return false;
        ++it;
        modelIt->nextItem();
    }
    return true;
}
