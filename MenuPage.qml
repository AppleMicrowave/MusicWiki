import QtQuick 2.15
import QtQuick.Controls 2.0
import QtQuick.Controls.TreeView

Page {
    id: secondPage
    title: "Instrument Database"

    Column {
        spacing: 10
        anchors.fill: parent
        anchors.margins: 20

        // Поле для фильтрации
        TextField {
            id: filterField
            placeholderText: "Type to filter..."
            onTextChanged: treeView.search(text)
        }

        // TreeView для отображения данных
        TreeView {
            id: treeView
            anchors.fill: parent

            // Пример колонок
            model: ListModel {
                ListElement { name: "Guitar"; type: "String"; price: "400$" }
                ListElement { name: "Piano"; type: "Keyboard"; price: "1500$" }
                ListElement { name: "Drums"; type: "Percussion"; price: "800$" }
            }

            TableViewColumn {
                role: "name"
                title: "Name"
                width: 200
            }

            TableViewColumn {
                role: "type"
                title: "Type"
                width: 150
            }

            TableViewColumn {
                role: "price"
                title: "Price"
                width: 100
            }
        }

        // Кнопка для возврата на предыдущую страницу
        Button {
            text: "Go Back"
            onClicked: stackView.pop()
        }
    }
}
