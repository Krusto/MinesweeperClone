#include "WindowsFunctions.h"

void GotoXY(SHORT x, SHORT y)// функция която казва на курсора да отиде на x,y
{
	COORD cursorPosition; // точка с позицията на курсора
	cursorPosition.X = x; // задаваме х на курсора
	cursorPosition.Y = y; // задаваме у на курсора
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition); // взимаме сегашната конзола и казваме да смени позицията на курсора

}

POINT GetCursorPosition() // функция която взима позицията на курсора
{
	POINT pos{}; // точка на която е курсора
	GetCursorPos(&pos); // взимаме позицията на курсора
	return pos; // връщаме резултат който е позицията на курсора
}

void ClearScreen()// функция която изчиства дисплея
{
	system("cls"); // задаваме команда в конзолата която чисти екрана
}

void ShowConsoleCursor(bool showFlag)// функция която задава флаг на курсора дали да се вижда
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // взимаме сегашната конзола

	CONSOLE_CURSOR_INFO     cursorInfo; // структура която държи инфо за курсора

	GetConsoleCursorInfo(out, &cursorInfo); // взимаме информация за курсора
	cursorInfo.bVisible = showFlag; // задаваме флаг дали да се вижда курсора
	SetConsoleCursorInfo(out, &cursorInfo); // казваме конзолата за сложи тази информация на курсора
}
