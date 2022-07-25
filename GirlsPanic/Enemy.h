#pragma once
#include <windows.h>
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
//#include "GameManager.h" -> ���� ������ ���شٸ� �浹�� �Ͼ�� �������� �ȵ�. ������ cpp �� #include�� �������
//class GameManager; -> ���漱���� ���� include�� �̿������ʰ� GameManager(���ϴ� class) �� �˸��� �ִ�.






class Enemy
{
private:
	int xCursor;
	int yCursor;
	POINT velocity;
	Gdiplus::Image *EnemyImg;
public:
	int EnemySizeControl;
	Enemy();
	Enemy(int x, int y, POINT V );
	~Enemy() { }

	
	void SetImg(Gdiplus::Image* img);
	void EnemyinitPos(int x, int y);
	void EnemySetVelocity(POINT v);
	void EnemyAI(DWORD newTime,class GameManager GM);
	int GetxCursor();
	int GetyCursor();
	Gdiplus::Image* GetEnemyImage();
	
	bool isColled(class GameManager GM);


	//void fkadsljkal(class GameManager GM); �տ��� ���漱��� ���� ���������� �� �� ���� �� ����ϱ� ���ϴ�.

};