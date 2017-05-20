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
    this->Reflash->start(10);

    QObject::connect(ui->DeBugButton,SIGNAL(clicked(bool)),this,SLOT(DeBugInterfaceSlot()));
    QObject::connect(ui->PowerButton,SIGNAL(clicked(bool)),this,SLOT(OpenPortSlot()));
    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(PortConfigSlot()));
    QObject::connect(ui->AngleSlider,SIGNAL(valueChanged(int)),this,SLOT(AngleSlot()));
    QObject::connect(ui->AngleBox,SIGNAL(valueChanged(int)),this,SLOT(AngleBoxSlot()));
    QObject::connect(ui->DistanceAddButton,SIGNAL(clicked(bool)),this,SLOT(distanceAddSlot()));
    QObject::connect(ui->DistanceButton,SIGNAL(clicked(bool)),this,SLOT(distanceSlot()));
    QObject::connect(this->Reflash,SIGNAL(timeout()),ui->qwtPlot,SLOT(replot()));
    QObject::connect(ui->cleanButton,SIGNAL(clicked(bool)),this->Plot,SLOT(CleanSlot()));
    QObject::connect(ui->stopbutton,SIGNAL(clicked(bool)),this,SLOT(StopSlot()));

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
        QMessageBox a;
        a.setIcon(QMessageBox::Information);
        a.setWindowTitle("正在打开串口");
        a.show();

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
        a.close();
    }
    else
    {
        QMessageBox a;
        a.setIcon(QMessageBox::Information);
        a.setWindowTitle("正在关闭串口");
        a.show();

        Port.clear();
        Port.close();
        ui->PowerButton->setText("打开串口");

        a.close();
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
    Port.AngleSlot(ui->AngleSlider->value());
}

void MainWindow::AngleBoxSlot()
{
    ui->AngleSlider->setValue(ui->AngleBox->value());
}

void MainWindow::distanceAddSlot()
{
    Port.DistanceAddSlot();
}

void MainWindow::distanceSlot()
{
    Port.distanceMinusSlot();
}

void MainWindow::StopSlot()
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
    ui->AngleSlider->setValue(5);
    AngleSlot();//串口多发送几次数据
    AngleSlot();
    AngleSlot();
    AngleSlot();
    AngleSlot();

}
