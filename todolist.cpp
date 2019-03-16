#include "todolist.h"

ToDoList::ToDoList(QObject *parent) : QObject(parent)
{
    //add some initial sample data
    mItems.append({true, QStringLiteral("Wash the car")});
    mItems.append({false, QStringLiteral("Fix the sink")});
}

QVector<ToDoItem> ToDoList::items() const
{
    return mItems;
}
//returns whether data was successfully modified or not
bool ToDoList::setItemAt(int index, const ToDoItem &item)
{
    /*
     * check if the index is valid
     */
    if(index<0 || index >= mItems.size())
        return false;

    const ToDoItem &oldItem = mItems.at(index);
    /*
     * checks if new item has identical
     * values or not to check whether we are changing
     * the data or not
     */
    if(item.done == oldItem.done && item.description == oldItem.description){
        return false;
    }

    mItems[index] = item;
    return true;
}

void ToDoList::appendItem()
{
    emit preItemAppend();

    ToDoItem item;
    item.done = false;
    mItems.append(item);

    emit postItemAppended();
}
//check on all items and remove the ones that are done
void ToDoList::removeCompletedItems()
{
    for (int i=0;i<mItems.size();) {
        if(mItems.at(i).done){
            emit preItemRemoved(i);

            mItems.removeAt(i);

            emit postItemRemoved();
        }
        else{
            ++i;
        }
    }
}
