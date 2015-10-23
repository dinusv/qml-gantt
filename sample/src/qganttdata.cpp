#include "qganttdata.h"

 const QColor initColors[4] = {QColor("#bb4e4c"), QColor("#218c8d"), QColor("#4f83bd"), QColor("#e39541")};

QGanttData::QGanttData(QObject *parent)
    : QObject(parent)
    , m_color(initColors[rand() % 4]){
}

QGanttData::~QGanttData(){
}

