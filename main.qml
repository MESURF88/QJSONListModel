import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Window {
    id: root
    width: 840
    height: 480
    visible: true
    title: qsTr("JSONViews")

    readonly property int statusRowMargin : 30
    property string jsonRawFeed: ""
    property int buttonInterrupt: 0
    Item
    {
        id: bodySection
        width: parent.width
        height: 300

        Column{
        Button
        {
            id: btn1
            height: 30
            width: 100
            text: "show json"
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    console.log("sample JSON two books...");
                    jsonRawFeed = "{ \"store\": {\"book\": [ { \"title\": \"Harry Potter and the Goblet of Fire\" }, {\"title\": \"Anders Game\"} ] } }";
                    buttonInterrupt = buttonInterrupt? 0 : 1;
                }

            }

        }

        Button
        {
            id: btn2
            height: 30
            width: 100
            text: "start timer"
            MouseArea{
                anchors.fill: parent
                onPressed: {
                    dspl.startGame();
                }

            }

        }

        ListView {
                    id: list1
                    width: parent.width
                    height: 200


                    JSONListModel {
                        id: jsonModel1
                        //source: "tmp.txt"
                        json: buttonInterrupt? jsonRawFeed : dspl.jsonStringRaw;

                        query: "$.store.book[*]"
                    }
                    model: jsonModel1.model
                    delegate: Rectangle {
                        id: currView
                        height: 30
                                    Text {
                                        width: parent.width
                                        horizontalAlignment: Text.AlignLeft
                                        font.pixelSize: 14
                                        color: "black"
                                        text: model.title
                                    }
                    }
        }
        }
    }
}
