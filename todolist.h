#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QVector>

//make a struct for each obj
struct ToDoItem{
    bool done;
    QString description;
};

class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QObject *parent = nullptr);

    QVector<ToDoItem> items() const;
    //this will allow the model to modify the
    // todo list data
    bool setItemAt(int index, const ToDoItem &item);
//signals send signals to slots
signals:
    //signal functions don't need definitions

    //need to notify before something happens to
    // data and after that
    void preItemAppend();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

public slots:
    void appendItem();
    void removeCompletedItems();

private:
    QVector<ToDoItem> mItems;
};

#endif // TODOLIST_H
