import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: subListPage
    title: "Instrument List"

    Rectangle {
        anchors.fill: parent
        color: "#FF7F7F"

        Column {
            height: 600
            spacing: 10
            anchors.fill: parent
            anchors.margins: 20

            // Поле поиска
            Row {
                spacing: 10
                leftPadding: 40
                TextField {
                    id: searchField
                    placeholderText: "Search..."
                    anchors.verticalCenter: parent.verticalCenter
                    width: 400

                    onTextChanged: {
                        if (dbManager.itemModel) {
                            dbManager.itemModel.filterItemsFromQml(searchField.text);
                        }
                    }
                }
                ComboBox {
                    id: filterBox
                    anchors.verticalCenter: parent.verticalCenter
                    model: ["All", "Guitars", "Basses", "Violins"]
                    currentIndex: 0
                }
                Item {
                        width: 550
                        height: 1
                    }
                // Text {
                //     id: category_name
                //     font.family: "Century Schoolbook"
                //     font.bold: true
                //     font.pointSize: 20
                //     text: "" + dbManager.itemModel.category
                // }
                Button {
                    id: returnToMenuBtn
                    anchors.verticalCenter: parent.verticalCenter
                    width: 100
                    height: 40
                    text: "Назад"
                    onClicked: stackView.pop()
                }
            }

            // Каркас для меню списка
            ScrollView {
                anchors.fill: parent
                anchors.topMargin: 60
                anchors.leftMargin: 40
                contentWidth: 1100
                contentHeight: 750
                height: 700

                Flow {
                    width: 1200
                    spacing: 40
                    Repeater {
                        model: dbManager.itemModel ? dbManager.itemModel : []
                        delegate: Column {
                            Button {
                                text: model.name // Используем роль "name"
                                width: 190
                                height: 190
                            }
                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: model.kind + " " + model.name
                                horizontalAlignment: Text.AlignHCenter
                                font.pointSize: 8

                                wrapMode: Text.WordWrap
                                width: parent.width
                            }
                        }
                    }
                }
            }
        }
    }
}
