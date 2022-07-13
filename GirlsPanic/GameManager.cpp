
#include "GameManager.h"

CirculyDoublyLinkedList::~CirculyDoublyLinkedList()
{
	
}


void CirculyDoublyLinkedList::Sethead(Node* T)
{
	head = T;
	tail = head->prev;
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

void CirculyDoublyLinkedList::CreateSplitLine(std::stack<POINT> OCLine)
{
	CirculyDoublyLinkedList::Node* splithead = new CirculyDoublyLinkedList::Node(OCLine.top());
	head = splithead;
	tail = splithead;
	OCLine.pop();
	while (!OCLine.empty())
	{
		CirculyDoublyLinkedList::Node* splitNode = new CirculyDoublyLinkedList::Node(OCLine.top());
		AddNode(splitNode);
		OCLine.pop();
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

void CirculyDoublyLinkedList::reverseList()
{
	Node* cursor = head;
	do {
		Node* temp = cursor->prev;
		cursor->prev = cursor->next;
		cursor->next = temp;
		cursor = cursor->prev;
	} while (cursor == head);

	head = tail;
	tail = cursor;

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


// 갱신될 리스트 반환
CirculyDoublyLinkedList* CirculyDoublyLinkedList::splitList(std::stack<POINT> OCLine, Node* StartFront, Node* EndFront)
{
	CirculyDoublyLinkedList*A=new CirculyDoublyLinkedList;
	A->head = EndFront->next;
	A->tail = StartFront;

	CirculyDoublyLinkedList* B = new CirculyDoublyLinkedList;
	B->head = StartFront->next;
	B->tail = EndFront;




	CirculyDoublyLinkedList::Node* Ahead = new CirculyDoublyLinkedList::Node(OCLine.top());
	OCLine.pop();
	A->head = Ahead;
	while(OCLine.size()!=0)
	{
		CirculyDoublyLinkedList::Node* Aextension = new CirculyDoublyLinkedList::Node(OCLine.top());
		OCLine.pop();
		A->AddNode(Aextension);
	}
	

	return A;
}

void CirculyDoublyLinkedList::InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, bool ClockWise)
{
	if (ClockWise)
	{
	
	}
	else
	{
		reverseList();
	}
	EnterDataTail->next = head;
	EnterDataHead->prev = tail;
	tail->next = EnterDataHead;
	head->prev = EnterDataTail;
}

CirculyDoublyLinkedList* CirculyDoublyLinkedList::compareArea(CirculyDoublyLinkedList* clockwise, CirculyDoublyLinkedList* counterclockwise)
{
	Node* cursor = clockwise->head->next;
	
	//4가지의 스타트를 나눌것.
	cursor->point.x;
		/*
	switch()

	if (cursor->point.x < head->point.x)
	{

	}
	else if (cursor->point.x > head->point.x)
	{

	}
	
	*/
	return nullptr;
}

GameManager::GameManager()
{
	
	
}
GameManager::~GameManager()
{


}

void GameManager::SetImg( Gdiplus::Image* img)
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

POINT GameManager::GetVector() const
{
	int VecX = currentAfter->point.x - currentFront->point.x;
	int VecY = currentAfter->point.y - currentFront->point.y;

	if (VecX != 0)
	{
	VecX /= abs(VecX);
	}

	if (VecY != 0)
	{
		VecY /= abs(VecY);
	}
	return POINT({ VecX, VecY });
}


POINT GameManager::GetprevVector() const
{
	int VecX = currentFront->point.x - currentFront->prev->point.x;
	int VecY = currentFront->point.y - currentFront->prev->point.y;
	
	if (VecX != 0)
	{
		VecX /= abs(VecX);
	}

	if (VecY != 0)
	{
		VecY /= abs(VecY);
	}
	return POINT({ VecX, VecY });
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

PlayerData GameManager::GetPlayerData() const
{
	return player;
}

Gdiplus::Image* GameManager::GetPlayerImage() const
{
	return playerImg;
}

void GameManager::SetPlayerPos(const int X, const int Y)
{
	player.xCursor = X;
	player.yCursor = Y;
}

void GameManager::SetPlayerVel(int V)
{
	player.velocity = V;
}



void GameManager::SetList( CirculyDoublyLinkedList::Node* head,  CirculyDoublyLinkedList::Node* tail)
{
	player.Conquered->head = head;
	player.Conquered->tail = tail;
}



int GameManager::onObjectLine() const
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

POINT GameManager::ableLine() const
{
	int vX = currentFront->prev->point.x - currentFront->point.x+ currentFront->next->point.x - currentFront->point.x;
	int vY = currentFront->prev->point.y - currentFront->point.y+ currentFront->next->point.y - currentFront->point.y;
	
	return { vX / abs(vX), vY / abs(vY) };
}

int GameManager::OcuppyLine()
{
	if (currentFront->point.x == player.xCursor && currentFront->point.y == player.yCursor)//꼭지점
	{
		if (GetVector().x * GetprevVector().y - GetVector().y * GetprevVector().x >0)
		{
			return Both;
		}
		else
		{
			return Nothing;
		}
	}
	else // 모서리
	{
		return Only;

	}

}

bool GameManager::isXboader(CirculyDoublyLinkedList::Node* cursor, int directions)
{
	if (directions == 12)//Up
	{
		if (player.yCursor <= cursor->point.y)
		{
			if (player.xCursor >= cursor->point.x && player.xCursor <= cursor->next->point.x)
			{
				player.yCursor = cursor->point.y;
				return true;
			}
		
		}
	}
	else if(directions == 13)
	{
		if (player.yCursor >= cursor->point.y)
		{
			if (player.xCursor <= cursor->point.x && player.xCursor >= cursor->next->point.x)
			{
				player.yCursor = cursor->point.y;
				return true;
			}

		}
	}
	return false;


}

bool GameManager::isYboader(CirculyDoublyLinkedList::Node* cursor, int directions)
{
	if (directions == 10)//right
	{
		if (player.xCursor >= cursor->point.x)
		{
			if (player.yCursor >= cursor->point.y && player.yCursor <= cursor->next->point.y)
			{
				player.xCursor = cursor->point.x;
				return true;
			}

		}
	}
	else if (directions == 11)
	{
		{
			if (player.xCursor <= cursor->point.x)
			{
				if (player.yCursor <= cursor->point.y && player.yCursor >= cursor->next->point.y)
				{
					player.xCursor = cursor->point.x;
					return true;
				}

			}
		}
	}

	return false;

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


