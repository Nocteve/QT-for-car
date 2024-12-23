#include "qt_for_car.h"
#include <QInputDialog.h>
#include <QMessageBox.h>
#include <QString.h>
#include <QLabel.h>
#include <QSlider.h>
#include <thread>
#include <Windows.h>
#include "serial.h"
QWidget* t;
bool judge = false;
QString stateForCom;
QLabel* labelForCom;
QLabel* labelForSpeed;
QSlider* changeSpeed;
QLabel* dataShow;
extern HANDLE hSerial;
void input() {
    bool ok = false;
    QString com = QInputDialog::getText(t, "Please input your COM", "Please input your COM",
        QLineEdit::Normal, "COM3", &ok);
    ok = false;
    int baudRate = QInputDialog::getInt(t, "Please input your baudRate", "Please input your baudRate",
        9600, -2147483647, 2147483647, 100, &ok);
    if (!com.isEmpty() && baudRate) {
        std::wstring c = com.toStdWString();
        DWORD b = baudRate;
        if (!initSerialPort(c, baudRate)) {
            judge = false;
        }
        else {
            judge = true;
        }
    }
}
void change() {
    input();
    if (judge == true) {
        stateForCom = "Successfully initialized.";
    }
    else {
        stateForCom = "Failed to initialize the port.";
    }
    labelForCom->setText(stateForCom);
}
void change_speed() {
    labelForSpeed->setNum(changeSpeed->value());
    char command[50];
    sprintf_s(command, sizeof(command), "PWM %.2f", (float)changeSpeed->value());
    sendCommandToESP32(command);
}

void readData() {
    while (judge) {
        std::string data;
        receiveDataFromESP32(data);
        int i = data.find("PWM_L");
        QString pwm_l = QString::fromStdString(data);
        dataShow->setText(pwm_l);
        //Sleep(50);
    }
}

qt_for_car::qt_for_car(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    t = this;
    input();
        
    if (judge == true) {
        stateForCom = "Successfully initialized.";
    }
    else {
        stateForCom = "Failed to initialize the port.";
    }
    labelForCom = new QLabel(stateForCom,this);
    labelForCom->move(20, 20);
    labelForCom->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    this->setFixedSize(600, 400);

    QPushButton* changeCom = new QPushButton("changeCom", this);
    connect(changeCom, &QPushButton::clicked, change);
    changeCom->move(20,50);
    changeCom->resize(180, 40);

    QPushButton* forward,*backward,*left,*right;
    forward = new QPushButton("forward",this);
    backward = new QPushButton("backward", this);
    left = new QPushButton("left", this);
    right = new QPushButton("right", this);
    forward->resize(80, 80);
    backward->resize(80, 80);
    left->resize(80, 80);
    right->resize(80, 80);
    forward->move(270, 240);
    backward->move(270, 320);
    left->move(190, 320);
    right->move(350, 320);
    forward->setShortcut(QKeySequence(Qt::Key_W));
    backward->setShortcut(QKeySequence(Qt::Key_S));
    left->setShortcut(QKeySequence(Qt::Key_A));
    right->setShortcut(QKeySequence(Qt::Key_D));
    connect(forward, &QPushButton::pressed, this, &qt_for_car::car_forward);
    connect(backward, &QPushButton::pressed, this, &qt_for_car::car_backward);
    connect(left, &QPushButton::pressed, this, &qt_for_car::car_left);
    connect(right, &QPushButton::pressed, this, &qt_for_car::car_right);

    QPushButton* stop = new QPushButton("Stop !", this);
    stop->resize(80, 80);
    stop->move(20, 100);
    stop->setShortcut(Qt::Key_P);
    connect(stop, &QPushButton::pressed, this, &qt_for_car::car_stop);

    changeSpeed = new QSlider(Qt::Horizontal,this);
    changeSpeed->move(450, 360);
    changeSpeed->resize(120, 30);
    changeSpeed->setMinimum(0);
    changeSpeed->setMaximum(255);
    changeSpeed->setValue(255);
    labelForSpeed = new QLabel(this);
    labelForSpeed->resize(60, 30);
    labelForSpeed->move(200, 100);
    labelForSpeed->setNum(255);
    labelForSpeed->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    QLabel* pwm = new QLabel("PWM:", this);
    pwm->setStyleSheet("QLabel{font:normal bold 15px}");
    pwm->move(450, 335);
    labelForSpeed->move(498, 330);
    connect(changeSpeed, &QSlider::sliderReleased, this, change_speed);

    QPushButton* quickLeft, * quickRight;
    quickLeft = new QPushButton("quick left", this);
    quickRight = new QPushButton("quick right", this);
    quickLeft->resize(80, 80);
    quickRight->resize(80, 80);
    quickLeft->move(20, 240);
    quickRight->move(100, 240);
    quickLeft->setShortcut('U');
    quickRight->setShortcut('I');

    //dataShow = new QLabel(this);
    ////dataShow->resize(300, 300);
    //dataShow->move(100, 100);
    //dataShow->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    //std::thread read(readData);
    ////read.join();
    //read.detach();
}

qt_for_car::~qt_for_car()
{}
