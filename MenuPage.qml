import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: menuPage
    title: "Main Menu"

    Rectangle {
        anchors.fill: parent
        color: "#FF7F7F"

        Column {
            anchors.centerIn: parent
            spacing: 20

            Row {
                spacing: 20
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    text: "Ударные"
                    width: 250
                    height: 400
                }

                Button {
                    text: "Струнные"
                    width: 250
                    height: 400
                    onClicked: stackView.push("SubListPage.qml")
                }


                Button {
                    text: "Клавишные"
                    width: 250
                    height: 400
                }

                Button {
                    text: "Духовые"
                    width: 250
                    height: 400
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                Button {
                    text: "Избранное"
                    width: 1060
                    height: 120
                }
            }
        }
    }
}
