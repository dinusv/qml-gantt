#ifndef QGANTTMODELLIST_H
#define QGANTTMODELLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>

class QGanttModel;
class QGanttModelContainer;
class QGanttModelList : public QAbstractListModel{

    Q_OBJECT
    Q_PROPERTY(qint64 contentWidth READ contentWidth NOTIFY contentWidthChanged)

public:
    enum Roles{
        Name  = Qt::UserRole + 1,
        GanttModel
    };

public:
    QGanttModelList(QObject *parent = 0);
    QGanttModelList(qint64 contentWidth, QObject* parent = 0);
    ~QGanttModelList();

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void clearAll();

    void appendModel(QGanttModel* model);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

    qint64 contentWidth() const;
    void setContentWidth(qint64 arg);

signals:
    void contentWidthChanged(qint64 arg);

private:
    QList<QGanttModelContainer*> m_items;
    QHash<int, QByteArray> m_roles;

    qint64 m_contentWidth;
};

inline int QGanttModelList::rowCount(const QModelIndex &) const{
    return m_items.size();
}

inline qint64 QGanttModelList::contentWidth() const{
    return m_contentWidth;
}

inline void QGanttModelList::setContentWidth(qint64 arg){
    if (m_contentWidth == arg)
        return;
    m_contentWidth = arg;
    emit contentWidthChanged(arg);
}

#endif // QGANTTMODELLIST_H
