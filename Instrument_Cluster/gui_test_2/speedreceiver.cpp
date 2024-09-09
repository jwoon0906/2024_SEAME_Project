#include "speedreceiver.h"
#include <QDebug>

SpeedReceiver::SpeedReceiver(QObject *parent) : QObject(parent), m_speed(0) {
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, 12345);  // Python에서 보낸 데이터를 받을 포트

    connect(udpSocket, &QUdpSocket::readyRead, this, &SpeedReceiver::processPendingDatagrams);
}

int SpeedReceiver::speedValue() const {
    return m_speed;
}

void SpeedReceiver::processPendingDatagrams() {
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());

        // 수신된 데이터를 문자열에서 정수로 변환
        m_speed = datagram.toInt();
        emit speedValueChanged();  // QML에서 업데이트할 수 있도록 시그널을 보냅니다.
    }
}
