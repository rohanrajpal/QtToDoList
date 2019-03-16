#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>

#include "todolist.h"
#include "todomodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    /*!
     * \brief qmlRegisterType<ToDoModel>
     * Registers the cpp model with qml type
     */
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");
    qmlRegisterUncreatableType<ToDoList>("ToDo",1,0,"ToDoList",
                                         QStringLiteral("ToDoList should not be created in QML"));
    ToDoList toDoList;


    QQmlApplicationEngine engine;
    /*!
      This is where the todolist is actually exposed to qml
      as a context property
      */
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"), &toDoList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
