#pragma once
#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <string>

bool initSerialPort(const std::wstring& portName, DWORD baudRate);
void sendCommandToESP32(const char* command);
bool receiveDataFromESP32(std::string& receivedData);
void processSerialData(std::string& ledStatus, double& ledBlinkFrequency);
void closeSerialPort();

#endif // SERIAL_H
#pragma once
