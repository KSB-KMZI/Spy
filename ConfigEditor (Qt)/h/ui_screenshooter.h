/********************************************************************************
** Form generated from reading UI file 'screenshooter.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCREENSHOOTER_H
#define UI_SCREENSHOOTER_H

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

class Ui_screenshooter
{
public:
    QPushButton *GC;
    QCheckBox *RSC;
    QSpinBox *SSC;
    QLabel *Period;

    void setupUi(QDialog *screenshooter)
    {
        if (screenshooter->objectName().isEmpty())
            screenshooter->setObjectName(QStringLiteral("screenshooter"));
        screenshooter->resize(176, 92);
        GC = new QPushButton(screenshooter);
        GC->setObjectName(QStringLiteral("GC"));
        GC->setGeometry(QRect(20, 60, 121, 23));
        RSC = new QCheckBox(screenshooter);
        RSC->setObjectName(QStringLiteral("RSC"));
        RSC->setGeometry(QRect(120, 30, 70, 17));
        SSC = new QSpinBox(screenshooter);
        SSC->setObjectName(QStringLiteral("SSC"));
        SSC->setGeometry(QRect(20, 30, 81, 22));
        SSC->setMinimum(1);
        SSC->setMaximum(32766);
        Period = new QLabel(screenshooter);
        Period->setObjectName(QStringLiteral("Period"));
        Period->setGeometry(QRect(40, 10, 47, 13));

        retranslateUi(screenshooter);

        QMetaObject::connectSlotsByName(screenshooter);
    } // setupUi

    void retranslateUi(QDialog *screenshooter)
    {
        screenshooter->setWindowTitle(QApplication::translate("screenshooter", "Dialog", 0));
        GC->setText(QApplication::translate("screenshooter", "Generate config file", 0));
        RSC->setText(QApplication::translate("screenshooter", "Run", 0));
        Period->setText(QApplication::translate("screenshooter", "Period", 0));
    } // retranslateUi

};

namespace Ui {
    class screenshooter: public Ui_screenshooter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCREENSHOOTER_H
