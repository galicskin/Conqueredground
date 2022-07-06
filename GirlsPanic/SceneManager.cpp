#include "SceneManager.h"

using namespace Gdiplus;

SceneManager::SceneManager()
{
	img = nullptr;
	where = 0;
}

SceneManager::~SceneManager()
{
}

void SceneManager::DrawScene(HDC hdc, RECT Clientrc)
{ 
	
	Graphics graphics(hdc);


	REAL transparency = 0.7f;
	ImageAttributes imgAttr;// ���İ� ����
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //��������� ���İ�: 4,4 �κ�
			0.0f,0.0f,0.0f,0.0f,1.0f, //��������� ���� ������ 4�κ��� ������
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = img->GetWidth();
	int h = img->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(img, Rect((Clientrc.right-Clientrc.left-w)/2, (Clientrc.bottom-Clientrc.top-h)/2, w , h ), 0, 0, w, h, UnitPixel, &imgAttr);

}



void SceneManager::NextScene()
{
	where++;
}

void SceneManager::DrawPalyer(HDC hdc,PlayerData player)
{
	Graphics graphics(hdc);


	REAL transparency = 0.7f;
	ImageAttributes imgAttr;// ���İ� ����
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //��������� ���İ�: 4,4 �κ�
			0.0f,0.0f,0.0f,0.0f,1.0f, //��������� ���� ������ 4�κ��� ������
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = img->GetWidth();
	int h = img->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(img, Rect(player.xCursor-(w/2) , player.yCursor-(h / 2), w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}

void SceneManager::EnemyDraw(HDC hdc, Enemy enemy)
{
	Graphics graphics(hdc);


	REAL transparency = 0.7f;
	ImageAttributes imgAttr;// ���İ� ����
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //��������� ���İ�: 4,4 �κ�
			0.0f,0.0f,0.0f,0.0f,1.0f, //��������� ���� ������ 4�κ��� ������
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = img->GetWidth();
	int h = img->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(img, Rect(enemy.GetxCursor() - (w / 2), enemy.GetyCursor() - (h / 2), w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}


