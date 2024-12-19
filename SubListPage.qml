import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: subListPage
    title: "Instrument List"

    Rectangle {
        anchors.fill: parent
        color: "#FF7F7F"

        Column {
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
                }
                ComboBox {
                    id: filterBox
                    anchors.verticalCenter: parent.verticalCenter
                    model: ["All", "Guitars", "Basses", "Violins"]
                    currentIndex: 0
                }
                Item {
                        width: 450 // Задаем отступ в 200 пикселей
                        height: 1 // Минимальная высота
                    }
                Text {
                    font.family: "MS Sans Serif"
                    font.bold: true
                    font.pointSize: 20
                    text: "Ударные"
                }
                Button {
                    id: returnToMenuBtn
                    anchors.verticalCenter: parent.verticalCenter
                    width: 50
                    height: 30
                    text: "Menu"
                    onClicked: stackView.pop()
                }
            }

            // Каркас для меню списка
            ScrollView {
                anchors.fill: parent
                anchors.topMargin: 60
                anchors.leftMargin: 40
                contentWidth: 1100
                contentHeight: 700

                Flow {
                    width: 1200
                    spacing: 40
                    Repeater {
                        model: 15
                        delegate: Column {
                            Button {
                                text: "Instrument " + (index + 1)
                                width: 190
                                height: 190
                            }
                            Text {
                                text: "Guitar_name"
                                anchors.horizontalCenter: parent.horizontalCenter
                            }
                        }
                    }
                }
            }
        }
    }
}
