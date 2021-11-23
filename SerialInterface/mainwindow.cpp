#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QComboBox>
#include <Qstring>
#include <QLabel>
#include <QDebug>
#include <QtSerialPort/QserialPort>
#include <QtSerialPort/QserialPortInfo>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ComBoBoxInit();
    LabelInit();
    PortInformation();
    TableInit();
}

MainWindow::~MainWindow()
{
    delete ui;
    serialPort->close();
}

void MainWindow::SerialTransmitter()
{

    QByteArray sendData;
    sendData = ui->transEdit->text().toUtf8().left(1);
    serialPort->write(sendData.data());
}

void MainWindow::SerialReceiver()
{
    QByteArray readData;
    readData = serialPort->readAll();

    ui->receiveEdit->setText(readData);
}

void MainWindow::on_sendButton_clicked()
{
    MainWindow::SerialTransmitter();
}

void MainWindow::on_connectButton_clicked()
{
    serialPort = new QSerialPort();
    serialPort->setPortName("COM13");
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    QObject::connect(ui->connectButton, SIGNAL(clicked(bool)), this, SLOT(SerialTransmitter()));
    QObject::connect(serialPort, SIGNAL(readyRead()), this, SLOT(SerialReceiver()));

    if(!serialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "\n Serial Port Open Failed!\n";
    }
}

void MainWindow::on_disconnectButton_clicked()
{
    if(serialPort->isOpen())
    {
        serialPort->close();
    }
}

void MainWindow::PortInformation()
{
    ui->portNumberComboBox->clear();
    const auto infos = QSerialPortInfo::availablePorts();

    for(const QSerialPortInfo &info : infos)
    {
        ui->portNumberComboBox->addItem(info.portName());
    }

}

void MainWindow::LabelInit()
{
    /* Settging Label Init Function */
    ui->portNumberLabel->setText("Port Number");
    ui->baudrateLabel->setText("Baud rate");
    ui->dataBitsLabel->setText("Data Bits");
    ui->stopBitsLabel->setText("Stop Bits");
    ui->parityBitsLabel->setText("Parity Bits");
    ui->flowControlLabel->setText("Flow Control");
}

void MainWindow::ReadData()
{
    const QByteArray data = serialPort->readAll();
}

void MainWindow::ComBoBoxInit()
{
    BaudrateInit();

    ui->dataBitsComboBox->addItem("8 Bits");
    ui->dataBitsComboBox->addItem("9 Bits");

    ui->stopBitsComboBox->addItem("1 Bits");
    ui->stopBitsComboBox->addItem("2 Bits");

    ui->parityBitsComboBox->addItem("None");
    ui->parityBitsComboBox->addItem("odd");
    ui->parityBitsComboBox->addItem("even");

    ui->flowControlComboBox->addItem("Disable");

}

void MainWindow::BaudrateInit()
{
    ui->baudrateComboBox->addItem("9600");
    ui->baudrateComboBox->addItem("1200");
    ui->baudrateComboBox->addItem("2400");
    ui->baudrateComboBox->addItem("4800");
    ui->baudrateComboBox->addItem("19200");
    ui->baudrateComboBox->addItem("38400");
    ui->baudrateComboBox->addItem("57600");
    ui->baudrateComboBox->addItem("115200");
}

void MainWindow::TableInit()
{
    QStringList tableHeader;
    tableHeader << "name" << "Description" << "Manufacturer";
    ui->portTable->setColumnCount(3);
    ui->portTable->setHorizontalHeaderLabels(tableHeader);
    GetPortList();
}

void MainWindow::GetPortList()
{
    int index;
    ui->portTable->setRowCount(0);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->portTable->insertRow((ui->portTable->rowCount()));
        index = ui->portTable->rowCount() - 1;
        ui->portTable->setItem(index, NAME, new QTableWidgetItem(info.portName()));
        ui->portTable->setItem(index, DESCRIPTION, new QTableWidgetItem(info.description()));
        ui->portTable->setItem(index, MANUFACTURER, new QTableWidgetItem(info.manufacturer()));
    }
}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}
