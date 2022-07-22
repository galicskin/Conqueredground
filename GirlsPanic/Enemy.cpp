#include "Enemy.h"
#include "GameManager.h"
#include <time.h>
using namespace Gdiplus;

Enemy::Enemy()
{
	xCursor=0;
	yCursor=0;
	velocity=0;
	EnemyImg=nullptr;
}

Enemy::Enemy(int x,int y,int V)
{
	xCursor = x;
	yCursor = y;
	velocity = V;
	EnemyImg = nullptr;
}



void Enemy::SetImg(Gdiplus::Image* img)
{
	EnemyImg = img;
}

void Enemy::EnemyinitPos(int x, int y)
{
	xCursor = x;
	yCursor = y;
}

void Enemy::EnemySetVelocity(int v)
{
	velocity = v;
}

void Enemy::EnemyAI(DWORD newTime, class GameManager GM)
{
	srand(time(NULL));


	switch (rand() % 4)
	{
		case 0:
		xCursor += 1;
		break;
		case 1:
		xCursor -=1;
		break;
		case 2:
		yCursor += 1;
		break;
		case 3:
		yCursor -= 1;
		break;
	}

}

int Enemy::GetxCursor()
{
	return xCursor;
}

int Enemy::GetyCursor()
{
	return yCursor;
}

Gdiplus::Image* Enemy::GetEnemyImage()
{
	return EnemyImg;
}


