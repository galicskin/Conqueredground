#pragma once
#include <windows.h>
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
//#include "GameManager.h" -> 서로 선언을 해준다면 충돌이 일어나서 컴파일이 안됨. 가능한 cpp 에 #include를 해줘야함
//class GameManager; -> 전방선언을 통해 include를 이용하지않고 GameManager(원하는 class) 를 알릴수 있다.




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
	void EnemyAI();
	int GetxCursor();
	int GetyCursor();
	Gdiplus::Image* GetEnemyImage();
	
	

	//void fkadsljkal(class GameManager GM); 앞에서 전방선언과 같은 원리이지만 좀 더 보기 및 사용하기 편하다.

};