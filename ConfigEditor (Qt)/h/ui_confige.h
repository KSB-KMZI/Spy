/********************************************************************************
** Form generated from reading UI file 'confige.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGE_H
#define UI_CONFIGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ConfigE
{
public:
    QGridLayout *gridLayout;
    QGridLayout *Grid;
    QPushButton *CallKeylogger;
    QPushButton *CallGrabber;
    QPushButton *CallScreenshooter;

    void setupUi(QDialog *ConfigE)
    {
        if (ConfigE->objectName().isEmpty())
            ConfigE->setObjectName(QStringLiteral("ConfigE"));
        ConfigE->resize(351, 142);
        gridLayout = new QGridLayout(ConfigE);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Grid = new QGridLayout();
        Grid->setSpacing(6);
        Grid->setObjectName(QStringLiteral("Grid"));
        CallKeylogger = new QPushButton(ConfigE);
        CallKeylogger->setObjectName(QStringLiteral("CallKeylogger"));

        Grid->addWidget(CallKeylogger, 1, 0, 1, 1);

        CallGrabber = new QPushButton(ConfigE);
        CallGrabber->setObjectName(QStringLiteral("CallGrabber"));

        Grid->addWidget(CallGrabber, 0, 0, 1, 1);

        CallScreenshooter = new QPushButton(ConfigE);
        CallScreenshooter->setObjectName(QStringLiteral("CallScreenshooter"));

        Grid->addWidget(CallScreenshooter, 2, 0, 1, 1);


        gridLayout->addLayout(Grid, 0, 0, 1, 1);


        retranslateUi(ConfigE);

        QMetaObject::connectSlotsByName(ConfigE);
    } // setupUi

    void retranslateUi(QDialog *ConfigE)
    {
        ConfigE->setWindowTitle(QApplication::translate("ConfigE", "ConfigE", 0));
        CallKeylogger->setText(QApplication::translate("ConfigE", "Generate config file for Keylogger.exe", 0));
        CallGrabber->setText(QApplication::translate("ConfigE", "Generate config file for Grabber.exe", 0));
        CallScreenshooter->setText(QApplication::translate("ConfigE", "Generate config file for Screenshooter.exe", 0));
    } // retranslateUi

};

namespace Ui {
    class ConfigE: public Ui_ConfigE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGE_H
