#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>

class TCarriage { // класс каретка
	const float dx = 0.05f; // скорость
	float x; // положение по х
	float y; // положение по у
	float length = 0.2f; // ширина
public:
	TCarriage() { x = 0; y = -0.95f; } 

	void DrawObj(); // нарисовать объект
	void Move(char left, char right, float borderL, float borderR); // движение каретки

	float getX() { return x; } 
	float getY() { return y; }
	float getLength() { return length; }
};

