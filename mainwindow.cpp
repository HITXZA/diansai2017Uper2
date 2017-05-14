#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialport_ui.h"
#include "ui_serialport_ui.h"
#include "debugwindow.h"
#include "ui_debugwindow.h"
#include "port.h"
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Plot->QwtInit(ui->qwtPlot);
    ui->AngleSlider->setMaximum(90);
    ui->AngleSlider->setMinimum(0);
    ui->AngleSlider->setValue(0);

    QObject::connect(ui->DeBugButton,SIGNAL(clicked(bool)),this,SLOT(DeBugInterfaceSlot()));
    QObject::connect(ui->PowerButton,SIGNAL(clicked(bool)),this,SLOT(OpenPortSlot()));
    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(PortConfigSlot()));
    QObject::connect(ui->AngleSlider,SIGNAL(valueChanged(int)),this,SLOT(AngleSlot()));
    QObject::connect(ui->AngleBox,SIGNAL(valueChanged(int)),this,SLOT(AngleBoxSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PortConfigSlot()
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

void MainWindow::OpenPortSlot()
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

void MainWindow::DeBugInterfaceSlot()
{
    QObject::disconnect(&Port,SIGNAL(readyRead()),this->Plot,SLOT(QwtReceiveSlot()));
    debugwindow DeBug;
    DeBug.exec();
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

void MainWindow::AngleSlot()
{
    ui->AngleBox->setValue(ui->AngleSlider->value());
    qDebug()<<"ok";
    //TODO串口发送数据
}

void MainWindow::AngleBoxSlot()
{
    ui->AngleSlider->setValue(ui->AngleBox->value());
}
