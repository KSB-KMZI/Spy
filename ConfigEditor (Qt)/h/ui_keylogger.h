/********************************************************************************
** Form generated from reading UI file 'keylogger.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYLOGGER_H
#define UI_KEYLOGGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Keylogger
{
public:
    QCheckBox *RKL;
    QPushButton *GC;

    void setupUi(QDialog *Keylogger)
    {
        if (Keylogger->objectName().isEmpty())
            Keylogger->setObjectName(QStringLiteral("Keylogger"));
        Keylogger->resize(167, 81);
        RKL = new QCheckBox(Keylogger);
        RKL->setObjectName(QStringLiteral("RKL"));
        RKL->setGeometry(QRect(20, 20, 70, 17));
        GC = new QPushButton(Keylogger);
        GC->setObjectName(QStringLiteral("GC"));
        GC->setGeometry(QRect(20, 50, 111, 23));

        retranslateUi(Keylogger);

        QMetaObject::connectSlotsByName(Keylogger);
    } // setupUi

    void retranslateUi(QDialog *Keylogger)
    {
        Keylogger->setWindowTitle(QApplication::translate("Keylogger", "Dialog", 0));
        RKL->setText(QApplication::translate("Keylogger", "Run", 0));
        GC->setText(QApplication::translate("Keylogger", "Generate config file", 0));
    } // retranslateUi

};

namespace Ui {
    class Keylogger: public Ui_Keylogger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYLOGGER_H
