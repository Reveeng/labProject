import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import SerialApi 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ComboBox{
        model: SerialInfoModel
        delegate: ItemDelegate{
            width: control.width
            text: modelData.text
            enabled: modelData.enabled
        }
    }
}
