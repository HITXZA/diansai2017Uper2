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
    if(Port.isOpen())
    {
        ui->PowerButton->setText("关闭串口");
        QObject::connect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
    }
    else
    {
        ui->PowerButton->setText("打开串口");
    }

    this->Plot->QwtInit(ui->qwtPlot);
    ui->AngleSlider->setMaximum(90);
    ui->AngleSlider->setMinimum(0);
    ui->P->setMaximum(1000);
    ui->P->setMinimum(0);
    ui->I->setMaximum(1000);
    ui->I->setMinimum(0);
    ui->D->setMaximum(1000);
    ui->D->setMinimum(0);
    ui->PBox->setSingleStep(0.01);
    ui->IBox->setSingleStep(0.01);
    ui->DBox->setSingleStep(0.01);


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
    QObject::connect(ui->DistanceButtonAdd,SIGNAL(clicked(bool)),this,SLOT(DistanceaddSlot()));
    QObject::connect(ui->DistanceButton,SIGNAL(clicked(bool)),this,SLOT(DistanceSlot()));
    QObject::connect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
    QObject::connect(ui->cleanButton,SIGNAL(clicked(bool)),this->Plot,SLOT(CleanSlot()));
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
    ui->PBox->setValue(ui->P->value()/100.0);
    this->SendData();
}

void debugwindow::PBoxSlot()
{
    ui->P->setValue(ui->PBox->value()*100);
}

void debugwindow::ISlot()
{
    ui->IBox->setValue(ui->I->value()/100.0);
    this->SendData();
}

void debugwindow::IBoxSlot()
{
    ui->I->setValue(ui->IBox->value()*100);
}

void debugwindow::DSlot()
{
    ui->DBox->setValue(ui->D->value()/100.0);
    this->SendData();
}

void debugwindow::DBoxSlot()
{
    ui->D->setValue(ui->DBox->value()*100);
}

void debugwindow::AngleSlot()
{
    ui->AngleBox->setValue(ui->AngleSlider->value());
    Port.AngleSlot(ui->AngleSlider->value());
}

void debugwindow::AngleBoxSlot()
{
    ui->AngleSlider->setValue(ui->AngleBox->value());
}

void debugwindow::DistanceaddSlot()
{
    Port.DistanceAddSlot();
}

void debugwindow::DistanceSlot()
{
    Port.distanceMinusSlot();
}

void debugwindow::SendData()
{
    Port.PIDSlot(ui->PBox->value(),ui->IBox->value(),ui->DBox->value());
}
