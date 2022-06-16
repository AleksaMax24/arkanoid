#include "carriage.hpp"
#include "bricks.hpp"
#include "ball.hpp"
#include "arkanoid.hpp"

int const GREEN = 3;
int const YELLOW = 2;
int const RED = 1;

void TCarriage::DrawObj()  // рисуем белую каретку
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 1);
	glVertex2f(x - length, y);
	glVertex2f(x - length, y + 0.01f);
	glVertex2f(x, y + 0.025f);
	glVertex2f(x + length, y + 0.01f);
	glVertex2f(x + length, y);
	glEnd();
}

void TBrick::DrawObj() { // рисуем кирпичик
	glBegin(GL_TRIANGLE_FAN);
	if (lifes == GREEN) { // если все 3 жизни, то зеленый
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else if (lifes == YELLOW) { // если жизней 2, то желтый
		glColor3f(1.0f, 1.0f, 0.0f);
	}
	else if (lifes == RED) { // если жизнь 1, то красный
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING);
	glColor3f(1, 1, 1);
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();
}

void TBrickUnbrkbl::DrawObj() { // серый неразрушаемый кирпичик
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING);
	glColor3f(1, 1, 1);
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();
}

void TBrickSpeedup::DrawObj() {
	glBegin(GL_TRIANGLE_FAN);
	if (lifes == GREEN) {
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else if (lifes == YELLOW) {
		glColor3f(1.0f, 1.0f, 0.0f);
	}
	else if (lifes == RED) {
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GGL_STRING);
	glColor3f(1, 1, 1);
	glVertex2f(x - width * 0.5f, y - height * 0.5f);
	glVertex2f(x - width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y + height * 0.5f);
	glVertex2f(x + width * 0.5f, y - height * 0.5f);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.75f, 1.0f);
	glVertex2f(x - width * 0.3f, y - height * 0.1f);
	glVertex2f(x - width * 0.3f, y + height * 0.1f);
	glVertex2f(x + width * 0.1f, y + height * 0.1f);
	glVertex2f(x + width * 0.1f, y - height * 0.1f);
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0f, 0.75f, 1.0f);
	glVertex2f(x + width * 0.1f, y - height * 0.2f);
	glVertex2f(x + width * 0.3f, y);
	glVertex2f(x + width * 0.1f, y + height * 0.2f);
	glEnd();

}


void TBall::DrawObj() { // рисуем м€чик
	float x0;
	float y0;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 1);
	float cnt = 40;
	float alpha = 3.1415926f * 2.0f / cnt;
	for (int i = -1; i < cnt; i++) {
		x0 = (float)sin((double)alpha * (double)i) * radius;
		y0 = (float)cos((double)alpha * (double)i) * radius;
		glVertex2f(x0 + x, y0 + y);
	}
	glColor3f(0.5f, 0.5f, 0.5f);
	glPointSize(2);
	for (int i = -1; i < cnt; i++) {
		x0 = (float)sin((double)alpha * (double)i) * radius;
		y0 = (float)cos((double)alpha * (double)i) * radius;
		glVertex2f(x0 + x, y0 + y);
	}
	glEnd();
}

void TBonus::DrawObj() { // рисуем бонус
	float x0;
	float y0;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 0.75, 0);
	float cnt = 100;
	float alpha = 3.1415926f * 2.0f / cnt;
	for (int i = -1; i < cnt; i++) {
		x0 = (float)sin((double)alpha * (double)i) * radius;
		y0 = (float)cos((double)alpha * (double)i) * radius;
		glVertex2f(x0 + x, y0 + y);
	}
	glEnd();
}



void ArkanoidGame::DrawFrames() { // рисуем рамку дл€ игры
	glBegin(GGL_STRING);
	glColor3f(0, 0, 1);
	glVertex2f(-1, -1);
	glVertex2f(-1, 1);
	glVertex2f(1, 1);
	glVertex2f(1, -1);
	glEnd();

}

