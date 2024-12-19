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
                TextField {
                    id: searchField
                    placeholderText: "Search..."
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width * 0.8
                }
                ComboBox {
                    id: filterBox
                    model: ["All", "Guitars", "Basses", "Violins"]
                    currentIndex: 0
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
                        delegate: Button {
                            text: "Instrument " + (index + 1)
                            width: 190
                            height: 190
                        }
                    }
                }
            }
        }
    }
}
