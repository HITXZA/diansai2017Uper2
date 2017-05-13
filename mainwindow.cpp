#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialport_ui.h"
#include "ui_serialport_ui.h"
#include "port.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->Plot->QwtInit(ui->qwtPlot);

    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(PortConfigSlot()));
    QObject::connect(ui->PortConfigButton,SIGNAL(clicked(bool)),this,SLOT(OpenPortSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PortConfigSlot()
{
    //TODO 连接串口槽
    serialport_ui config;
    config.exec();
    if(Port.isOpen())
    {
        ui->PowerButton->setText("关闭串口");
        //TODO 连接串口槽
    }
    else
    {
        ui->PowerButton->setText("打开串口");
        //TODO 连接串口槽
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
