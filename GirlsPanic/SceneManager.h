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

enum Where { START = 0, STAGE1, STAGE2, STAGE3, PAUSE, END };

class SceneManager 
{
protected:
	Gdiplus::Image * background;
	int where;
public:
	SceneManager();
	virtual ~SceneManager() { delete background; }

	int GetWhere();
	virtual void SetImg(Gdiplus::Image* newback);
	void DrawBackground(HDC hdc, RECT Clientrc);
	//void NextScene(int& WHERE) { WHERE++; }
	void DrawPlayer(HDC hdc, GameManager gm);
	void EnemyDraw(HDC hdc, Enemy enemy);
	
	
	void RESize(RECT Clientrc);
	virtual void DrawStage(HDC hdc, RECT Clienctrc);

};

class StartScene : public SceneManager
{
private:
	Gdiplus::Image* StartImg;
public:
	StartScene();
	virtual ~StartScene() { delete StartImg; }

	void SetImg(Gdiplus::Image* img);
	void DrawStart(HDC hdc, RECT Clienctrc);
};

class Stage1 : public SceneManager
{
private:
	Gdiplus::Image* Stage1Img;
public:
	Stage1();
	virtual ~Stage1() { delete Stage1Img; }

	void SetImg(Gdiplus::Image* img);
	void DrawStage(HDC hdc, RECT Clienctrc);
};

class EndScene : public SceneManager
{
private:
	Gdiplus::Image* EndImg;
public:
	EndScene();
	virtual ~EndScene() { delete EndImg; }

	void SetImg(Gdiplus::Image* img);
	void DrawEnd(HDC hdc);
};