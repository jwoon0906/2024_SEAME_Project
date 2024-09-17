#include "canreceiver.h"
#include <QCanBus>
#include <QDebug>

CanReceiver::CanReceiver(QObject *parent) : QObject(parent), canDevice(nullptr)
{
    // 사용 가능한 CAN 버스 드라이버 확인
    if (!QCanBus::instance()->plugins().contains(QStringLiteral("socketcan"))) {
        qDebug() << "socketcan 플러그인이 없습니다. 확인해 주세요.";
        return;
    }

    // CAN 버스 장치 열기
    canDevice = QCanBus::instance()->createDevice(QStringLiteral("socketcan"), QStringLiteral("can0"));
    if (!canDevice) {
        qDebug() << "CAN 장치를 열 수 없습니다.";
        return;
    }

    // CAN 장치 시작
    if (!canDevice->connectDevice()) {￣
        qDebug() << "CAN 장치 연결 실패:" << canDevice->errorString();
        delete canDevice;
        canDevice = nullptr;
        return;
    }

    // CAN 데이터가 들어올 때마다 메시지를 수신하도록 슬롯 연결
    connect(canDevice, &QCanBusDevice::framesReceived, this, &CanReceiver::processFrames);

    qDebug() << "CAN 장치가 성공적으로 시작되었습니다.";
}

CanReceiver::~CanReceiver()
{
    if (canDevice) {
        canDevice->disconnectDevice();
        delete canDevice;
    }
}

void CanReceiver::processFrames()
{
    while (canDevice->framesAvailable()) {
        const QCanBusFrame frame = canDevice->readFrame();
        qDebug() << "CAN 메시지 수신:" << frame.toString();
        // 여기서 frame.data()를 처리할 수 있습니다.
    }
}
