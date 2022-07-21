#include "SceneManager.h"

using namespace Gdiplus;



SceneManager::SceneManager()
{
	background = nullptr;
	where = 0;
}

SceneManager::~SceneManager()
{
	
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


	REAL transparency = 1;
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
	
	int sizeControl_w = w / 10; //사이즈 컨트롤 
	int sizeControl_h = h / 10;
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(gm.GetPlayerImage(), Rect(gm.GetPlayerData().xCursor -(sizeControl_w /2) , gm.GetPlayerData().yCursor -(sizeControl_h / 2), sizeControl_w, sizeControl_h), 0, 0, w, h, UnitPixel, &imgAttr);



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

	int sizeControl_w = w / 10; //사이즈 컨트롤 
	int sizeControl_h = h / 10;

	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));
	graphics.DrawImage(enemy.GetEnemyImage(), Rect(enemy.GetxCursor() - (sizeControl_w / 2), enemy.GetyCursor() - (sizeControl_h / 2), sizeControl_w, sizeControl_h), 0, 0, w, h, UnitPixel, &imgAttr);

}

void SceneManager::RESize(RECT Clientrc)
{
	Point LU = { Clientrc.right / 4 , Clientrc.bottom / 10 };
	Point RU = { Clientrc.right *3/ 4 , Clientrc.bottom *9/ 10 };
	Point LL = { Clientrc.right / 4 ,Clientrc.bottom * 9 / 10 };
	Point destinationPoints[] = { LU, RU, LL };
	
}

void SceneManager::DrawStage(HDC hdc,RECT Clientrc)
{
}

StartScene::StartScene()
{
	StartImg = nullptr;
	where = START;
}

StartScene::~StartScene()
{
	
}







void StartScene::SetImg(Gdiplus::Image* img)
{
	StartImg = img;
}

void StartScene::DrawStart(HDC hdc, RECT Clientrc)
{
	Graphics graphics(hdc);

	REAL transparency = 1;
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
	graphics.DrawImage(StartImg, Rect((Clientrc.right - Clientrc.left - w) / 2, (Clientrc.bottom - Clientrc.top - h) / 2, w, h), 0, 0, w, h, UnitPixel, &imgAttr);



}


Stage1::Stage1()
{
	where = STAGE1;
}

Stage1::~Stage1()
{
	
}



void Stage1::SetImg(Gdiplus::Image* img)
{
	Stage1Img = img;
}

void Stage1::DrawStage(HDC hdc, RECT Clientrc)
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
	graphics.DrawImage(Stage1Img, Rect((Clientrc.right- Clientrc.left - w) / 2, (Clientrc.bottom - Clientrc.top - h) / 2 , w, h), 0, 0, w, h, UnitPixel, &imgAttr);

}

void Stage1::DrawCover(HDC hdc, GameManager gm)
{
	COLORREF color=RGB(255,255,255);
	HBRUSH hBrush, oldBrush;
	hBrush= CreateSolidBrush(color);
	oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	//gm.GetPolygonPoints();
	POINT*T=gm.GetPolygonPoints();
	Polygon(hdc, T, gm.GetPlayerData().Conquered->size);

	delete[] T;
	T = nullptr;
	SelectObject(hdc, oldBrush);
	DeleteObject(hBrush);

	




	/*
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
	graphics.DrawImage(Stage1Img, Rect((Clienctrc.right - Clienctrc.left - w) / 2, (Clienctrc.bottom - Clienctrc.top - h) / 2, w, h), 0, 0, w, h, UnitPixel, &imgAttr);
	*/
}

void Stage1::DrawLine(HDC hdc, std::stack<POINT> T, GameManager GM)
{
	int Size = T.size() + 1;
	POINT* line = new POINT[Size];
	

	line[0] = { GM.GetPlayerData().xCursor,GM.GetPlayerData().yCursor };

	for (int i=1 ; i < Size; i++)
	{
		line[i] = T.top();
		T.pop();
	
	}

	Polyline(hdc, line, Size);
	
	delete[] line;
	line = nullptr;
}

EndScene::EndScene()
{
	where = END;
}

EndScene::~EndScene()
{
	
}




void EndScene::SetImg(Gdiplus::Image* img)
{
	EndImg = img;
}

void EndScene::DrawEnd(HDC hdc)
{

}
