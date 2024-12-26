#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

extern HANDLE hSerial;

bool initSerialPort(const std::wstring& portName, DWORD baudRate);
void sendCommandToESP32(const char* command);
bool receiveDataFromESP32(std::string& receivedData);
void closeSerialPort();

unsigned char calculateBCC(const unsigned char* data, size_t length);

#endif // SERIAL_H
#pragma once
