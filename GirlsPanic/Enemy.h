#pragma once
#include <windows.h>
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")


class Enemy
{
private:
	int xCursor;
	int yCursor;
	int velocity;
	Gdiplus::Image *EnemyImg;
public:
	Enemy();
	Enemy(int x, int y, int V );
	~Enemy() { delete EnemyImg; }
	void EnermyAI();
	int GetxCursor();
	int GetyCursor();
	Gdiplus::Image* GetEnemyImage();

};