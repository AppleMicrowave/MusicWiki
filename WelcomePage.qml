import QtQuick 2.15
import QtQuick.Controls 2.0

Page {
    id: firstPage
    title: "First Page"

    Rectangle {
        id: frame
        anchors.fill: parent
        color: "#FF5F5F" // Цвет фона, похожий на ваш кадр

        // Текст "Music Wiki"
        Text {
            text: "Music\nWiki"
            anchors.left: parent.left
            anchors.leftMargin: 60
            anchors.top: parent.top
            anchors.topMargin: 40

            font.pixelSize: 128
            font.bold: true
            lineHeight: 0.8

            color: "black"
        }

        // Кнопка Search
        Rectangle {
            id: searchButton
            width: 150
            height: 150
            radius: 75
            color: "#4FD8D8" // Цвет кнопки
            border.color: "black"
            border.width: 2

            x: 700
            anchors.rightMargin: 60
            anchors.verticalCenter: parent.verticalCenter

            Text {
                text: "Search"
                anchors.centerIn: parent
                font.pixelSize: 18
                font.bold: true
                color: "black"
            }
            Rectangle {
                id: wave

                width: parent.width
                height: parent.height
                radius: 75

                color: "transparent"
                border.color: "#01a3a4"
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                onClicked: begin_animation.start()
            }
        }
        ParallelAnimation {
            id: begin_animation
            onFinished: stackView.push("SubListPage.qml", { "dbManager": dbManager })
            PropertyAnimation {
                target: wave
                property: "border.width"
                from: 3
                to: 0
                duration: 300
            }
            PropertyAnimation {
                target: wave
                property: "width"
                to: searchButton.width + 50
                duration: 250
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation {
                target: wave
                property: "height"
                to: searchButton.height + 50
                duration: 250
                easing.type: Easing.InOutQuad
            }
            PropertyAnimation {
                target: wave
                property: "opacity"
                from: 1
                to: 0
                duration: 300
            }
        }
        // Вертикальная линия, соединяющая кнопку
        Rectangle {
           width: 2
           color: "black"
           anchors.top: searchButton.top
           anchors.topMargin: -500
           anchors.horizontalCenter: searchButton.horizontalCenter
           height: 500
       }
    }

}
