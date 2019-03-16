#ifndef TODOMODEL_H
#define TODOMODEL_H

#include <QAbstractListModel>
class ToDoList;

class ToDoModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(ToDoList *list READ list WRITE setList)

public:
    explicit ToDoModel(QObject *parent = nullptr);
    /*
     * roles are defined here
     */
    enum {
        DoneRole = Qt::UserRole,
        DescriptionRole
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    /*!
     * virtual means that the function will be overriden
     * const means if a const class created its members cant
     * be changed
     * override means this function is overriding
     */
    virtual QHash<int, QByteArray> roleNames() const override;
    ToDoList *list() const;
    void setList(ToDoList *list);

private:
    ToDoList *mList;
};

#endif // TODOMODEL_H
