#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>
#include <QtSerialPort/QserialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort* serialPort;

private slots:

    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void on_sendButton_clicked();

    void on_quitButton_clicked();

private:
    Ui::MainWindow *ui;

    void ComBoBoxInit();
    void LabelInit();
    void BaudrateInit();
    void TableInit();
    void PortInit();

    void SerialTransmitter();
    void SerialReceiver();
    void PortInformation();
    void ReadData();
    void GetPortList();

    enum Columns
    {
        NAME, DESCRIPTION, MANUFACTURER
    };
};

#endif // MAINWINDOW_H
