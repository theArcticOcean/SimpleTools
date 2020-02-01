import QtQuick 2.0

Rectangle {
    border.color: "red"
    color: "transparent"
    focus: false

    property alias mouseArea: iMouseArea

    MouseArea
    {
        id: iMouseArea
        anchors.fill: parent
    }
}
