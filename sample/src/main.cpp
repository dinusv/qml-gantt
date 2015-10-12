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

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "qrangeview.h"
#include "qganttmodel.h"
#include "qganttmodelitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGanttModel m;
    m.setContentWidth(20000);

    for ( int i = 0; i < 20000; i = i + 50){
        m.insertItem(i, 25);
    }

    qmlRegisterUncreatableType<QAbstractRangeModel>(
                "Gantt", 1, 0, "AbstractRangeModel", "AbstractRangeModel is of abstract type.");
    qmlRegisterType<QRangeView>(     "Gantt", 1, 0, "RangeView");
    qmlRegisterType<QGanttModel>(    "Gantt", 1, 0, "GanttModel");
    qmlRegisterType<QGanttModelItem>("Gantt", 1, 0, "GanttModelItem");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("timelineModel", &m);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
