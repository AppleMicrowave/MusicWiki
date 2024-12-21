import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic

Page {
    id: subListPage
    title: "Instrument List"

    property var dbManager: null

    function applyFilters() {
        let searchText = searchField.text || "";
        let property = propertyBox.currentText === "--Без фильтра--" ? "" : propertyBox.currentText;
        let variant = variantBox.currentText || "";
        let filter = filterBox.currentText || "";

        if (searchText === "" && property === "" && variant === "" && filter === "") {
            dbManager.itemModel.setItems(dbManager.itemModel.originalItems);
        } else {
            dbManager.itemModel.filterItems(searchText, property, variant, filter);
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "#FF7F7F"

        Column {
            height: 600
            spacing: 10
            anchors.fill: parent
            anchors.margins: 20

            Row {
                spacing: 10
                leftPadding: 40

                TextField {
                    id: searchField
                    placeholderText: "Поиск..."
                    width: 200
                    height: 31
                    font.pixelSize: 16

                    onTextChanged: applyFilters();
                }

                ComboBox {
                    id: filterBox
                    width: 150
                    height: 30
                    model: ["Название", "Вендер"]
                    onCurrentTextChanged: applyFilters();
                }

                ComboBox {
                    id: propertyBox
                    width: 150
                    height: 30
                    model: ["--Без фильтра--", "Тип", "Вид"]
                    onCurrentTextChanged: {
                        if (currentText === "--Без фильтра--") {
                            variantBox.model = [];
                        } else {
                            variantBox.model = dbManager.itemModel ? dbManager.itemModel.getUniqueValues(currentText) : [];
                        }
                        applyFilters();
                    }
                }

                ComboBox {
                    id: variantBox
                    width: 150
                    height: 30
                    onCurrentTextChanged: applyFilters();
                }

                Switch {
                    id: favoriteSwitch
                    text: "Показывать только Избранные"
                    onToggled: {
                        if (favoriteSwitch.checked) {
                            dbManager.filterItemsByFavorites(true);
                        } else {
                            dbManager.filterItemsByFavorites(false);
                        }
                    }
                }

                Button {
                    id: returnToMenuBtn
                    anchors.verticalCenter: parent.verticalCenter
                    width: 100
                    height: 40
                    text: "Назад"
                    onClicked: stackView.pop()
                }
            }

            ScrollView {
                anchors.fill: parent
                anchors.topMargin: 60
                anchors.leftMargin: 40
                contentWidth: 1100
                contentHeight: 2000
                height: 700

                Flow {
                    width: 1200
                    spacing: 40
                    Repeater {
                        model: dbManager.itemModel ? dbManager.itemModel : []
                        delegate: Column {
                            property string imagePath: model.imagePath

                            Button {
                                id: itemButton
                                width: 190
                                height: 190
                                background: Rectangle {
                                    color: "#FFFFFF"
                                    border.color: "black"

                                    Image {
                                        anchors.fill: parent
                                        source: imagePath
                                        fillMode: Image.PreserveAspectFit
                                        cache: true // Включаем кеширование
                                    }
                                }

                                //text: model.name
                                onClicked: {
                                    stackView.push("ItemDetailsPage.qml", {
                                        itemData: {
                                            type: model.type,
                                            kind: model.kind,
                                            name: model.name,
                                            imagePath: model.imagePath,
                                            description: model.description,
                                            manufacturers: model.manufacturers,
                                            price: model.price
                                        }
                                    });
                                }
                            }

                            Text {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: model.name
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
