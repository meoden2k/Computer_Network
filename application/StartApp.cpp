#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <string>
#include "ConvertString.cpp"

void StartApplication(std::string app) {
    // Chuyển đổi std::string sang std::wstring
    std::wstring wapp = ToWString(app);
    // Gọi ShellExecuteW để mở ứng dụng
    ShellExecuteW(NULL, L"open", wapp.c_str(), NULL, NULL, SW_SHOWNORMAL);

}