#pragma once

#include <QtWidgets/QWidget>
#include <qpushbutton.h>
#include "ui_qt_for_car.h"
#include "serial.h"

class qt_for_car : public QWidget
{
    Q_OBJECT

public:
    qt_for_car(QWidget *parent = nullptr);
    ~qt_for_car();
public slots:
    void car_forward() {
        sendCommandToESP32("FORWARD");
    }
    void car_backward() {
        sendCommandToESP32("BACKWARD");
    }
    void car_left() {
        sendCommandToESP32("LEFT");
    }
    void car_right() {
        sendCommandToESP32("RIGHT");
    }
    void car_stop() {
        sendCommandToESP32("STOP");
    }
private:
    Ui::qt_for_carClass ui;
};
