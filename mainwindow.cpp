#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialport_ui.h"
#include "ui_serialport_ui.h"
#include "port.h"
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Plot->QwtInit(ui->qwtPlot);

    QObject::connect(ui->PowerButton,SIGNAL(clicked(bool)),this,SLOT(OpenPortSlot()));
    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(PortConfigSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PortConfigSlot()
{
    //QObject::disconnect(&Port,SIGNAL(readyRead()),this,SLOT(ReceiveSlot()));
    serialport_ui config;
    config.exec();
    if(Port.isOpen())
    {
        ui->PowerButton->setText("关闭串口");
        //Object::connect(&Port,SIGNAL(readyRead()),this,SLOT(ReceiveSlot()));
    }
    else
    {
        ui->PowerButton->setText("打开串口");
        //QObject::disconnect(&Port,SIGNAL(readyRead()),this,SLOT(ReceiveSlot()));
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
            //连接槽
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
