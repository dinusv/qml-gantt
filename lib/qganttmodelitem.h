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

#ifndef QGANTTMODELITEM_H
#define QGANTTMODELITEM_H

#include "qganttglobal.h"
#include <QObject>

class Q_GANTT_EXPORT QGanttModelItem : public QObject{

    Q_OBJECT
    Q_PROPERTY(qint64 position READ position NOTIFY positionChanged)
    Q_PROPERTY(qint64 length   READ length   NOTIFY lengthChanged)
    Q_PROPERTY(QString data    READ data     NOTIFY dataChanged)

public:
    explicit QGanttModelItem(QObject *parent = 0);
    QGanttModelItem(qint64 position, qint64 length, QObject* parent = 0);
    virtual ~QGanttModelItem();

    qint64 position() const;
    qint64 length() const;
    const QString& data() const;

    void setPosition(qint64 arg);
    void setLength(qint64 arg);
    void setData(const QString& data);

signals:
    void positionChanged();
    void lengthChanged();
    void dataChanged();

private:
    qint64  m_position;
    qint64  m_length;
    QString m_data;
};

inline qint64 QGanttModelItem::position() const{
    return m_position;
}

inline qint64 QGanttModelItem::length() const{
    return m_length;
}

inline void QGanttModelItem::setPosition(qint64 arg){
    if (m_position == arg)
        return;

    m_position = arg;
    emit positionChanged();
}

inline void QGanttModelItem::setLength(qint64 arg){
    if (m_length == arg)
        return;

    m_length = arg;
    emit lengthChanged();
}

inline const QString&QGanttModelItem::data() const{
    return m_data;
}

inline void QGanttModelItem::setData(const QString& data){
    if ( data != m_data ){
        m_data = data;
        emit dataChanged();
    }
}

#endif // QGANTTMODELITEM_H
