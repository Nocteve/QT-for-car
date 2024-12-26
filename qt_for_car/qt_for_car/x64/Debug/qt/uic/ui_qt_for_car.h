/********************************************************************************
** Form generated from reading UI file 'qt_for_car.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_FOR_CAR_H
#define UI_QT_FOR_CAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt_for_carClass
{
public:

    void setupUi(QWidget *qt_for_carClass)
    {
        if (qt_for_carClass->objectName().isEmpty())
            qt_for_carClass->setObjectName("qt_for_carClass");
        qt_for_carClass->resize(600, 400);

        retranslateUi(qt_for_carClass);

        QMetaObject::connectSlotsByName(qt_for_carClass);
    } // setupUi

    void retranslateUi(QWidget *qt_for_carClass)
    {
        qt_for_carClass->setWindowTitle(QCoreApplication::translate("qt_for_carClass", "qt_for_car", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qt_for_carClass: public Ui_qt_for_carClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_FOR_CAR_H
