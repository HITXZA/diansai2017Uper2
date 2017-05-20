#include "port.h"
#include <QMessageBox>
#include <QDebug>

port::port()
{
    this->position=5;
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
    qDebug()<<data;
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
    this->position++;
    if(this->position>10)
        this->position=10;

    QByteArray a;
    a.resize(3);
    a[0]=0x0c;
    a[1]=0x04;
    a[2]=this->position;
    Port.SaveWrite(a);
}

void port::distanceMinusSlot()
{
    this->position--;
    if(this->position<=0)
        this->position=0;

    QByteArray a;
    a.resize(3);
    a[0]=0x0c;
    a[1]=0x04;
    a[2]=this->position;
    Port.SaveWrite(a);
}

void port::AngleSlot(int angle)
{
    QByteArray a;
    a.resize(2);
    a[0]=0x0b;
    a[1]=angle;
    Port.SaveWrite(a);
}

void port::PSlot(unsigned char P)
{
    QByteArray a;
    a.resize(3);
    a[0]=0x0c;
    a[1]=0;
    a[2]=P;

    Port.SaveWrite(a);
}

void port::ISlot(unsigned char I)
{
    QByteArray a;
    a.resize(3);
    a[0]=0x0c;
    a[1]=1;
    a[2]=I;

    Port.SaveWrite(a);
}

void port::DSlot(unsigned char D)
{
    QByteArray a;
    a.resize(3);
    a[0]=0x0c;
    a[1]=2;
    a[2]=D;

    Port.SaveWrite(a);
}

port Port;
