#include "serial.h"
#include <iostream>
#include <windows.h>

extern HANDLE hSerial;
HANDLE hSerial;
bool initSerialPort(const std::wstring& portName, DWORD baudRate) {
    hSerial = CreateFile(portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,    // 不共享
        NULL, // 默认安全属性
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    /*if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port." << std::endl;
        return false;
    }*/

    // 设置波特率、数据位、停止位等
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = baudRate; // 使用传入的波特率
    dcbSerialParams.ByteSize = 8;          // 8个数据位
    dcbSerialParams.StopBits = ONESTOPBIT; // 1个停止位
    dcbSerialParams.Parity = NOPARITY;     // 无奇偶校验

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port parameters." << std::endl;
        CloseHandle(hSerial);
        return false;
    }

    return true;
}

void sendCommandToESP32(const char* command) {
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Serial port not initialized." << std::endl;
        return;
    }

    DWORD bytesWritten;
    WriteFile(hSerial, command, strlen(command), &bytesWritten, NULL);
    WriteFile(hSerial, "\r\n", 2, &bytesWritten, NULL);
}

bool receiveDataFromESP32(std::string& receivedData) {
    char buffer[256];
    DWORD bytesRead = 0;

    if (ReadFile(hSerial, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        receivedData = buffer;
        return true;
    }
    return false;
}

void closeSerialPort() {
    CloseHandle(hSerial);
}

//void processSerialData(std::string& ledStatus, double& ledBlinkFrequency) {
//    std::string receivedData;
//    if (receiveDataFromESP32(receivedData)) {
//        // 调试输出
//        std::cout << "Received Data: " << receivedData << std::endl;
//        system("pause");
//
//        if (receivedData.find("LED ON") != std::string::npos) {
//            ledStatus = "打开";
//        }
//        else if (receivedData.find("LED OFF") != std::string::npos) {
//            ledStatus = "关闭";
//        }
//        else if (receivedData.find("LED BLINK") != std::string::npos) {
//            std::string frequencyStr = receivedData.substr(receivedData.find("at ") + 3);
//            ledBlinkFrequency = atof(frequencyStr.c_str());
//        }
//    }
//}