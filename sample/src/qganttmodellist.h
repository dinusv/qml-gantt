#ifndef QGANTTMODELLIST_H
#define QGANTTMODELLIST_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>

class QGanttModel;
class QGanttModelContainer;
class QGanttModelList : public QAbstractListModel{

public:
    enum Roles{
        Name  = Qt::UserRole + 1,
        GanttModel
    };

public:
    QGanttModelList(QObject *parent = 0);
    ~QGanttModelList();

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent) const;
    virtual QHash<int, QByteArray> roleNames() const;

    void clearAll();

    void appendModel(QGanttModel* model);

    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);

private:
    QList<QGanttModelContainer*> m_items;
    QHash<int, QByteArray> m_roles;

};

inline int QGanttModelList::rowCount(const QModelIndex &) const{
    return m_items.size();
}

#endif // QGANTTMODELLIST_H
