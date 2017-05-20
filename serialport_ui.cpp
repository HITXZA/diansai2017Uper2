#include "serialport_ui.h"
#include "ui_serialport_ui.h"
#include "port.h"
#include <QMessageBox>
#include <QDebug>

serialport_ui::serialport_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serialport_ui)
{
    ui->setupUi(this);
    Port.PortScan();
    if(Port.PortInfo.isEmpty())
    {
        ui->COMBox->addItem("无串口");
        ui->PowerButton->setEnabled(false);
        ui->SaveButton->setEnabled(false);
    }
    foreach (QSerialPortInfo info, Port.PortInfo)
    {
        ui->COMBox->addItem(info.portName());
    }


    this->PortToRight();
    this->PortChackSlot();
    QObject::connect(ui->PowerButton,SIGNAL(clicked(bool)),this,SLOT(PortOpenSlot()));
    QObject::connect(ui->SaveButton,SIGNAL(clicked(bool)),this,SLOT(PortSaveSlot()));
    QObject::connect(ui->SendButton,SIGNAL(clicked(bool)),this,SLOT(SendSlot()));

}

serialport_ui::~serialport_ui()
{
    if(Port.isOpen())
    {
        QObject::disconnect(&Port,SIGNAL(readyRead()),this,SLOT(ReceiveSlot()));
    }
    delete ui;
}

void serialport_ui::PortChackSlot()
{
    if(Port.isOpen())
    {
        ui->ChackBox->setEnabled(false);
        ui->SpeedBox->setEnabled(false);
        ui->COMBox->setEnabled(false);
        ui->DataBox->setEnabled(false);
        ui->StopBox->setEnabled(false);
        ui->PowerButton->setText("关闭串口");
        QObject::connect(&Port,SIGNAL(readyRead()),this,SLOT(ReceiveSlot()));
    }
    else if(!Port.isOpen())
    {
        ui->ChackBox->setEnabled(true);
        ui->SpeedBox->setEnabled(true);
        ui->COMBox->setEnabled(true);
        ui->DataBox->setEnabled(true);
        ui->StopBox->setEnabled(true);
        ui->PowerButton->setText("打开串口");
        QObject::disconnect(&Port,SIGNAL(readyRead()),this,SLOT(ReceiveSlot()));
    }
}

void serialport_ui::PortSaveSlot()
{
    Port.settings.baud=ui->SpeedBox->currentIndex();
    Port.settings.Data=ui->DataBox->currentIndex();
    Port.settings.parity=ui->ChackBox->currentIndex();
    Port.settings.portname=ui->COMBox->currentText();
    Port.settings.stopbit=ui->StopBox->currentIndex();
    QMessageBox::information(this,"保存成功","串口信息更新成功",QMessageBox::Yes);
    this->PortChackSlot();
}

void serialport_ui::PortOpenSlot()
{
    if(ui->PowerButton->text()=="打开串口")
    {
        QMessageBox a;
        a.setIcon(QMessageBox::Information);
        a.setWindowTitle("正在打开串口");
        a.show();

        Port.settings.baud=ui->SpeedBox->currentIndex();
        Port.settings.Data=ui->DataBox->currentIndex();
        Port.settings.parity=ui->ChackBox->currentIndex();
        Port.settings.portname=ui->COMBox->currentText();
        Port.settings.stopbit=ui->StopBox->currentIndex();
        bool ok=Port.OpenPort();
        a.close();
        if(ok)
        {
            ui->PowerButton->setText("关闭串口");
        }
        else
        {
            QMessageBox::information(this,"串口可能未打开","请检查设备是否未连接或被其他程序占用",QMessageBox::Yes);
            ui->PowerButton->setText("打开串口");
        }
    }
    else if(ui->PowerButton->text()=="关闭串口")
    {
        QMessageBox a;
        a.setIcon(QMessageBox::Information);
        a.setWindowTitle("正在关闭串口");
        a.show();

        Port.clear();
        Port.close();
    }


    this->PortChackSlot();
}

void serialport_ui::ReceiveSlot()
{
    if(ui->HEXBox->isChecked())
    {
        QByteArray buf=Port.read(1);
        QString str=" "+buf.toHex();
        ui->ReceiveAera->insertPlainText(str);
        buf.clear();
    }
    else if(!ui->HEXBox->isChecked())
    {
        QByteArray buf;
        buf =Port.readAll();
        QString str="下位机:"+buf;
        QString test=buf;
        qDebug()<<test.toInt();
        ui->ReceiveAera->append(str);
        buf.clear();
    }
}

void serialport_ui::SendSlot()
{
    if(!Port.isOpen())
    {
        QMessageBox::information(this,"发送错误","串口未打开",QMessageBox::Ok);
        return;
    }
    if(ui->SendAera->text().isEmpty())
    {
        if(QMessageBox::question(this,tr("当前发送区无内容"),"您确定要发送空内容吗?",QMessageBox::Cancel|QMessageBox::Ok)==QMessageBox::Cancel)
        {
            return;
        }
    }


    Port.write(ui->SendAera->text().toLatin1());
    ui->ReceiveAera->append("上位机:"+ui->SendAera->text());
    if(ui->CleanBox->isChecked())
    {
        ui->SendAera->clear();
    }
}

void serialport_ui::PortToRight()
{
    ui->COMBox->setCurrentText(Port.settings.portname);
    ui->SpeedBox->setCurrentIndex(Port.settings.baud);
    ui->StopBox->setCurrentIndex(Port.settings.stopbit);
    ui->DataBox->setCurrentIndex(Port.settings.Data);
    ui->ChackBox->setCurrentIndex(Port.settings.parity);
}
