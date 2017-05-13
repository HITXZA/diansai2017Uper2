#include "debugwindow.h"
#include "ui_debugwindow.h"
#include "serialport_ui.h"
#include "ui_serialport_ui.h"
#include "port.h"
#include <QMessageBox>

debugwindow::debugwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::debugwindow)
{
    ui->setupUi(this);
    this->Plot->QwtInit(ui->qwtPlot);

    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(PortConfigSlot()));
    QObject::connect(ui->PowerButton,SIGNAL(clicked(bool)),this,SLOT(OpenPortSlot()));
}

debugwindow::~debugwindow()
{
    delete ui;
}

void debugwindow::PortConfigSlot()
{
    QObject::disconnect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
    serialport_ui config;
    config.exec();
    if(Port.isOpen())
    {
        ui->PowerButton->setText("关闭串口");
        QObject::connect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
    }
    else
    {
        ui->PowerButton->setText("打开串口");
        QObject::disconnect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
    }

}

void debugwindow::OpenPortSlot()
{
    if(ui->PowerButton->text()=="打开串口")
    {
        bool ok=Port.OpenPort();
        if(ok)
        {
            ui->PowerButton->setText("关闭串口");
            QObject::connect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
        }
        else
        {
            QMessageBox::information(this,"串口可能未打开","请检查设备是否未连接或被其他程序占用",QMessageBox::Yes);
            ui->PowerButton->setText("打开串口");
        }
    }
    else
    {
        Port.clear();
        Port.close();
        ui->PowerButton->setText("打开串口");
    }
}
