import QtQuick 2.7
import QtQuick.Controls 2.2

ApplicationWindow {
    visible: true
    width: 900
    height: 400
    title: qsTr("Speedometer")

    // 속도계 배경 이미지
    Image {
        id: backgroundImage
        width: 900
        height: 400
        anchors.fill: parent
        source: "image/back.png" // Replace with the path to your background image
    }
    Image {
        id: speedImage
        width: 874
        height: 365
        anchors.centerIn: parent
        source: "qrc:/image/dial3.png"

        // 속도계 배경 이미지 경로
    }

    Canvas {
        id: speedPointer
        width: 300
        height: 300
        anchors.centerIn: parent

        onPaint: {
            var ctx = getContext("2d");
            var centerX = width / 2;
            var centerY = height / 2 - 7;

            ctx.clearRect(0, 0, width, height);

            var angle = ((speedReceiver.speedValue +1) / 180) * 180 - 180;  // 최고속도 240
            ctx.save();
            ctx.translate(centerX, centerY);
            ctx.rotate(angle * Math.PI / 180);
            ctx.beginPath();
            ctx.moveTo(0, 0);
            ctx.lineTo(0, -100);
            ctx.lineWidth = 5;
            ctx.strokeStyle = "#FFFFFF";
            ctx.stroke();
            ctx.restore();
        }

        // speedValue 값이 변경될 때마다 바늘을 다시 그립니다.
        Connections {
            target: speedReceiver
            onSpeedValueChanged: speedPointer.requestPaint()
        }
    }
}
