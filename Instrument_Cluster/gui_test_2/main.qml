import QtQuick 2.7
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 1280
    height: 400
    visibility: Window.FullScreen

    // 속도계 배경 이미지
    Image {
        id: speedImage
        width: 1280
        anchors.centerIn: parent
        source: "qrc:/image/vintage_retro_classic.png"
    }

    property real speed: 0

    Image {
        id: needle
        source: "qrc:/image/needle_without_back.png"
        anchors.centerIn: parent
        anchors.verticalCenterOffset: 30
        anchors.horizontalCenterOffset: 0.5
        transform: Rotation {
            id: rotation
            origin.x: needle.width * 97 / 157
            origin.y: needle.height * 61 / 164
            angle: speedToAngle(speed)

            // Add behavior to the angle property directly inside Rotation
            Behavior on angle {
                NumberAnimation {
                    duration: 300  // Adjust this for the desired smoothness (300ms)
                    easing.type: Easing.InOutQuad  // Easing for smooth movement
                }
            }
        }
    }

    // 속도 값을 바늘의 각도로 변환하는 함수
    function speedToAngle(speed) {
        var minSpeed = 0;  // min speed
        var maxSpeed = 100;  // max speed
        var minAngle = 7;  // min angle of needle
        var maxAngle = 225;  // max angle of needle

        // speed to degree
        return minAngle + (speed - minSpeed) * (maxAngle - minAngle) / (maxSpeed - minSpeed);
    }

    // Simulating received speed data with smooth update
    Timer {
        interval: 100  // Update every 100ms (you can adjust this)
        running: true
        repeat: true
        onTriggered: {
            var newSpeed = speedReceiver.speedValue;  // Simulate new speed value between 0 and 240
            speed = newSpeed;  // Assign new speed
        }
    }
}

