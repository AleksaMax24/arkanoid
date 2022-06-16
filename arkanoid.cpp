#include "arkanoid.hpp"


void ArkanoidGame::InitBricks() { // заполняем вектор bricks кирпичиками на определенных позициях
	float startX = -0.9f;
	float startY = 0.8f;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 2 && j > 1 && j < 8) {
				bricks.push_back(new TBrickUnbrkbl(startX + j * 0.2f, startY - i * 0.1f));
			}
			else if (j == 0 || j == 9) {
				bricks.push_back(new TBrickSpeedup(startX + j * 0.2f, startY - i * 0.1f));
			}
			else {
				bricks.push_back(new TBrick(startX + j * 0.2f, startY - i * 0.1f));
			}
		}
	}
};

void ArkanoidGame::InitLifes() { // инициализируем 3 жизни
	for (int k = 0; k < 3; k++) {
		lifes.push_back(new TBall(-1.1f - k * 0.1f, 0.9f));
	}
}

ArkanoidGame::ArkanoidGame() { // конструктор игры
	balls.push_back(new TBall(0.0f, -0.9f));
	InitBricks();
	InitLifes();
}


void ArkanoidGame::MoveBalls() { // движение мячиков
	BallsCollision(); 
	for (size_t i = 0; i < balls.size(); i++) { 
		balls[i]->DrawObj();
		if (balls[i]->Move(carriage, bricks, bonuses, score)) {
			if (balls.size() == 2) { 
				delete balls[i]; 
				balls.erase(balls.begin() + i);
			}
			else { 
				if (!lifes.empty()) { 
					score -= 10;
					lifes.pop_back(); 
					delete balls[i]; 
					balls.erase(balls.begin() + i);
					balls.push_back(new TBall(carriage.getX(), carriage.getY() + 0.1f)); 
				}
				else exit(1); 
			}
		}
	}
}

void ArkanoidGame::MoveCarriage() { // движение каретки
	carriage.DrawObj();
	carriage.Move('A', 'D', -1.0f, 1.0f); // двигаем на клавиши А D
}

void ArkanoidGame::MoveBonuses() { // движение бонусов
	for (size_t i = 0; i < bonuses.size(); i++) { 
		bonuses[i]->DrawObj();
		if (bonuses[i]->Move(carriage, bricks, balls, score)) { 
			delete bonuses[i];
			bonuses.erase(bonuses.begin() + i);
		}
	}
}

void ArkanoidGame::DrawLifes() { // рисуем жизни
	std::vector<TBall*>::iterator it = lifes.begin();
	for (; it != lifes.end(); it++) {
		(*it)->DrawObj();
	}
}

void ArkanoidGame::DrawBricks() { // рисуем кирпичики
	std::vector<TBrick*>::iterator it = bricks.begin();
	for (; it != bricks.end(); it++) {
		(*it)->DrawObj();
		(*it)->Move();
	}
}

void ArkanoidGame::BallsCollision() { // столкновение мячей
	if (balls.size() == 2) { 
		if (balls[0]->IsCrossPoint(balls[1]->getX(), balls[1]->getY(), 2 * balls[1]->getRadius())) {
			balls[0]->Mirror(balls[1]->getX(), balls[1]->getY());
			balls[1]->Mirror(balls[0]->getX(), balls[0]->getY());
		}
	}
}
