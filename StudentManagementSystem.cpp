#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <regex>
#include <chrono>
#include <thread>
#include "admin.h"
#include "functions.h"
using namespace std;
void main_menu();
int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
    system("cls");
    main_menu();
    system("cls");
    system("pause");
    return 0;
}