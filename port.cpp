#include "port.h"
#include <QMessageBox>
#include <QDebug>

port::port()
{
    this->PortInfo.clear();                                  //先清除列表
    this->PortInfo=QSerialPortInfo::availablePorts();        //读取串口信息
}

bool port::OpenPort()
{
    if(this->isOpen())
    {
        return true;
    }

    this->setPortName(this->settings.portname);
    this->open(QIODevice::ReadWrite);

    switch(this->settings.baud)
    {
    case 0:
        this->setBaudRate(QSerialPort::Baud9600);
        break;
    case 1:
        this->setBaudRate(QSerialPort::Baud19200);
        break;
    case 2:
        this->setBaudRate(QSerialPort::Baud38400);
        break;
    case 3:
        this->setBaudRate(QSerialPort::Baud57600);
        break;
    case 4:
        this->setBaudRate(QSerialPort::Baud115200);
        break;
    }

    switch(this->settings.Data)
    {
    case 0:
        this->setDataBits(QSerialPort::Data8);
        break;
    case 1:
        this->setDataBits(QSerialPort::Data7);
        break;
    case 2:
        this->setDataBits(QSerialPort::Data6);
        break;
    case 3:
        this->setDataBits(QSerialPort::Data5);
        break;
    }

    switch(this->settings.stopbit)
    {
    case 0:
        this->setStopBits(QSerialPort::OneStop);
        break;
    case 1:
        this->setStopBits(QSerialPort::TwoStop);
        break;
    }

    switch(this->settings.parity)
    {
    case 0:
        this->setParity(QSerialPort::NoParity);
        break;
    case 1:
        this->setParity(QSerialPort::OddParity);
        break;
    case 2:
        this->setParity(QSerialPort::EvenParity);
        break;
    }

    if(!this->isOpen())
    {
        return false;
    }
    return true;
}

void port::PortScan()
{
    this->PortInfo.clear();                                  //先清除列表
    this->PortInfo=QSerialPortInfo::availablePorts();        //读取串口信息
}

void port::SaveWrite(QByteArray &data)
{
    if(!Port.isOpen())
    {
        QMessageBox a;
        a.setIcon(QMessageBox::Information);
        a.setWindowTitle("请打开串口");
        a.setText("串口可能未打开");
        a.show();
        a.exec();
        return;
    }
    Port.write(data);
}

void port::SaveWrite(char *data)
{
    if(!Port.isOpen())
    {
        QMessageBox a;
        a.setIcon(QMessageBox::Information);
        a.setWindowTitle("请打开串口");
        a.setText("串口可能未打开");
        a.show();
        a.exec();
        return;
    }
    Port.write(data);
}

void port::DistanceAddSlot()
{
    QByteArray a;
    a.resize(4);
    a[0]=0x01;
    a[1]=~0x01;
    a[2]=~0x01;
    a[3]=0x01;
    Port.SaveWrite(a);
}

void port::distanceMinusSlot()
{
    QByteArray a;
    a.resize(4);
    a[0]=0x02;
    a[1]=~0x02;
    a[2]=~0x02;
    a[3]=0x02;
    Port.SaveWrite(a);
}

void port::AngleSlot(int angle)
{
    QByteArray a;
    a.resize(5);
    a[0]=0x03;
    a[1]=~0x03;
    a[2]=angle;
    a[3]=~0x03;
    a[4]=0x03;
    Port.SaveWrite(a);
}

void port::PIDSlot(float P, float I, float D)
{
    union send
    {
        unsigned char a[12];
        float PID[3];
    }Send;
    Send.PID[0]=P;
    Send.PID[1]=I;
    Send.PID[2]=D;
    QByteArray a;
    a.resize(16);
    a[0]=0x05;
    a[1]=~0x05;
    for(int i=2;i<14;i++)
    {
        a[i]=Send.a[i-2];
    }
    a[14]=~0x05;
    a[15]=0x05;
    qDebug()<<a;
    Port.SaveWrite(a);
}

port Port;
