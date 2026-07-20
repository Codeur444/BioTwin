/********************************************************************************
** Form generated from reading UI file 'BioCore.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIOCORE_H
#define UI_BIOCORE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BioCore
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BioCore)
    {
        if (BioCore->objectName().isEmpty())
            BioCore->setObjectName("BioCore");
        BioCore->resize(800, 600);
        centralwidget = new QWidget(BioCore);
        centralwidget->setObjectName("centralwidget");
        BioCore->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BioCore);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 23));
        BioCore->setMenuBar(menubar);
        statusbar = new QStatusBar(BioCore);
        statusbar->setObjectName("statusbar");
        BioCore->setStatusBar(statusbar);

        retranslateUi(BioCore);

        QMetaObject::connectSlotsByName(BioCore);
    } // setupUi

    void retranslateUi(QMainWindow *BioCore)
    {
        BioCore->setWindowTitle(QCoreApplication::translate("BioCore", "BioCore", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BioCore: public Ui_BioCore {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIOCORE_H
