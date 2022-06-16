#include "ball.hpp"
#include "carriage.hpp"
#include "bricks.hpp"



int sgn(float val) 
{
	return (val > 0) ? (1) : ((val < 0) ? (-1) : (0));
}

bool TBall::ReflectCarriage(TCarriage& carriage) { // отражение от каретки
	
	if (((x + radius > carriage.getX() - carriage.getLength() &&  // если мячик внутри левой границы
		x - radius < carriage.getX() + carriage.getLength())) && // если мячик внутри правой границы
		IsCrossLine(carriage.getX() - carriage.getLength(), carriage.getY(), // и если мячик пересекает линию каретки
			carriage.getX() + carriage.getLength(), carriage.getY()))
	{
		dx = sgn(dx) * speedcomp;
		dy = sgn(dy) * speedcomp;
		dy *= -1;
		float speed = float(sqrt(dy * dy + dx * dx));
		if (x > carriage.getX()) { // если мячик правее каретки
			dy = float(cos(((x - carriage.getX()) / carriage.getLength()) * M_PI_4) * speed);
			dx = float(sin(((x - carriage.getX()) / carriage.getLength()) * M_PI_4) * speed);
		}
		else if (x < carriage.getX()) {
			dy = float(cos(((carriage.getX() - x) / carriage.getLength()) * M_PI_4) * speed);
			dx = float(-sin(((carriage.getX() - x) / carriage.getLength()) * M_PI_4) * speed);
		}
		return true;
	}
	return false;
}

bool TBall::IsCrossPoint(float x1, float y1, float r)
{
	
	return (x - x1) * (x - x1) + (y - y1) * (y - y1) < r * r;
}

bool TBall::IsCrossLine(float x1, float y1, float x2, float y2) {
	float A = y2 - y1;
	float B = x1 - x2;
	float C = x2 * y1 - x1 * y2;
	return fabs(A * x + B * y + C) / sqrt(A * A + B * B) <= radius;

}

void TBall::Mirror(float x1, float y1)
{
	float ballvec = float(atan2(dx, dy)); // вектор движения шарика
	float crossvec = float(atan2(x - x1, y - y1)); // вектор столкновения шарика и точки

	float resvec = float(M_PI - ballvec + crossvec * 2.0f); // результирующий вектор столкновения
	float speed = float(sqrt(dx * dx + dy * dy)); // модуль скорости

	// получаем новые компоненты скорости по осям Y и X
	dx = float(sin(resvec) * speed);
	dy = float(cos(resvec) * speed);
}

const int BONUS_CHANCE = 10;


bool TBall::ReflectBricks(std::vector<TBrick*>& bricks, std::vector <TBonus*>& bonuses, int& score)
{
	if (!bricks.empty()) {
		float height_2 = bricks[0]->getHeight() / 2.0f;
		float width_2 = bricks[-0]->getWidth() / 2.0f;

		for (size_t i = 0; i < bricks.size(); i++)
		{
			if (x > bricks[i]->getX() - width_2 && x < bricks[i]->getX() + width_2 &&
				IsCrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() - height_2))
			{
				dy *= -1;
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			if (y > bricks[i]->getY() - height_2 && y < bricks[i]->getY() + height_2 &&
				IsCrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2,
					bricks[i]->getX() - width_2, bricks[i]->getY() + height_2)) {
				dx *= -1;
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			if (x > bricks[i]->getX() - width_2 && x < bricks[i]->getX() + width_2 &&
				IsCrossLine(bricks[i]->getX() - width_2, bricks[i]->getY() + height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() + height_2)) {
				dy *= -1;
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			if (y > bricks[i]->getY() - height_2 && y < bricks[i]->getY() + height_2 &&
				IsCrossLine(bricks[i]->getX() + width_2, bricks[i]->getY() + height_2,
					bricks[i]->getX() + width_2, bricks[i]->getY() - height_2)) {
				dx *= -1;
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			
			if (IsCrossPoint(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2, radius)) {
				Mirror(bricks[i]->getX() - width_2, bricks[i]->getY() - height_2);
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			if (IsCrossPoint(bricks[i]->getX() - width_2, bricks[i]->getY() + height_2, radius)) {
				Mirror(bricks[i]->getX() - width_2, bricks[i]->getY() + height_2);
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			if (IsCrossPoint(bricks[i]->getX() + width_2, bricks[i]->getY() + height_2, radius)) {
				Mirror(bricks[i]->getX() + width_2, bricks[i]->getY() + height_2);
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
			if (IsCrossPoint(bricks[i]->getX() + width_2, bricks[i]->getY() - height_2, radius)) {
				Mirror(bricks[i]->getX() + width_2, bricks[i]->getY() - height_2);
				if (bricks[i]->lifesAway(*this, score)) {
					if (rand() % BONUS_CHANCE == 1) {
						bonuses.push_back(new TBonus(bricks[i]->getX(), bricks[i]->getY()));
					}
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
				return true;
			}
		}
	}
	return false;
}

bool TBall::Move(TCarriage& carriage, std::vector<TBrick*>& bricks, std::vector<TBonus*>& bonuses, int& score) {
	x += dx; 
	y += dy; 


	ReflectCarriage(carriage);

	ReflectBricks(bricks, bonuses, score);

	
	if (IsCrossLine(-1, 1, 1, 1)) 
	{
		dy *= -1; 
		return false;
	}
	if (IsCrossLine(-1, -1, 1, -1))  
	{
		dy *= -1; 
		return true; 
	}
	if (IsCrossLine(-1, -1, -1, 1)) 
	{
		dx *= -1; 
		return false;
	}
	if (IsCrossLine(1, -1, 1, 1)) 
	{
		dx *= -1;
		return false;
	}
	return false;
}

const int BALL_OR_BRICK = 2;

bool TBonus::Move(TCarriage& carriage, std::vector<TBrick*>& bricks, std::vector<TBall*>& ballz, int& score) { // шарик бонуса

	dy += ddy;
	y += dy; 

	if (ReflectCarriage(carriage)) { 
		score += 5; 
		if (rand() % BALL_OR_BRICK == 1 && ballz.size() < 2) { // 50 на 50, выпадает второй шарик или двигающийся кирпич
			ballz.push_back(new TBall(0.0f, -0.9f));
		}
		else {
			bricks.push_back(new TBrickFlying());
		}
		return true;
	}

	
	if (IsCrossLine(-1, -1, 1, -1)) {
		return true;
	}
	return false;
}

