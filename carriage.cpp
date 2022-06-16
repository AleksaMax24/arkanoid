#include "carriage.hpp"

void TCarriage::Move(char left, char right, float borderL, float borderR) // передвижение каретки
{
	if (GetKeyState(left) < 0) x -= dx; 
	else if (GetKeyState(right) < 0) x += dx; 

	if (x - length < borderL) x = borderL + length; // проверка на выход за границы
	if (x + length > borderR) x = borderR - length;
}