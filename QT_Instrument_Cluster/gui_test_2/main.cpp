#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "speedreceiver.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // QML 엔진 및 C++ 객체(QML에서 사용할 SpeedReceiver) 설정
    QQmlApplicationEngine engine;
    SpeedReceiver speedReceiver;
    engine.rootContext()->setContextProperty("speedReceiver", &speedReceiver);

    // QML 파일 로드
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
