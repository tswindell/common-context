import QtQuick 2.5
import QtQuick.Window 2.2

import human.components 0.1

Window {
    id:main
    visible:true

    width:480
    height:852

    Component.onCompleted: {
    }

    StateObject {
        id: object1

        properties: [
            StateProperty {
                name: "p1"
                type: "string"
                object: "Hello, world"
            },

            StateProperty {
                name: "p2"
                type: "number"
                object: 12
            },

            StateProperty {
                name: "p3"
                type: "object"
                object: StateObject {}
            }
        ]
    }

    ListView {
        id: listview
        anchors.fill: parent
        model: object1.properties
        delegate: Item {
            width: parent.width
            height: 72
            Text {
                anchors.centerIn: parent
                text: '' + model.object
            }
        }
    }
}
