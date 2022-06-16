#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <math.h>
#include <vector>


class TBall; // ссылка на класс

class TBrick { // класс кирпич
protected:
	float x;
	float y;
	const float height = 0.1f, width = 0.2f; // высота и ширина
	int lifes = 3; // жизни у кирпича
public:
	TBrick(float brickX, float brickY); // конструктор

	virtual void DrawObj(); // рисовка

	virtual bool lifesAway(TBall& ball, int& score); // взаимодействие с м€сиками игрока

	virtual void Move() {} // движение - функци€ с пустым телом

	float getX() { return x; } 
	float getY() { return y; }
	float getHeight() { return height; }
	float getWidth() { return width; }

};


class TBrickUnbrkbl : public TBrick { // кирпич неразрушаемый
public:
	TBrickUnbrkbl(float brickX, float brickY) : TBrick(brickX, brickY) {} 

	virtual void DrawObj(); // рисовка

	virtual bool lifesAway(TBall& ball, int& score); // взаимодействие м€чиками игрока

};

class TBrickSpeedup : public TBrick { // кирпич ускор€ющи
public:
	TBrickSpeedup(float brickX, float brickY) : TBrick(brickX, brickY) {} 
	virtual void DrawObj();

	virtual bool lifesAway(TBall& ball, int& score); // взаимодействие м€чиками игрока

};

class TBrickFlying : public TBrick { // бонусный кипич
	float dx; // имеет скорость
public:
	TBrickFlying() : TBrick(-0.6f, -0.6f) { dx = 0.001f; }
	void Move(); // имеет свою функцию движени€


};
