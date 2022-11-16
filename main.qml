import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: root
    width: 840
    height: 480
    visible: true
    title: qsTr("BattleShips")

    readonly property int statusRowMargin : 30

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
        RowLayout
        {
            id: rowArea
            Button {
                id: startGameButton
                anchors
                {
                    topMargin: 5
                }
                height: 50
                width: 100
                background: Rectangle {
                    color: "LightGreen"
                }

                text: qsTr("Start BattleShip Sim")
                onClicked: dspl.startGame()
            }
            Text {
                height: 50
                width: 100

                id: winnerText
                text: dspl.someVar
            }
        }
    }

    Item {
        id: gameView
        height: root.height - statusRow.height - statusRowMargin
        anchors
        {
            top: statusRow.bottom
            margins: 10
        }
            Rectangle {
            id: rect1View
            width: root.width/2
            height: gameView.height
            border.color: "black"
            border.width: 2
            anchors
            {
                left: root.left
            }

                GridView {
                    id: gridView1
                    cellHeight: rect1View.width/10
                    cellWidth: rect1View.width/10
                    interactive: false
                    anchors
                    {
                        fill: rect1View
                    }
                    model: dspl.listInitiator

                    delegate: Rectangle {
                        id: delegate1Rect
                        border.color: tcolor
                        border.width: (tcolor === "blue") || (tcolor === "red")? 50 : 2
                        width: gridView1.cellWidth -2
                        height: gridView1.cellHeight -2
                        Text {
                            text: model.name
                            anchors
                            {
                                verticalCenter: delegate1Rect.verticalCenter
                                horizontalCenter: delegate1Rect.horizontalCenter
                            }
                        }
                    }
                }
            }

        Rectangle {
        id: rect2View
        width: root.width/2
        height: gameView.height
        border.color: "black"
        border.width: 2
        anchors
        {
            left: rect1View.right
        }

            GridView {
                id: gridView2
                cellHeight: rect2View.width/10
                cellWidth: rect2View.width/10
                interactive: false
                anchors
                {
                    fill: rect2View
                }
                model: dspl.listInitiated

                delegate: Rectangle {
                    id: delegate2Rect
                    border.color: tcolor
                    border.width: (tcolor === "blue") || (tcolor === "red")? 50 : 2
                    width: gridView2.cellWidth -2
                    height: gridView2.cellHeight -2
                    Text {
                        text: name
                        anchors
                        {
                            verticalCenter: delegate2Rect.verticalCenter
                            horizontalCenter: delegate2Rect.horizontalCenter
                        }
                    }
                }
            }
        }
    }
}
