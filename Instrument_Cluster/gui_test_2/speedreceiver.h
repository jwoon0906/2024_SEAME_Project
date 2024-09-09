#ifndef SPEEDRECEIVER_H
#define SPEEDRECEIVER_H

#include <QObject>
#include <QUdpSocket>

class SpeedReceiver : public QObject {
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue NOTIFY speedValueChanged)

public:
    SpeedReceiver(QObject *parent = nullptr);
    int speedValue() const;

signals:
    void speedValueChanged();

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    int m_speed;
};

#endif  // SPEEDRECEIVER_H
