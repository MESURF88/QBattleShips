import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import gbt 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("BattleShips")

    Item
    {
        id: statusRow
        width: parent.width
        height: 30
        anchors
        {
            horizontalCenter: root.horizontalCenter
            top: root.top
        }
        Button {
            id: startGameButton
            anchors
            {
                centerIn: statusRow
                topMargin: 5
            }
            height: 30
            width: 100
            background: Rectangle {
                color: "LightGreen"
            }

            text: qsTr("Start BattleShip Sim")
            onClicked: dspl.startGame()
        }
    }

    Item {
        id: gameView
        anchors
        {
            top: statusRow.bottom
            margins: 10
        }

        Rectangle {
        id: rect1View
        width: cpu1view.width
        height: cpu1view.height
        border.color: "black"
        border.width: 2
        anchors {
            left: root.left
        }
            Column
            {
                id: cpu1view
                width: root.width/2
                height: root.height - statusRow.height - 10
                anchors {
                    margins: 5
                }
                Row{
                    Text {
                        text: "CPU1 here"
                    }
                }
                Row{
                    GridView
                    {

                    }
                }
            }
        }
        Rectangle {
        id: rect2View
        width: cpu2view.width
        height: cpu2view.height
        border.color: "black"
        border.width: 2
        anchors {
            left: rect1View.right
        }
            Column
            {
                id: cpu2view
                width: root.width/2
                height: root.height - statusRow.height - 10
                anchors {
                    margins: 5
                }
                Row {

                    Text {
                        text: "CPU2 here"
                    }
                }
                GridView {
                    id: gridView
                    width: cpu2view.width/4
                    height: cpu2view.height/4
                    model: GameBoardTest {}

                    delegate: RowLayout {
                        width: gridView.width

                        TextField {
                            text: model.name

                            Layout.preferredWidth: 1
                            Layout.fillWidth: true

                            onAccepted: model.name = text
                        }
                    }
                }

                }
            }
        }

}
