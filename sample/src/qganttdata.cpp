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

#include "qganttdata.h"

 const QColor initColors[4] = {QColor("#bb4e4c"), QColor("#218c8d"), QColor("#4f83bd"), QColor("#e39541")};

QGanttData::QGanttData(QObject *parent)
    : QObject(parent)
    , m_color(initColors[rand() % 4]){
}

QGanttData::~QGanttData(){
}

