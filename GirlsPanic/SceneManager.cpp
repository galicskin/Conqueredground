#include "SceneManager.h"

using namespace Gdiplus;



SceneManager::SceneManager()
{
	background = nullptr;
	where = 0;
}



int SceneManager::GetWhere()
{
	return where;
}

void SceneManager::SetImg(Gdiplus::Image* newback)
{
	background = newback;
}

void SceneManager::DrawBackground(HDC hdc,RECT Clientrc)
{ 
	
	Graphics graphics(hdc);


	REAL transparency = 0.5f;
	ImageAttributes imgAttr;// 알파값 관련
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //단위행렬중 알파값: 4,4 부분
			0.0f,0.0f,0.0f,0.0f,1.0f, //단위행렬쪽 말고 나머지 4부분은 밝기관련
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = background->GetWidth();
	int h = background->GetHeight();

	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(background, Rect(0, 0, Clientrc.right, Clientrc.bottom), 0, 0, w, h, UnitPixel, &imgAttr);

}




void SceneManager::DrawPlayer(HDC hdc,GameManager gm)
{
	Graphics graphics(hdc);


	REAL transparency = 0.7f;
	ImageAttributes imgAttr;// 알파값 관련
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //단위행렬중 알파값: 4,4 부분
			0.0f,0.0f,0.0f,0.0f,1.0f, //단위행렬쪽 말고 나머지 4부분은 밝기관련
	};
	imgAttr.SetColorMatrix(&colorMatrix);
	
	int w = gm.GetPlayerImage()->GetWidth();
	int h = gm.GetPlayerImage()->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(gm.GetPlayerImage(), Rect(gm.GetPlayerData().xCursor -(w/2) , gm.GetPlayerData().yCursor -(h / 2), w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}

void SceneManager::EnemyDraw(HDC hdc, Enemy enemy)
{
	Graphics graphics(hdc);


	REAL transparency = 0.7f;
	ImageAttributes imgAttr;// 알파값 관련
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //단위행렬중 알파값: 4,4 부분
			0.0f,0.0f,0.0f,0.0f,1.0f, //단위행렬쪽 말고 나머지 4부분은 밝기관련
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = enemy.GetEnemyImage()->GetWidth();
	int h = enemy.GetEnemyImage()->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(enemy.GetEnemyImage(), Rect(enemy.GetxCursor() - (w / 2), enemy.GetyCursor() - (h / 2), w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}

void SceneManager::RESize(RECT Clientrc)
{
	Point LU = { Clientrc.right / 4 , Clientrc.bottom / 10 };
	Point RU = { Clientrc.right *3/ 4 , Clientrc.bottom *9/ 10 };
	Point LL = { Clientrc.right / 4 ,Clientrc.bottom * 9 / 10 };
	Point destinationPoints[] = { LU, RU, LL };
	
}

void SceneManager::DrawStage(HDC hdc,RECT Clienctrc)
{
}

StartScene::StartScene()
{
	StartImg = nullptr;
	where = START;
}







void StartScene::SetImg(Gdiplus::Image* img)
{
	StartImg = img;
}

void StartScene::DrawStart(HDC hdc, RECT Clienctrc)
{
	Graphics graphics(hdc);

	REAL transparency = 0.5f;
	ImageAttributes imgAttr;// 알파값 관련
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //단위행렬중 알파값: 4,4 부분
			0.0f,0.0f,0.0f,0.0f,1.0f, //단위행렬쪽 말고 나머지 4부분은 밝기관련
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = StartImg->GetWidth();
	int h = StartImg->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(StartImg, Rect((Clienctrc.right - Clienctrc.left - w) / 2, (Clienctrc.bottom - Clienctrc.top - h) / 2, w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}


Stage1::Stage1()
{
	where = STAGE1;
}



void Stage1::SetImg(Gdiplus::Image* img)
{
	Stage1Img = img;
}

void Stage1::DrawStage(HDC hdc, RECT Clienctrc)
{
	Graphics graphics(hdc);


	REAL transparency = 0.5f;
	ImageAttributes imgAttr;// 알파값 관련
	ColorMatrix colorMatrix =
	{
			1.0f,0.0f,0.0f,0.0f,0.0f,   // r
			0.0f,1.0f,0.0f,0.0f,0.0f,   // g
			0.0f,0.0f,1.0f,0.0f,0.0f,   // b
			0.0f,0.0f,0.0f,transparency,0.0f,  //단위행렬중 알파값: 4,4 부분
			0.0f,0.0f,0.0f,0.0f,1.0f, //단위행렬쪽 말고 나머지 4부분은 밝기관련
	};
	imgAttr.SetColorMatrix(&colorMatrix);

	int w = Stage1Img->GetWidth();
	int h = Stage1Img->GetHeight();
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(Stage1Img, Rect((Clienctrc.right- Clienctrc.left - w) / 2, (Clienctrc.bottom - Clienctrc.top - h) / 2 , w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}

EndScene::EndScene()
{
	where = END;
}




void EndScene::SetImg(Gdiplus::Image* img)
{
	EndImg = img;
}

void EndScene::DrawEnd(HDC hdc)
{

}
