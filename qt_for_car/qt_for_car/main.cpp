#include "qt_for_car.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_for_car w;
    w.show();
    return a.exec();
}
