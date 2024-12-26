#include "serial.h"
#include <iostream>
#include <windows.h>


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

unsigned char calculateBCC(const unsigned char* data, size_t length) {
    unsigned char bcc = 0x00;  // ��ʼ��BCCֵΪ0
    for (size_t i = 0; i < length; i++) {
        bcc ^= data[i];  // ��ÿ���ֽڽ����������
    }
    return bcc;
}

