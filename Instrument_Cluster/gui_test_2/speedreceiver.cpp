#include "speedreceiver.h"
#include <QDebug>

SpeedReceiver::SpeedReceiver(QObject *parent) : QObject(parent), m_speed(0), Q(1.0), R(1.0), P(2.0), K(0.0), x_est_last(0) {
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

        // UDP로 받은 데이터를 정수로 변환
        int measuredSpeed = datagram.toInt();

        // 칼만 필터 적용
        m_speed = applyKalmanFilter(measuredSpeed);

        emit speedValueChanged();  // QML에서 업데이트할 수 있도록 시그널
    }
}

// 칼만 필터 함수
int SpeedReceiver::applyKalmanFilter(int measuredSpeed) {
    // 예측 단계: P값 업데이트 (예측 오차 공분산 업데이트)
    P = P + Q;

    // 업데이트 단계: 칼만 이득(K) 계산
    K = P / (P + R);

    // 필터링된 값 계산
    int x_est = x_est_last + K * (measuredSpeed - x_est_last);

    // P값 업데이트 (오차 공분산 업데이트)
    P = (1 - K) * P;

    // 이번에 계산한 값을 다음에 사용할 추정값으로 저장
    x_est_last = x_est;

    return x_est;
}


//--------------------------------------
//#include "speedreceiver.h"
//#include <QDebug>

//SpeedReceiver::SpeedReceiver(QObject *parent) : QObject(parent), m_speed(0) {
//    udpSocket = new QUdpSocket(this);
//    udpSocket->bind(QHostAddress::LocalHost, 12345);  // Python에서 보낸 데이터를 받을 포트

//    connect(udpSocket, &QUdpSocket::readyRead, this, &SpeedReceiver::processPendingDatagrams);
//}

//int SpeedReceiver::speedValue() const {
//    return m_speed;
//}

//void SpeedReceiver::processPendingDatagrams() {
//    while (udpSocket->hasPendingDatagrams()) {
//        QByteArray datagram;
//        datagram.resize(udpSocket->pendingDatagramSize());
//        udpSocket->readDatagram(datagram.data(), datagram.size());

//        m_speed = datagram.toInt();
//        emit speedValueChanged();  // QML에서 업데이트할 수 있도록 시그널을 보냅니다.
//    }
//}
