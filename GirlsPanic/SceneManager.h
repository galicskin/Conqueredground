#pragma once

#include "framework.h"
#include <ole2.h>
#include <winnt.h>
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")

#include "GameManager.h"
#include "Enemy.h"
// Gdi

class SceneManager 
{
private:
	Gdiplus::Image *img;
	int where;
public:
	SceneManager();
	~SceneManager();

	
	virtual void DrawScene(HDC hdc, RECT Clientrc);
	void NextScene();
	void DrawPalyer(HDC hdc,PlayerData player);
	void EnemyDraw(HDC hdc, Enemy enemy);
};