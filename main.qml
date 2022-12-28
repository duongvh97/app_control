import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import AppEnum 1.0

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("App Control")

    Label {
        id: titleControlPanel
        text: qsTr("Control Panel")
        font.pixelSize: 18
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 8
    }

    GroupBox {
        id: controlPanel
        label: titleControlPanel
        width: 300
        height: 700
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5

        GroupBox {
            id: grb1
            title: "Serial monitor"
            width: 280
            height: 100
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                id: showStatus
                width: 280
                height: 16
                wrapMode: Text.WrapAnywhere
                text: SerialPort.message
            }
            Text {
                id: showDataResp
                width: 280
                height: 80
                wrapMode: Text.WrapAnywhere
                anchors {
                    top: showStatus.bottom
                    topMargin: 5
                }
                text: SerialPort.dataResponse
            }
        }
    }

    GroupBox {
        id: connectBox
        title : "Setup"
        width: 280
        height: 165
        anchors {
            top: controlPanel.top
            topMargin: 150
            horizontalCenter: controlPanel.horizontalCenter
        }

        Column {
            spacing: 10
            Row {
                Text {
                    text: "Status: "
                    anchors.verticalCenter: parent.verticalCenter
                }

                Rectangle {
                    width: 20
                    height: 20
                    radius: 10
                    color: SerialPort.isPortOpened? "green" : "red"
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
            Row {
                spacing: 5
                ComboBox {
                    id: boxPortList
                    anchors.verticalCenter: parent.verticalCenter
                    width: 123
                    model: SerialPort.portList
                    focus: true
                    onActivated: {
                        SerialPort.portName = currentText
                    }
                    onCurrentTextChanged: {
                        SerialPort.closeSerialPort()
                        SerialPort.message = "Connect serial port again!"
                    }
                }
                ComboBox {
                    id: boxBaudRateList
                    anchors.verticalCenter: parent.verticalCenter
                    width: 123
                    model: ["115200", "57600", "9600"]
                    focus: true
                    onActivated: {
                        SerialPort.baudRate = parseInt(currentText)
                    }
                    onCurrentTextChanged: {
                        SerialPort.closeSerialPort()
                        SerialPort.message = "Connect serial port again!"
                    }
                }
            }
            Row {
                spacing: 5
                Button {
                    width: 123
                    text: SerialPort.isPortOpened? "Disconnect" : "Connect"
                    onClicked: {
                        if(SerialPort.isPortOpened) {
                            SerialPort.closeSerialPort()
                            SerialPort.message = "Disconnect serial port"
                        }
                        else {
                            SerialPort.openSerialPort(SerialPort.portName, SerialPort.baudRate)
                            SerialPort.message = "Connected: " + SerialPort.portName + " baudrate: " + SerialPort.baudRate
                        }
                    }
                }
                Button {
                    width: 123
                    text: "Scan port"
                    onClicked: {
                        SerialPort.closeSerialPort()
                        SerialPort.scanSerialPort()
                        SerialPort.message = "Scan serial port";
                    }
                }
            }
        }
    }

    GroupBox {
        id: gridButton
        title : "Button Control"
        width: 280
        height: 370
        anchors {
            top: connectBox.bottom
            topMargin: 5
            horizontalCenter: controlPanel.horizontalCenter

        }
        Grid {
            id: motorBtn
            columns: 3
            spacing: 5
            Button{
                width: 80
                text: "SPEED 1"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_SET_MOTOR_SPEED_1)
                    }
                }
            }
            Button{
                width: 80
                text: "SPEED 2"
                onClicked: {
                    if(SerialPort.isPortOpened){
                        SerialPort.sendData(AppEnum.CMD_SET_MOTOR_SPEED_2)
                    }
                }
            }
            Button{
                width: 80
                text: "SPEED 3"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_SET_MOTOR_SPEED_3)
                    }
                }
            }
            Button{
                width: 80
                text: "SPEED 4"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_SET_MOTOR_SPEED_4)
                    }
                }
            }
        }
        Button{
            width: 165
            text: "TURN OFF MOTOR"
            anchors.bottom: motorBtn.bottom
            anchors.left: motorBtn.left
            anchors.leftMargin: 85
            onClicked: {
                if(SerialPort.isPortOpened) {
                    SerialPort.sendData(AppEnum.CMD_TURN_OFF_ALL_MOTOR)
                }
            }
        }

        Row {
            id: fanBtn
            spacing: 5
            anchors.top: motorBtn.bottom
            anchors.topMargin: 15
            Button {
                width: 123
                text: "TURN OFF FAN"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_TURN_OFF_FAN)
                    }
                }
            }
            Button {
                width: 123
                text: "TURN ON FAN"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_TURN_ON_FAN)
                    }
                }
            }
        }

        Row {
            id: lightBtn
            spacing: 5
            anchors.top: fanBtn.bottom
            anchors.topMargin: 15
            Button {
                width: 123
                text: "TURN OFF LIGHT"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_TURN_OFF_WARM_LIGHT)
                    }
                }
            }
            Button {
                width: 123
                text: "TURN ON LIGHT"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_TURN_ON_WARM_LIGHT)
                    }
                }
            }
        }

        Row {
            id: timerBtn
            spacing: 5
            anchors.top: lightBtn.bottom
            anchors.topMargin: 15
            Button {
                width: 123
                text: "TIMER"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_SET_TIME_OUT)
                    }
                }
            }
            Button {
                width: 123
                text: "GET STATUS"
                onClicked: {
                    if(SerialPort.isPortOpened) {
                        SerialPort.sendData(AppEnum.CMD_REPORT_STATE)
                    }
                }
            }
        }

        Button {
            id: turnOffDevice
            text: "TURN OFF DEVICE"
            anchors.top: timerBtn.bottom
            anchors.topMargin: 15
            width: 254
            height: 60
            onClicked: {
                if(SerialPort.isPortOpened) {
                    SerialPort.sendData(AppEnum.CMD_TURN_OFF_ALL)
                }
            }
        }
    }
    /*****************************/
    Label {
        id: titleCamera
        text: qsTr("Camera")
        font.pixelSize: 18
        anchors {
            top: titleControlPanel.top
            left: showCamera.left
        }
    }
    GroupBox {
        id: showCamera
        label: titleCamera
        height: 700
        width: 1280 - controlPanel.width - 5 - 10
        anchors {
            bottom: controlPanel.bottom
            left: controlPanel.right
            leftMargin: 5
        }
    }

    Component.onCompleted: {
        SerialPort.portName = boxPortList.currentText
        SerialPort.baudRate = parseInt(boxBaudRateList.currentText)
    }
}
