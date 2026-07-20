#include "BioCore.h"
#include "./ui_BioCore.h"
#include <QDebug>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;

BioCore::BioCore(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BioCore)
{
    ui->setupUi(this);
    serialPortInit();
    connect(portSerial, &QSerialPort::readyRead, this, &BioCore::readSerial);
}

void BioCore::serialPortInit()
{
    portSerial = new QSerialPort(this);
    portSerial->setPortName("/dev/ttyACM0");
    portSerial->setBaudRate(QSerialPort::Baud9600);

    if (portSerial->open(QIODevice::ReadOnly))
    {
        cout << "Connecté" << endl;
    }
    else
    {
        cout << "Erreur, cable non connecté" << endl;
    }
}

void BioCore::readSerial()
{
    QByteArray line;
    QJsonDocument json;
    QJsonObject data;
    QString message, error;
    double bpm, beatMoy;

    while(portSerial->canReadLine())
    {
        line = portSerial->readLine().trimmed();
        json = QJsonDocument::fromJson(line);
        data = json.object();
        message = data["message"].toString();
        error = data["error"].toString();
        bpm = data["bpm"].toDouble();
        beatMoy = data["beatMoy"].toDouble();

        if (message.length() > 0)
        {
            cout << message.toStdString() << endl;
        }

        if (error.length() > 0)
        {
            cout << error.toStdString() << endl;
        }

        if (bpm > 0)
        {
            cout << "BPM : " << bpm << endl;
        }

        if (beatMoy > 0)
        {
            cout << "BPM moyenne : " << beatMoy << endl;
        }
    }
}

BioCore::~BioCore()
{
    delete ui;
}
