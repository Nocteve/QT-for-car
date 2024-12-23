#include "serial.h"
#include <iostream>
#include <windows.h>

extern HANDLE hSerial;
HANDLE hSerial;
bool initSerialPort(const std::wstring& portName, DWORD baudRate) {
    hSerial = CreateFile(portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,    // ������
        NULL, // Ĭ�ϰ�ȫ����
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    /*if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port." << std::endl;
        return false;
    }*/

    // ���ò����ʡ�����λ��ֹͣλ��
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = baudRate; // ʹ�ô���Ĳ�����
    dcbSerialParams.ByteSize = 8;          // 8������λ
    dcbSerialParams.StopBits = ONESTOPBIT; // 1��ֹͣλ
    dcbSerialParams.Parity = NOPARITY;     // ����żУ��

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
//        // �������
//        std::cout << "Received Data: " << receivedData << std::endl;
//        system("pause");
//
//        if (receivedData.find("LED ON") != std::string::npos) {
//            ledStatus = "��";
//        }
//        else if (receivedData.find("LED OFF") != std::string::npos) {
//            ledStatus = "�ر�";
//        }
//        else if (receivedData.find("LED BLINK") != std::string::npos) {
//            std::string frequencyStr = receivedData.substr(receivedData.find("at ") + 3);
//            ledBlinkFrequency = atof(frequencyStr.c_str());
//        }
//    }
//}