import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: itemDetailsPage
    title: itemData.name || "Детали инструмента"

    property var itemData: {}

    Column {
        anchors.fill: parent
        spacing: 20
        anchors.margins: 20

        // Название инструмента
        Text {
            text: itemData.name || "Название неизвестно"
            font.pixelSize: 30
            font.bold: true
            color: "black"
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Изображение инструмента
        Image {
            source: itemData.imagePath
            width: 400
            height: 400
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Описание
        Text {
            text: itemData.description || "Описание отсутствует"
            wrapMode: Text.WordWrap
            font.pixelSize: 18
            color: "gray"
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
        }

        // Производители
        Text {
            text: "Производители: " + (itemData.manufacturers ? itemData.manufacturers.join(", ") : "Не указано")
            wrapMode: Text.WordWrap
            font.pixelSize: 18
            color: "black"
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
        }

        // Цена
        Text {
            text: "Цена: " + (itemData.price || "Не указана") + " $."
            font.pixelSize: 20
            color: "green"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            text: "Назад"
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: stackView.pop()
        }
    }
}
