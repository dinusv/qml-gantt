#include "qganttmodellist.h"
#include "qganttmodel.h"

#include <QDebug>
class QGanttModelContainer{
public:
    ~QGanttModelContainer(){ delete model; }

    QString      name;
    QGanttModel* model;
};


QGanttModelList::QGanttModelList(QObject* parent)
    : QAbstractListModel(parent){

}

QGanttModelList::~QGanttModelList(){
    clearAll();
}

QVariant QGanttModelList::data(const QModelIndex &index, int role) const{
    if ( index.row() >= m_items.size() )
        return QVariant();
    if ( role == QGanttModelList::Name )
        return m_items[index.row()]->name;
    else if ( role == QGanttModelList::GanttModel )
        return QVariant::fromValue(m_items[index.row()]->model);
    else
        return QVariant();
}

bool QGanttModelList::setData(const QModelIndex &index, const QVariant &value, int role){
    if ( index.row() >= m_items.size() )
        return false;
    if ( role == QGanttModelList::Name ){
        m_items[index.row()]->name = value.toString();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    } else
        return false;
}

QHash<int, QByteArray> QGanttModelList::roleNames() const{
    QHash<int, QByteArray> rolenames;
    rolenames[Name]       = "name";
    rolenames[GanttModel] = "ganttModel";
    return rolenames;
}

void QGanttModelList::clearAll(){
    for ( QList<QGanttModelContainer*>::Iterator it = m_items.begin(); it != m_items.end(); ++it )
        delete *it;
    m_items.clear();
}

void QGanttModelList::appendModel(QGanttModel *model){
    QGanttModelContainer* item = new QGanttModelContainer;
    item->model = model;
    item->name  = "Gantt Row #" + QString::number(m_items.size());
    m_items.append(item);
}

bool QGanttModelList::insertRows(int row, int count, const QModelIndex &parent){
    beginInsertRows(parent, row, row + count - 1);
    for ( int i =  row; i < row + count - 1; ++i ){
        QGanttModelContainer* item = new QGanttModelContainer;
        item->model = new QGanttModel;
        item->name  = "Gantt Row";
        m_items.insert(i, item);
    }
    endInsertRows();
    return true;
}

bool QGanttModelList::removeRows(int row, int count, const QModelIndex &parent){
    beginRemoveRows(parent, row, row + count - 1);
    for ( int i = row + count - 1; i <= row; --i )
        m_items.removeAt(i);
    endRemoveRows();
}

