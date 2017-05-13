#ifndef PORT_H
#define PORT_H

#include <QObject>
#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

class port : public QSerialPort
{

    Q_OBJECT
public:
    port();
    void PortScan();
    QList<QSerialPortInfo> PortInfo;
    bool OpenPort();
    struct
    {
        QString portname;
        char baud;
        char Data;
        char stopbit;
        char parity;
    }settings;

private:


};

extern port Port;
#endif // PORT_H
