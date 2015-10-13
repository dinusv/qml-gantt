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

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qrangeview.h"
#include "qganttmodel.h"
#include "qganttmodelitem.h"
#include "qganttdata.h"

QVariant createModelData(){
    return QVariant::fromValue(new QGanttData);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterUncreatableType<QAbstractRangeModel>(
                "Gantt", 1, 0, "AbstractRangeModel", "AbstractRangeModel is of abstract type.");
    qmlRegisterType<QRangeView>(     "Gantt", 1, 0, "RangeView");
    qmlRegisterType<QGanttModel>(    "Gantt", 1, 0, "GanttModel");
    qmlRegisterType<QGanttModelItem>("Gantt", 1, 0, "GanttModelItem");
    qmlRegisterType<QGanttData>(     "Gantt", 1, 0, "GanttData");

    QGanttModel m;
    m.setItemDataFactoryFunction(&createModelData);
    m.setContentWidth(20000);

    for ( int i = 0; i < 20000; i = i + 100){
        m.insertItem(i, 40);
    }


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("ganttModel", &m);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
