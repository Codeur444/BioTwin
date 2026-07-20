#include "BioCore.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BioCore w;
    w.show();
    return QApplication::exec();
}
