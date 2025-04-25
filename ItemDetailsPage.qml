import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Page {
    id: detailsPage
    title: "Item Details"

    property var itemData: {}

    // Основной макет страницы
    Rectangle {
        anchors.fill: parent
        color: "#FF5F5F"

        // Макет содержимого
        Row {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 70
            width: 300

            // Изображение инструмента
            Rectangle {
                width: parent.width / 3
                height: parent.height - 40
                color: "white"
                border.color: "black"
                border.width: 5

                Image {
                    anchors.fill: parent
                    anchors.margins: 20
                    source: itemData.imagePath // Замените на путь к изображению
                    fillMode: Image.PreserveAspectFit
                }
            }

            // Описание инструмента
            ColumnLayout {
                spacing: 50
                Layout.maximumWidth: 200

                Text {
                    text: "Тип: " + itemData.type
                    font.pixelSize: 24
                    font.bold: true
                    color: "black"
                }

                Text {
                    text: "Вид: " + itemData.kind
                    font.pixelSize: 24
                    font.bold: true
                    color: "black"
                }

                Text {
                    text: "Наименование: " + itemData.name
                    font.pixelSize: 24
                    font.bold: true
                    color: "black"
                }

                Text {
                    text: "Цена: ~" + itemData.price
                    font.pixelSize: 24
                    font.bold: true
                    color: "black"
                }

                Text {
                    wrapMode: Text.WordWrap
                    maximumLineCount: 3
                    text: "Описание: " + itemData.description
                    Layout.preferredWidth: 600
                    font.pixelSize: 24
                    font.bold: true
                    color: "black"
                }

                Text {
                    text: "Крупные производители: " + itemData.manufacturers
                    font.pixelSize: 24
                    font.bold: true
                    color: "black"
                }
            }
        }

        // Кнопки внизу
        Row {
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20
            bottomPadding: 60
            //margins: 20

            Button {
                text: "+"
                font.pixelSize: 64
                width: 100
                height: 50
                onClicked: {
                    dbManager.addItemToFavorites(itemData.name) // Метод для добавления в избранное
                    favoriteDialog.open() // Показываем сообщение
                }
            }

            Button {
                text: "⟳"
                font.pixelSize: 64
                width: 100
                height: 50
                onClicked: stackView.pop() // Возврат в меню
            }

            Button {
                text: "-"
                font.pixelSize: 64
                width: 100
                height: 50
                onClicked: {
                    dbManager.removeItemFromFavorites(itemData.name) // Метод для удаления из избранного
                    removeDialog.open() // Показываем сообщение
                }
            }
        }
    }

    // Диалог успешного добавления
    Dialog {
        id: favoriteDialog
        modal: true
        title: "Уведомление"

        Text {
            text: "Элемент добавлен в избранное!"
            font.pixelSize: 16
        }

        footer: Button {
            text: "OK"
            width: 150
            height: 50
            onClicked: favoriteDialog.close()
        }
        standardButtons: Dialog.Ok
    }

    // Диалог успешного удаления
    Dialog {
        id: removeDialog
        modal: true
        title: "Уведомление"

        Text {
            text: "Элемент удалён из избранного!"
            font.pixelSize: 16
        }

        footer: Button {
            text: "OK"
            onClicked: removeDialog.close()
        }
        standardButtons: Dialog.Ok
    }
}
