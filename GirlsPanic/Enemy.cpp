#include "Enemy.h"
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



void Enemy::EnemyAI()
{
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


