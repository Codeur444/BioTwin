#ifndef BIOCORE_H
#define BIOCORE_H

#include <QMainWindow>
#include <QtSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class BioCore;
}
QT_END_NAMESPACE

class BioCore : public QMainWindow
{
    Q_OBJECT

public:
    explicit BioCore(QWidget *parent = nullptr);
    ~BioCore() override;

private slots:
    void readSerial();

private:
    Ui::BioCore *ui;
    QSerialPort *portSerial;

    void serialPortInit();
};
#endif
