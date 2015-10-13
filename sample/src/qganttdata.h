#ifndef QGANTTDATA_H
#define QGANTTDATA_H

#include <QObject>
#include <QColor>

class QGanttData : public QObject{

    Q_OBJECT
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QColor color  READ color WRITE setColor NOTIFY colorChanged)

public:
    explicit QGanttData(QObject *parent = 0);
    ~QGanttData();

    QString label() const;
    QColor  color() const;

signals:
    void labelChanged(QString arg);
    void colorChanged(QColor arg);

public slots:
    void setLabel(QString arg);
    void setColor(QColor arg);

private:
    QString m_label;
    QColor  m_color;
};

inline QString QGanttData::label() const{
    return m_label;
}

inline QColor QGanttData::color() const{
    return m_color;
}

inline void QGanttData::setLabel(QString arg){
    if (m_label == arg)
        return;

    m_label = arg;
    emit labelChanged(arg);
}

inline void QGanttData::setColor(QColor arg){
    if (m_color == arg)
        return;

    m_color = arg;
    emit colorChanged(arg);
}

#endif // QGANTTDATA_H
