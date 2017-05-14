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
    ui->AngleSlider->setMaximum(90);
    ui->AngleSlider->setMinimum(0);
    ui->DistanceSlider->setMaximum(10);
    ui->DistanceSlider->setMinimum(0);
    ui->P->setMaximum(1000);
    ui->P->setMinimum(0);
    ui->I->setMaximum(1000);
    ui->I->setMinimum(0);
    ui->D->setMaximum(1000);
    ui->D->setMinimum(0);


    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(PortConfigSlot()));
    QObject::connect(ui->PowerButton,SIGNAL(clicked(bool)),this,SLOT(OpenPortSlot()));
    QObject::connect(ui->P,SIGNAL(valueChanged(int)),this,SLOT(PSlot()));
    QObject::connect(ui->PBox,SIGNAL(valueChanged(double)),this,SLOT(PBoxSlot()));
    QObject::connect(ui->I,SIGNAL(valueChanged(int)),this,SLOT(ISlot()));
    QObject::connect(ui->IBox,SIGNAL(valueChanged(double)),this,SLOT(IBoxSlot()));
    QObject::connect(ui->D,SIGNAL(valueChanged(int)),this,SLOT(DSlot()));
    QObject::connect(ui->DBox,SIGNAL(valueChanged(double)),this,SLOT(DBoxSlot()));
    QObject::connect(ui->AngleSlider,SIGNAL(valueChanged(int)),this,SLOT(AngleSlot()));
    QObject::connect(ui->AngleBox,SIGNAL(valueChanged(int)),this,SLOT(AngleBoxSlot()));
    QObject::connect(ui->DistanceSlider,SIGNAL(valueChanged(int)),this,SLOT(distanceSlot()));
    QObject::connect(ui->DistanceBox,SIGNAL(valueChanged(int)),this,SLOT(distanceBoxSlot()));
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

void debugwindow::PSlot()
{
    ui->PBox->setValue(ui->P->value()/100);
    this->SendData();
}

void debugwindow::PBoxSlot()
{
    ui->P->setValue(ui->PBox->value()*100);
}

void debugwindow::ISlot()
{
    ui->IBox->setValue(ui->I->value()/100);
    this->SendData();
}

void debugwindow::IBoxSlot()
{
    ui->I->setValue(ui->IBox->value()*100);
}

void debugwindow::DSlot()
{
    ui->DBox->setValue(ui->D->value()/100);
    this->SendData();
}

void debugwindow::DBoxSlot()
{
    ui->D->setValue(ui->DBox->value()*100);
}

void debugwindow::AngleSlot()
{
    ui->AngleBox->setValue(ui->AngleSlider->value());
    this->SendData();
}

void debugwindow::AngleBoxSlot()
{
    ui->AngleSlider->setValue(ui->AngleBox->value());
}

void debugwindow::distanceSlot()
{
    ui->DistanceBox->setValue(ui->DistanceSlider->value());
    this->SendData();
}

void debugwindow::distanceBoxSlot()
{
    ui->DistanceSlider->setValue(ui->DistanceBox->value());
}

void debugwindow::SendData()
{

}
