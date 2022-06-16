#pragma once
#include "bricks.hpp"
#include "ball.hpp"

TBrick::TBrick(float brickX, float brickY) {
	x = brickX; y = brickY;
}

bool TBrick::lifesAway(TBall& ball, int& score) // �������������� � �������� ������
{
	lifes--;
	score++; 
	if (lifes == 0) { 
		score++;
		return true;
	}
	return false;
}

bool TBrickUnbrkbl::lifesAway(TBall& ball, int& score) { // ������������ ���� ������ ������� ��� �������
	return false;
}

float const SPEED_UP = 0.0005f; // ���������� �������� 

bool TBrickSpeedup::lifesAway(TBall& ball, int& score) {  // �������������� �������� ������
	lifes--;
	score++;
	ball.multSpeed(SPEED_UP); 
	if (lifes == 0) {
		score++;
		return true;
	}
	return false;
}

void TBrickFlying::Move() { // �������� ����������� ���������
	x += dx;
	if (x < getWidth() - 1) { 
		dx *= -1;
	}
	if (x > 1 - getWidth()) {
		dx *= -1;
	}
}
