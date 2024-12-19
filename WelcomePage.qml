import QtQuick 2.15
import QtQuick.Controls 2.0

Page {
    id: firstPage
    title: "First Page"

    Rectangle {
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
        text: "Go to Second Page"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        onClicked: stackView.push("MenuPage.qml")
    }
}
