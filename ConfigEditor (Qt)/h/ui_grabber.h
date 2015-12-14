/********************************************************************************
** Form generated from reading UI file 'grabber.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRABBER_H
#define UI_GRABBER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_Grabber
{
public:
    QCheckBox *WHW;
    QLabel *LHW;
    QLabel *LSC;
    QLabel *LSI;
    QLabel *LNI;
    QLabel *LES;
    QLabel *LSP;
    QCheckBox *WSC;
    QCheckBox *WSI;
    QCheckBox *WNI;
    QCheckBox *WES;
    QCheckBox *WSP;
    QLabel *Run;
    QSpinBox *SHI;
    QPushButton *GC;
    QSpinBox *SSC;
    QSpinBox *SSI;
    QSpinBox *SNI;
    QSpinBox *SES;
    QSpinBox *SSP;
    QCheckBox *CRun;

    void setupUi(QDialog *Grabber)
    {
        if (Grabber->objectName().isEmpty())
            Grabber->setObjectName(QStringLiteral("Grabber"));
        Grabber->resize(268, 246);
        WHW = new QCheckBox(Grabber);
        WHW->setObjectName(QStringLiteral("WHW"));
        WHW->setGeometry(QRect(190, 30, 70, 17));
        LHW = new QLabel(Grabber);
        LHW->setObjectName(QStringLiteral("LHW"));
        LHW->setGeometry(QRect(10, 30, 71, 16));
        LSC = new QLabel(Grabber);
        LSC->setObjectName(QStringLiteral("LSC"));
        LSC->setGeometry(QRect(10, 60, 61, 16));
        LSI = new QLabel(Grabber);
        LSI->setObjectName(QStringLiteral("LSI"));
        LSI->setGeometry(QRect(10, 90, 71, 16));
        LNI = new QLabel(Grabber);
        LNI->setObjectName(QStringLiteral("LNI"));
        LNI->setGeometry(QRect(10, 120, 71, 16));
        LES = new QLabel(Grabber);
        LES->setObjectName(QStringLiteral("LES"));
        LES->setGeometry(QRect(10, 150, 71, 16));
        LSP = new QLabel(Grabber);
        LSP->setObjectName(QStringLiteral("LSP"));
        LSP->setGeometry(QRect(10, 180, 71, 16));
        WSC = new QCheckBox(Grabber);
        WSC->setObjectName(QStringLiteral("WSC"));
        WSC->setGeometry(QRect(190, 60, 70, 17));
        WSI = new QCheckBox(Grabber);
        WSI->setObjectName(QStringLiteral("WSI"));
        WSI->setGeometry(QRect(190, 90, 70, 17));
        WNI = new QCheckBox(Grabber);
        WNI->setObjectName(QStringLiteral("WNI"));
        WNI->setGeometry(QRect(190, 120, 70, 17));
        WES = new QCheckBox(Grabber);
        WES->setObjectName(QStringLiteral("WES"));
        WES->setGeometry(QRect(190, 150, 70, 17));
        WSP = new QCheckBox(Grabber);
        WSP->setObjectName(QStringLiteral("WSP"));
        WSP->setGeometry(QRect(190, 180, 70, 17));
        Run = new QLabel(Grabber);
        Run->setObjectName(QStringLiteral("Run"));
        Run->setGeometry(QRect(110, 10, 101, 16));
        QFont font;
        font.setPointSize(12);
        Run->setFont(font);
        SHI = new QSpinBox(Grabber);
        SHI->setObjectName(QStringLiteral("SHI"));
        SHI->setGeometry(QRect(110, 30, 71, 22));
        SHI->setMinimum(1);
        SHI->setMaximum(32766);
        GC = new QPushButton(Grabber);
        GC->setObjectName(QStringLiteral("GC"));
        GC->setGeometry(QRect(10, 210, 131, 23));
        SSC = new QSpinBox(Grabber);
        SSC->setObjectName(QStringLiteral("SSC"));
        SSC->setGeometry(QRect(110, 60, 71, 22));
        SSC->setMinimum(1);
        SSC->setMaximum(32766);
        SSI = new QSpinBox(Grabber);
        SSI->setObjectName(QStringLiteral("SSI"));
        SSI->setGeometry(QRect(110, 90, 71, 22));
        SSI->setMinimum(1);
        SSI->setMaximum(32766);
        SNI = new QSpinBox(Grabber);
        SNI->setObjectName(QStringLiteral("SNI"));
        SNI->setGeometry(QRect(110, 120, 71, 22));
        SNI->setMinimum(1);
        SNI->setMaximum(32766);
        SES = new QSpinBox(Grabber);
        SES->setObjectName(QStringLiteral("SES"));
        SES->setGeometry(QRect(110, 150, 71, 22));
        SES->setMinimum(1);
        SES->setMaximum(32766);
        SSP = new QSpinBox(Grabber);
        SSP->setObjectName(QStringLiteral("SSP"));
        SSP->setGeometry(QRect(110, 180, 71, 22));
        SSP->setMinimum(1);
        SSP->setMaximum(32766);
        CRun = new QCheckBox(Grabber);
        CRun->setObjectName(QStringLiteral("CRun"));
        CRun->setGeometry(QRect(160, 210, 71, 17));

        retranslateUi(Grabber);

        QMetaObject::connectSlotsByName(Grabber);
    } // setupUi

    void retranslateUi(QDialog *Grabber)
    {
        Grabber->setWindowTitle(QApplication::translate("Grabber", "Dialog", 0));
        WHW->setText(QApplication::translate("Grabber", "Run", 0));
        LHW->setText(QApplication::translate("Grabber", "Hardware Info", 0));
        LSC->setText(QApplication::translate("Grabber", "Service Info", 0));
        LSI->setText(QApplication::translate("Grabber", "System Info", 0));
        LNI->setText(QApplication::translate("Grabber", "Network  Info", 0));
        LES->setText(QApplication::translate("Grabber", "Serial Info", 0));
        LSP->setText(QApplication::translate("Grabber", "Process Info", 0));
        WSC->setText(QApplication::translate("Grabber", "Run", 0));
        WSI->setText(QApplication::translate("Grabber", "Run", 0));
        WNI->setText(QApplication::translate("Grabber", "Run", 0));
        WES->setText(QApplication::translate("Grabber", "Run", 0));
        WSP->setText(QApplication::translate("Grabber", "Run", 0));
        Run->setText(QApplication::translate("Grabber", "Period (sec)", 0));
        GC->setText(QApplication::translate("Grabber", "Generate config file", 0));
        CRun->setText(QApplication::translate("Grabber", "Global run", 0));
    } // retranslateUi

};

namespace Ui {
    class Grabber: public Ui_Grabber {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRABBER_H
