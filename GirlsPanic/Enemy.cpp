#include "Enemy.h"
#include "GameManager.h"
#include <time.h>
using namespace Gdiplus;

Enemy::Enemy()
{
	xCursor=0;
	yCursor=0;
	velocity = { 0,0 };
	EnemyImg=nullptr;
	EnemySizeControl = 10;
}

Enemy::Enemy(int x,int y, POINT V)
{
	xCursor = x;
	yCursor = y;
	velocity = V;
	EnemyImg = nullptr;
	EnemySizeControl = 10;
}



void Enemy::SetImg(Gdiplus::Image* img)
{
	EnemyImg = img;
}

void Enemy::EnemyinitPos(int x, int y)
{
	xCursor = x;
	yCursor = y;
}

void Enemy::EnemySetVelocity(POINT v)
{
	velocity = v;
}

void Enemy::EnemyAI(DWORD newTime, class GameManager GM)
{
	CirculyDoublyLinkedList::Node* cursor = GM.GetcurrentFront();


	bool changevel = false;
	int w = EnemyImg->GetWidth()/ EnemySizeControl;
	int h = EnemyImg->GetHeight()/ EnemySizeControl;

	do {
		int sx = cursor->point.x;
		int sy = cursor->point.y;

		int ex = cursor->next->point.x;
		int ey = cursor->next->point.y;
	

		
		//�¿� ��� ����
		if (velocity.x > 0 )
		{
			if ((sx == ex) && (sy < ey)&& (xCursor < sx))//�𼭸���down�϶� �˻�
			{
				if (xCursor + (w / 2) >= sx)//�Ϲݰ˻�
				{
					if (yCursor >= sy && yCursor <= ey)// �𼭸�ƨ��
					{
						velocity.x *= -1;
						changevel = true;
					}
					else if (yCursor  >= sy-h/2) //���� �𼭸� ƨ�� 
					{
						double powD = (double)(pow(sy - yCursor, 2) + pow(sx - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.x *= -1;//��ƨ��
							changevel = true;
						}
					}
					else if (yCursor  <= ey+h/2)
					{

						double powD = (double)(pow(ey - yCursor, 2) + pow(sx - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.x *= -1;//��ƨ��
							changevel = true;
						}
					}
				}
			}
		}
		else if(velocity.x < 0)
		{
			if ((sx == ex) && (sy > ey)&& (xCursor > sx))//�𼭸���up�϶� �˻�
			{
				if (xCursor - (w / 2) <= sx)//�Ϲݰ˻�
				{
					if (yCursor <= sy && yCursor >= ey)// �𼭸�ƨ��
					{
						velocity.x *= -1;
						changevel = true;
					}
					else if (yCursor  >= ey-h/2) //���� �𼭸� ƨ�� 
					{
						double powD = (double)(pow(ey - yCursor, 2) + pow(sx - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.x *= -1;//��ƨ��
							changevel = true;
						}
					}
					else if (yCursor <= sy+h/2)
					{

						double powD = (double)(pow(sy - yCursor, 2) + pow(sx - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.x *= -1;//��ƨ��
							changevel = true;
						}
					}
				}
			}
		}
		


		// ���� ��� ����
		if (velocity.y > 0)//������ �Ʒ��� ��������
		{
			if ((sy == ey) && (sx > ex)&& (yCursor < sy))//�𼭸��� left�϶� �˻�
			{
				if (yCursor + (h / 2) >= sy)//�Ϲݰ˻�
				{
					if (xCursor <= sx && xCursor >= ex)// �𼭸�ƨ��
					{
						velocity.y *= -1;
						changevel = true;
					}
					else if (xCursor >= ex-w/2) //���� �𼭸� ƨ�� 
					{
						double powD = (double)(pow(sy - yCursor, 2) + pow(ex - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.y *= -1;//��ƨ��
							changevel = true;
						}
					}
					else if (yCursor <= sx-w/2)
					{

						double powD = (double)(pow(sy - yCursor, 2) + pow(sx - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.y *= -1;//��ƨ��
							changevel = true;
						}
					}
				}
			}
		}
		else if (velocity.y < 0)
		{
			if ((sy == ey) && (sx < ex) && (yCursor > sy))//�𼭸��� right�϶� �˻�
			{
				if (yCursor - (h / 2) <= sy)//�Ϲݰ˻�
				{
					if (xCursor >= sx && xCursor <= ex)// �𼭸�ƨ��
					{
						velocity.y *= -1;
						changevel = true;
					}
					else if (xCursor >= sx-w/2 ) //���� �𼭸� ƨ�� 
					{
						double powD = (double)(pow(sy - yCursor, 2) + pow(sx - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.y *= -1;//��ƨ��
							changevel = true;
						}
					}
					else if (yCursor <= ex+w/2)
					{

						double powD = (double)(pow(sy - yCursor, 2) + pow(ex - xCursor, 2));
						int D = (int)sqrt(powD);
						if (D <= w)
						{
							velocity.y *= -1;//��ƨ��
							changevel = true;
						}
					}
				}
			}
		}

		if (changevel == true)
		{
			break;
		}


		cursor = cursor->next;
	} while (cursor != GM.GetcurrentFront());

	
	xCursor += velocity.x;
	yCursor += velocity.y;

}

int Enemy::GetxCursor()
{
	return xCursor;
}

int Enemy::GetyCursor()
{
	return yCursor;
}

Gdiplus::Image* Enemy::GetEnemyImage()
{
	return EnemyImg;
}

bool Enemy::isColled(GameManager GM)
{

	int Rangex = abs(GM.GetPlayerData().xCursor - xCursor);
	int Rangey = abs(GM.GetPlayerData().yCursor - yCursor);

	int ew = EnemyImg->GetWidth() / EnemySizeControl;
	int eh = EnemyImg->GetHeight() / EnemySizeControl;

	int pw = GM.GetPlayerImage()->GetWidth() / GM.playerSizeControl;
	int ph = GM.GetPlayerImage()->GetHeight() / GM.playerSizeControl;
	
	if ((Rangex < (ew + pw) / 2) && (Rangey < (eh + ph) / 2))
	{
		if (pow(ew + pw, 2) >= pow(Rangex, 2) + pow(Rangey, 2))
		{
			return true;
		}
	}
	
		return false;
}



