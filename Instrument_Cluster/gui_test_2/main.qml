import QtQuick 2.7
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 1280
    height: 400
    visibility: "FullScreen"

    // 속도계 배경 이미지
    Image {
        id: speedImage
        width: 1280
        anchors.centerIn: parent
        source: "qrc:/image/vintage_retro_classic.png"
    }

    property real speed: 0

    property real estimatedSpeed: 0
    property real estimationError: 1
    property real processNoise: 0.125  // 프로세스 노이즈
    property real measurementNoise: 2.0 // 측정 노이즈



//    Text {
//        id: myText
//        text: "smooth_500_40_speed 160"  // 표시할 텍스트
//        font.pointSize: 24   // 폰트 크기 설정
//        color: "black"       // 텍스트 색상
//        anchors.centerIn: parent  // 부모 요소의 가운데에 위치
//    }

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
//                NumberAnimation {
//                    duration:1200  // Adjust this for the desired smoothness (300ms)
//                    easing.type: Easing.InOutQuad  // Easing for smooth movement
//                }
//                SpringAnimation{
//                    spring : 0.8
//                    damping : 0.3
//                    epsilon: 0.01
//                    duration: 1500
//                }
                SmoothedAnimation{
                    duration: 500
                    velocity: 40
                }
            }
        }
    }


    function speedToAngle(sp) {
        var minSpeed = 0;  // min speed
        var maxSpeed = 160;  // max speed
        var minAngle = 7;  // min angle of needle
        var maxAngle = 225;  // max angle of needle
        if (sp < minSpeed){
            sp = minSpeed;
        }else if(sp > maxSpeed){
            sp = maxSpeed;
        }

        // speed to degree
        //return minAngle + (speed - minSpeed) * (maxAngle - minAngle) / (maxSpeed - minSpeed);
        return (sp - minSpeed) * (maxAngle - minAngle) / (maxSpeed - minSpeed) + minAngle;
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

