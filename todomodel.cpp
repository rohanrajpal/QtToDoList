#include "todomodel.h"

#include "todolist.h"

ToDoModel::ToDoModel(QObject *parent)
    : QAbstractListModel(parent)
    , mList(nullptr)
{
}

int ToDoModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    // safe gaurd against null pointer accesses
    if (parent.isValid() || !mList)
        return 0;

    return mList->items().size();
}

QVariant ToDoModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !mList)
        return QVariant();

    const ToDoItem item = mList->items().at(index.row());

    switch (role) {
        case DoneRole:
            /*
             * QVariant class acts like a union
             * for most common qt data types
             */
            return QVariant(item.done);
        case DescriptionRole:
            return QVariant(item.description);
    }
    return QVariant();
}

bool ToDoModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!mList){
        return false;
    }
    ToDoItem item = mList->items().at(index.row());
    switch (role) {
        case DoneRole:
            //now we convert back the QVariant by typecasting
            item.done = value.toBool();
            break;
        case DescriptionRole:
            item.description = value.toString();
            break;
    }

    //check whether data has changed
    if (mList->setItemAt(index.row(),item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags ToDoModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> ToDoModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[DoneRole] = "done";
    names[DescriptionRole] = "description";
    return names;
}

ToDoList *ToDoModel::list() const
{
    return mList;
}

void ToDoModel::setList(ToDoList *list)
{
    beginResetModel();

    if(mList){
        //disconnet from the old list when assigning to
        // a new list
        mList->disconnect(this);
    }
    mList = list;

    if(mList){
        connect(mList, &ToDoList::preItemAppend, this, [=](){
           const int index = mList->items().size();
           beginInsertRows(QModelIndex(), index, index);
        });

        connect(mList, &ToDoList::postItemAppended, this, [=](){
            endInsertRows();
        });

        connect(mList, &ToDoList::preItemRemoved, this, [=](int index){
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mList, &ToDoList::postItemRemoved, this, [=](){
           endRemoveRows();
        });

    }

    endResetModel();
}
