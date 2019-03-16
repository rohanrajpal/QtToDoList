import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import ToDo 1.0
ColumnLayout{
    /*
      Frame is used to layout a
      logical group of controls together
      */
    Frame{
        /*
          ListView needs the following params

          -size
            determines the area that'll come
          -model
          -delegate

          Listview model is the source of the data
          it uses to create items

          */
        ListView{
            /*
            implicit are natural sizes of item
            they are the default width and height
            if none are specified
            */
            implicitWidth: 250
            implicitHeight: 250
            /*
            this ensure any object outside the
            view wont be deleted
            */
            clip: true
            anchors.fill: parent

            /*!
              Can be a js array, cpp model
              or a qml model
              */
            model: ToDoModel {
                list: toDoList
            }
            /*!
            model: ListModel {
                        ListElement {
                        each element is called a role, it indicates
                        to the model which type of data is being
                        referred to

                            done: true
                            description: "Wash the car"
                        }
                        ListElement {
                            done: false
                            description: "Fix the sink"
                        }
                    }
            */

            /*
              gives a template on how
              each list item is going to look
              */
            delegate: RowLayout {

                width:parent.width

                CheckBox {
                    //this connects the model data
                    // to the layout
                    // model tells where the properties
                    // come from
                    checked: model.done
                    /*
                      Onclicked changes the value of the model
                    */
                    onClicked: model.done = checked
                }
                TextField {
                    text: model.description
                    /*
                      */
                    onEditingFinished: model.description = text
                    /*
                      Layout attach type ensures the
                      text field takes as much horizontal
                      space as possible
                    */
                    Layout.fillWidth: true
                }
            }

        }
    }

    RowLayout{
        Button{
            text: qsTr("Add new item")
            onClicked: toDoList.appendItem()
            Layout.fillWidth: true
        }
        Button{
            text: qsTr("Remove completed")
            onClicked: toDoList.removeCompletedItems()
            Layout.fillWidth: true
        }
    }
}
