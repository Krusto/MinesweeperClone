#pragma once
#include <Windows.h> // библиотека за манипулация на конзолата

void GotoXY(SHORT x, SHORT y); // функция която казва на курсора да отиде на x,y
POINT GetCursorPosition(); // функция която взима позицията на курсора
void ClearScreen(); // функция която изчиства дисплея
void ShowConsoleCursor(bool showFlag); // функция която задава флаг на курсора дали да се вижда
