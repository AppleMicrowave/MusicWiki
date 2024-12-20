import QtQuick 2.15
import QtQuick.Controls 2.0

Page {
    id: firstPage
    title: "First Page"

    Rectangle {
        id: welcome

        anchors.centerIn: parent
        width: 200
        height: 100
        color: "lightblue"
        border.color: "black"
        border.width: 1

        Text {
            anchors.centerIn: parent
            text: "Music Wiki"
            font.pixelSize: 20
        }
    }

    Button {
        text: ""
        anchors.left: welcome.left
        width: 400
        height: 200

        onClicked: stackView.push("SubListPage.qml", { "dbManager": dbManager })
    }
}
