#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")

// Gdi

class SceneManager
{
private:
	Image img;
	int where;
public:
	SceneManager();
	~SceneManager();

	
	virtual void DrawScene(HDC hdc, RECT Clientrc);
	void NextScene();
	void DrawPalyer(HDC hdc,PlayerData player);
	void DrawEnermy(HDC hdc,EnemyData enermy);
};