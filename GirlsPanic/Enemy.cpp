#include "Enemy.h"

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

Enemy::~Enemy()
{

}

void Enemy::EnermyAI()
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
