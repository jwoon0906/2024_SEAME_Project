#ifndef SPEEDRECEIVER_H
#define SPEEDRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class SpeedReceiver : public QObject {
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue NOTIFY speedValueChanged)  // QML에 속성 등록

public:
    explicit SpeedReceiver(QObject *parent = nullptr);
    int speedValue() const;

signals:
    void speedValueChanged();

public slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    int m_speed;

    // 칼만 필터 변수들
    float Q;  // Process noise covariance
    float R;  // Measurement noise covariance
    float P;  // Estimation error covariance
    float K;  // Kalman gain
    float x_est_last;  // Last estimated value

    // 칼만 필터 함수
    int applyKalmanFilter(int measuredSpeed);
};

#endif // SPEEDRECEIVER_H

//------------

//#ifndef SPEEDRECEIVER_H
//#define SPEEDRECEIVER_H

//#include <QObject>
//#include <QUdpSocket>

//class SpeedReceiver : public QObject {
//    Q_OBJECT
//    Q_PROPERTY(int speedValue READ speedValue NOTIFY speedValueChanged)

//public:
//    SpeedReceiver(QObject *parent = nullptr);
//    int speedValue() const;

//signals:
//    void speedValueChanged();

//private slots:
//    void processPendingDatagrams();

//private:
//    QUdpSocket *udpSocket;
//    int m_speed;
//};

//#endif  // SPEEDRECEIVER_H
