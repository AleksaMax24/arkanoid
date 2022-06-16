#pragma once
#include "ball.hpp"
#include "carriage.hpp"
#include "bricks.hpp"
#include <vector>

const int windowW = 768; 
const int windowH = 512; 

class ArkanoidGame {// класс игры арканоид
	std::vector<TBall*> balls; 
	std::vector<TBall*> lifes; 

	TCarriage carriage; 
	std::vector <TBrick*> bricks; 
	std::vector <TBonus*> bonuses;
	int score = 0; 
public:

	void InitBricks();
	void InitLifes();

	ArkanoidGame();

	void MoveBalls();   
	void MoveCarriage();
	void MoveBonuses(); 

	void BallsCollision(); 

	void DrawFrames(); 
	void DrawBricks();
	void DrawLifes();
	


	void ShowScore();
};
