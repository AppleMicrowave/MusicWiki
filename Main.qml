import QtQuick 2.15
import QtQuick.Controls 2.0

ApplicationWindow {
    visible: true
    width: 1300
    height: 700
    title: "Music Wiki"

    StackView {
        id: stackView
        anchors.fill: parent

        Component.onCompleted: stackView.push("WelcomePage.qml")
    }
}
