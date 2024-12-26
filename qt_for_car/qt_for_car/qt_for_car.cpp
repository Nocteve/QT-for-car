#include "qt_for_car.h"
#include "serial.h"
#include <qthread.h>
QWidget* t;
bool judge = false;
QString stateForCom;
QLabel* labelForCom;
QLabel* labelForSpeed;
extern QLabel* labelForState;
QLabel* labelForState;
QSlider* changeSpeed;
QLabel* dataShow_pwm_l,*dataShow_pwm_r,*dataShow_speed_l,*dataShow_speed_r;
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
    char command[50];
    sprintf_s(command, sizeof(command), "PWM %.2f", (float)changeSpeed->value());
    sendCommandToESP32(command);
}
void _change_speed() {
    labelForSpeed->setNum(changeSpeed->value());
}
bool num_judge(char c) {
    return (c >= '0' && c <= '9');
}
void readData() {
    std::string data;
    if (!receiveDataFromESP32(data)) {
        return;
    }
    QString pwm_l,pwm_r,speed_l,speed_r;
    int p = data.find("PWM_L");
    for (int i = p; i < p + 10; i++) {
        if (num_judge(data[i])) {
            pwm_l.append(data[i]);
        }
    }
    p = data.find("PWM_R");
    for (int i = p; i < p + 10; i++) {
        if (num_judge(data[i])) {
            pwm_r.append(data[i]);
        }
    }
    p = data.find("Speed_L");
    for (int i = p; i < p + 10; i++) {
        if (num_judge(data[i])) {
            speed_l.append(data[i]);
        }
    }
    p = data.find("Speed_R");
    for (int i = p; i < p + 10; i++) {
        if (num_judge(data[i])) {
            speed_r.append(data[i]);
        }
    }
    pwm_l.append('\0');
    pwm_r.append('\0');
    speed_l.append('\0');
    speed_r.append('\0');
    dataShow_pwm_l->setText(pwm_l);
    dataShow_pwm_r->setText(pwm_r);
    dataShow_speed_l->setText(speed_l);
    dataShow_speed_r->setText(speed_r);
}

qt_for_car::qt_for_car(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    t = this;
    input();
    readData();//放在所有的槽函数下
    
    //LOGO
    QLabel *noc = new QLabel("FROM NOCTEVE", this);
    noc->setStyleSheet("QLabel{font: normal bold 20px;color:blue}");
    noc->move(380, 20);

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
    //labelForSpeed->move(200, 100);
    labelForSpeed->setNum(255);
    labelForSpeed->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    QLabel* pwm = new QLabel("PWM:", this);
    pwm->setStyleSheet("QLabel{font:normal bold 15px}");
    pwm->move(450, 335);
    labelForSpeed->move(498, 330);
    connect(changeSpeed, &QSlider::valueChanged, this, _change_speed);
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
    connect(quickLeft, &QPushButton::pressed, this, &qt_for_car::quick_left);
    connect(quickRight, &QPushButton::pressed, this, &qt_for_car::quick_right);

    QLabel* carState = new QLabel("State:", this);
    carState->setStyleSheet("QLabel{font:normal bold 15px}");
    carState->move(430, 300);
    labelForState = new QLabel("Stop",this);
    labelForState->resize(108, 30);
    labelForState->move(478, 295);
    labelForState->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    labelForState->setAlignment(Qt::AlignCenter);

    dataShow_pwm_l = new QLabel(this);
    dataShow_pwm_l->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    dataShow_pwm_l->resize(60, 30);
    dataShow_pwm_r = new QLabel(this);
    dataShow_pwm_r->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    dataShow_pwm_r->resize(60, 30);
    dataShow_speed_l = new QLabel(this);
    dataShow_speed_l->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    dataShow_speed_l->resize(60, 30);
    dataShow_speed_r = new QLabel(this);
    dataShow_speed_r->setStyleSheet("QLabel{font: normal bold 15px;color:black;border:1px solid #AAAAAA;background:white;}");
    dataShow_speed_r->resize(60, 30);
    QLabel* pwm_l, * pwm_r, * speed_l, * speed_r;
    pwm_l = new QLabel("PWM_L:", this);
    pwm_r = new QLabel("PWM_R:", this);
    speed_l = new QLabel("Speed_L:", this);
    speed_r = new QLabel("Speed_R:", this);
    pwm_l->setStyleSheet("QLabel{font:normal bold 15px}");
    pwm_r->setStyleSheet("QLabel{font:normal bold 15px}");
    speed_l->setStyleSheet("QLabel{font:normal bold 15px}");
    speed_r->setStyleSheet("QLabel{font:normal bold 15px}");
    pwm_l->move(210, 80);
    dataShow_pwm_l->move(280, 75);
    pwm_r->move(380, 80);
    dataShow_pwm_r->move(450, 75);
    speed_l->move(210, 150);
    dataShow_speed_l->move(280, 145);
    speed_r->move(380, 150);
    dataShow_speed_r->move(450, 145);
}

qt_for_car::~qt_for_car()
{}
