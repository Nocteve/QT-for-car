#include "qt_for_car.h"
#include <iostream>
#include <QtWidgets/QApplication>

//void openTerminal()
//{
//    AllocConsole(); // 打开控制台
//    FILE* pCOut;
//    freopen_s(&pCOut, "CONOUT$", "w", stdout);
//}
int main(int argc, char *argv[])
{
    //openTerminal();
    QApplication a(argc, argv);
    qt_for_car w;
    w.show();
    return a.exec();
}
