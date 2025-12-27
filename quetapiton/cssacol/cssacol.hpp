#include <iostream>
#include <string>
#include <windows.h>

inline void create_text_color(int crhb, std::string text, HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE)) {
    SetConsoleTextAttribute(hconsole, crhb);
    std::cout << text;
}