// линии дл€ прорисовки цифр на определенном месте в игре
static void Line1(float x1, float y1, float x2, float y2) {
	glVertex2f(x1 / 4 - 1.22f, y1 / 4 + 0.6f);
	glVertex2f(x2 / 4 - 1.22f, y2 / 4 + 0.6f);
}

static void Line2(float x1, float y1, float x2, float y2) {
	glVertex2f(x1 / 4 - 1.37f, y1 / 4 + 0.6f);
	glVertex2f(x2 / 4 - 1.37f, y2 / 4 + 0.6f);
}

static void Line3(float x1, float y1, float x2, float y2) {
	glVertex2f(x1 / 4 - 1.52f, y1 / 4 + 0.6f);
	glVertex2f(x2 / 4 - 1.52f, y2 / 4 + 0.6f);
}

void ArkanoidGame::ShowScore() { // рисуем счет
	int score1 = score % 10;
	int score10 = (score / 10) % 10;
	int score100 = (score / 100) % 10;
	glLineWidth(3);
	glColor3f(0.75, 0, 1);
	glBegin(GL_LINES);
	if ((score1 != 1) && (score1 != 4)) Line1(0.3f, 0.85f, 0.7f, 0.85f);
	if ((score1 != 0) && (score1 != 1) && (score1 != 7)) Line1(0.3f, 0.5f, 0.7f, 0.5f);
	if ((score1 != 1) && (score1 != 4) && (score1 != 7)) Line1(0.3f, 0.15f, 0.7f, 0.15f);

	if ((score1 != 5) && (score1 != 6)) Line1(0.7f, 0.5f, 0.7f, 0.85f);
	if ((score1 != 2)) Line1(0.7f, 0.5f, 0.7f, 0.15f);

	if ((score1 != 1) && (score1 != 2) && (score1 != 3) && (score1 != 7)) Line1(0.3f, 0.5f, 0.3f, 0.85f);
	if ((score1 == 0) || (score1 == 2) || (score1 == 6) || (score1 == 8)) Line1(0.3f, 0.5f, 0.3f, 0.15f);
	glEnd();
	if (score > 9) {
		glBegin(GL_LINES);
		if ((score10 != 1) && (score10 != 4)) Line2(0.3f, 0.85f, 0.7f, 0.85f);
		if ((score10 != 0) && (score10 != 1) && (score10 != 7)) Line2(0.3f, 0.5f, 0.7f, 0.5f);
		if ((score10 != 1) && (score10 != 4) && (score10 != 7)) Line2(0.3f, 0.15f, 0.7f, 0.15f);

		if ((score10 != 5) && (score10 != 6)) Line2(0.7f, 0.5f, 0.7f, 0.85f);
		if ((score10 != 2)) Line2(0.7f, 0.5f, 0.7f, 0.15f);

		if ((score10 != 1) && (score10 != 2) && (score10 != 3) && (score10 != 7)) Line2(0.3f, 0.5f, 0.3f, 0.85f);
		if ((score10 == 0) || (score10 == 2) || (score10 == 6) || (score10 == 8)) Line2(0.3f, 0.5f, 0.3f, 0.15f);
		glEnd();
	}
	if (score > 99) {
		glBegin(GL_LINES);
		if ((score100 != 1) && (score100 != 4)) Line3(0.3f, 0.85f, 0.7f, 0.85f);
		if ((score100 != 0) && (score100 != 1) && (score100 != 7)) Line3(0.3f, 0.5f, 0.7f, 0.5f);
		if ((score100 != 1) && (score100 != 4) && (score100 != 7)) Line3(0.3f, 0.15f, 0.7f, 0.15f);

		if ((score100 != 5) && (score100 != 6)) Line3(0.7f, 0.5f, 0.7f, 0.85f);
		if ((score100 != 2)) Line3(0.7f, 0.5f, 0.7f, 0.15f);

		if ((score100 != 1) && (score100 != 2) && (score100 != 3) && (score100 != 7)) Line3(0.3f, 0.5f, 0.3f, 0.85f);
		if ((score100 == 0) || (score100 == 2) || (score100 == 6) || (score100 == 8)) Line3(0.3f, 0.5f, 0.3f, 0.15f);
		glEnd();
	}

}