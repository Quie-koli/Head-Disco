/********************************************************************************
** Form generated from reading UI file 'HeadDisco.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEADDISCO_H
#define UI_HEADDISCO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HeadDiscoClass
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *HeadDiscoClass)
    {
        if (HeadDiscoClass->objectName().isEmpty())
            HeadDiscoClass->setObjectName(QString::fromUtf8("HeadDiscoClass"));
        HeadDiscoClass->resize(1000, 818);
        centralWidget = new QWidget(HeadDiscoClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        HeadDiscoClass->setCentralWidget(centralWidget);

        retranslateUi(HeadDiscoClass);

        QMetaObject::connectSlotsByName(HeadDiscoClass);
    } // setupUi

    void retranslateUi(QMainWindow *HeadDiscoClass)
    {
        HeadDiscoClass->setWindowTitle(QCoreApplication::translate("HeadDiscoClass", "HeadDisco", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HeadDiscoClass: public Ui_HeadDiscoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEADDISCO_H
