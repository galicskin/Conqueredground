
#include "GameManager.h"

CirculyDoublyLinkedList::~CirculyDoublyLinkedList()
{
	
}


void CirculyDoublyLinkedList::Sethead(Node* T)
{
	head = T;
	tail = T;
}

void CirculyDoublyLinkedList::AddNode(Node* T)
{
	tail->next = T;
	T->next = head;

	head->prev = T;
	T->prev = tail;

	tail = T;
	size++;
}

bool CirculyDoublyLinkedList::SubNode(Node* T)
{
	Node* cursor = head;
	while (cursor != T)
	{
		if (cursor == tail)
		{
			break;
			return false;
		}
		cursor = cursor->next;
	}
	cursor = cursor->prev;
	cursor->next = cursor->next->next;
	cursor->next->prev = cursor;
	delete T;
	size--;
	return true;
}

void CirculyDoublyLinkedList::DestroyList()
{
	for (auto iter = head; iter != nullptr; )
	{
		Node* nextNode = iter->next;
		delete iter;
		iter = nextNode;
	}
}

int CirculyDoublyLinkedList::GetSize(Node* anyhead)
{
	Node* cursor = anyhead;
	int tmpsize = 1;
	while(cursor != anyhead->prev)
	{
		cursor = cursor->next;
		tmpsize++;
	}

	return tmpsize;
}

CirculyDoublyLinkedList::Node* CirculyDoublyLinkedList::Expand_frontPoint(POINT end)
{
	Node* cursor = head;

	do {
		if (cursor->point.x == cursor->next->point.x) // y축 일정
		{
			if (end.x == cursor->point.x)
			{
				if ((end.y - cursor->point.y) * (cursor->next->point.y - end.y) >= 0)
				{
					if (cursor->next->point.y - end.y == 0)
					{
						return cursor->next;
					}
					return cursor;
				}
				
				
			}
		}
		else if (cursor->point.y == cursor->next->point.y)// x축 일정
		{
			if (end.y == cursor->point.y)
			{
				if ((end.x - cursor->point.x) * (cursor->next->point.x - end.x) >= 0)
				{
					if (cursor->next->point.x - end.x == 0)
					{
						return cursor->next;
					}
					return cursor;
				}
			}
		}
		else
		{
			//오류
			return nullptr;
		}
		cursor = cursor->next;
	} while (cursor != head);
		//해당점이 어떤 선분위에도 없음==오류
		return nullptr;
}



void CirculyDoublyLinkedList::splitList(Node* MoveStart, Node* MoveEnd)
{
	
}

void CirculyDoublyLinkedList::InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, Node* baseNode)
{

	EnterDataTail->next = baseNode->next;
	baseNode->next = EnterDataHead;
	EnterDataHead->prev = baseNode;
	EnterDataTail->next->prev = EnterDataTail;
	
}

GameManager::GameManager()
{
	
	
}
GameManager::~GameManager()
{


}

void GameManager::SetImg(Gdiplus::Image* img)
{
	playerImg = img;
}

PlayerData GameManager::player = { 0,0,0, new CirculyDoublyLinkedList };



void GameManager::init_SetFront_AfterNode()
{
	currentFront = player.Conquered->Expand_frontPoint({ player.xCursor, player.yCursor });
	currentAfter = currentFront->next;
}

void GameManager::SetNextLine()
{
	currentFront = currentAfter;
	currentAfter = currentAfter->next;
}

void GameManager::SetBackLine()
{
	currentAfter = currentFront;
	currentFront = currentFront->prev;
}

bool GameManager::backline()
{
	if ((currentFront->prev->point.x - currentFront->point.x) == 0)//y축 평행
	{
		return player.yCursor != currentFront->point.y;
	}
	else if ((currentFront->prev->point.y - currentFront->point.y) == 0)
	{
		return player.xCursor != currentFront->point.x;
	}
	

	
}

PlayerData GameManager::GetPlayerData()
{
	return player;
}

Gdiplus::Image* GameManager::GetPlayerImage()
{
	return playerImg;
}

void GameManager::SetPlayerPos(int X,int Y)
{
	player.xCursor = X;
	player.yCursor = Y;
}

void GameManager::SetPlayerVel(int V)
{
	player.velocity = V;
}



void GameManager::SetList(CirculyDoublyLinkedList::Node* head, CirculyDoublyLinkedList::Node* tail)
{
	GetPlayerData().Conquered->head = head;
	GetPlayerData().Conquered->tail = tail;
}



int GameManager::onObjectLine()
{
	if (currentFront->point.x == player.xCursor && currentFront->point.y == player.yCursor)
	{
		return FrontPos;
	}
	else if(currentAfter->point.x == player.xCursor && currentAfter->point.y == player.yCursor)
	{

		return AfterPos;
	}
	else if (currentFront->point.x - currentAfter->point.x == 0) //y축 평행
	{
		return Yaxis;
	}
	else if (currentFront->point.y - currentAfter->point.y == 0) //x축평행
	{
		return Xaxis;
	}
	else
	{
		return NOT;//아웃된것
	}
}

POINT GameManager::ableLine()
{
	int vX = currentFront->prev->point.x - currentFront->point.x+ currentFront->next->point.x - currentFront->point.x;
	int vY = currentFront->prev->point.y - currentFront->point.y+ currentFront->next->point.y - currentFront->point.y;
	
	return { vX / abs(vX), vY / abs(vY) };
}



void GameManager::MoveRight()
{
	player.xCursor += player.velocity;
}

void GameManager::MoveLeft()
{
	player.xCursor -= player.velocity;
}

void GameManager::MoveUp()
{
	player.yCursor -= player.velocity;
}

void GameManager::MoveDown()
{
	player.yCursor += player.velocity;
}



double GameManager::GetPlayerArea()
{
	return 0.0;
}

POINT* GameManager::GetPolygonPoints()
{

	CirculyDoublyLinkedList::Node* cursor = GetPlayerData().Conquered->head;
	POINT* polygon = new POINT[GetPlayerData().Conquered->size];
		for (int i = 0; i < GetPlayerData().Conquered->size; i++)
		{
			polygon[i] = cursor->point ;
			cursor=cursor->next;

		}

	return polygon;
}


void GameManager::MoveCursor(int wParam)
{
	switch (wParam)
	{
	case VK_RIGHT:
		player.xCursor += player.velocity;
		break;
	case VK_LEFT:
		player.xCursor -= player.velocity;
		break;
	case VK_UP:
		player.yCursor -= player.velocity;
		break;
	case VK_DOWN:
		player.yCursor += player.velocity;
		break;
	}

}

void GameManager::IsCollid(Enemy enemy)
{
}


