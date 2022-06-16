#pragma once
#include "bricks.hpp"
#include "ball.hpp"

TBrick::TBrick(float brickX, float brickY) {
	x = brickX; y = brickY;
}

bool TBrick::lifesAway(TBall& ball, int& score) // взаимодействие с мячиками игрока
{
	lifes--;
	score++; 
	if (lifes == 0) { 
		score++;
		return true;
	}
	return false;
}

bool TBrickUnbrkbl::lifesAway(TBall& ball, int& score) { // неразрушимый блок нельзя сломать или удалить
	return false;
}

float const SPEED_UP = 0.0005f; // увеличение скорости 

bool TBrickSpeedup::lifesAway(TBall& ball, int& score) {  // взаимодействие мячиками игрока
	lifes--;
	score++;
	ball.multSpeed(SPEED_UP); 
	if (lifes == 0) {
		score++;
		return true;
	}
	return false;
}

void TBrickFlying::Move() { // движение движущегося кирпичика
	x += dx;
	if (x < getWidth() - 1) { 
		dx *= -1;
	}
	if (x > 1 - getWidth()) {
		dx *= -1;
	}
}
