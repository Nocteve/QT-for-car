#pragma once

#include <QtWidgets/QWidget>
#include <qpushbutton.h>
#include "ui_qt_for_car.h"
#include "serial.h"
#include <QInputDialog.h>
#include <QMessageBox.h>
#include <QString.h>
#include <QLabel.h>
#include <QSlider.h>
#include <thread>
#include <Windows.h>
extern QLabel* labelForState;
class qt_for_car : public QWidget
{
    Q_OBJECT

public:
    qt_for_car(QWidget *parent = nullptr);
    ~qt_for_car();
public slots:
    void car_forward() {
        sendCommandToESP32("FORWARD");
        labelForState->setText("FORWARD");
    }
    void car_backward() {
        sendCommandToESP32("BACKWARD");
        labelForState->setText("BACKWARD");
    }
    void car_left() {
        sendCommandToESP32("LEFT");
        labelForState->setText("LEFT");
    }
    void car_right() {
        sendCommandToESP32("RIGHT");
        labelForState->setText("RIGHT");
    }
    void car_stop() {
        sendCommandToESP32("STOP");
        labelForState->setText("STOP");
    }
    void quick_left() {
        unsigned char data[6];
        DWORD bytesWritten;
        data[0] = 0xAA;
        data[1] = 0x00;
        data[2] = 0xFF;
        data[3] = 0x01;
        data[4] = 0xFF;

        data[5] = calculateBCC(data, 5);

        WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

        labelForState->setText("QUICKLEFT");
    }
    void quick_right() {
        unsigned char data[6];
        DWORD bytesWritten;
        data[0] = 0xAA;
        data[1] = 0x01;
        data[2] = 0xFF;
        data[3] = 0x00;
        data[4] = 0xFF;

        data[5] = calculateBCC(data, 5);

        WriteFile(hSerial, data, sizeof(data), &bytesWritten, NULL);

        labelForState->setText("QUICKRIGHT");
    }
private:
    Ui::qt_for_carClass ui;
};
