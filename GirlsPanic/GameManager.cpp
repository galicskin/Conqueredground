
#include "GameManager.h"




CirculyDoublyLinkedList::~CirculyDoublyLinkedList()
{
	for (auto iter = head; iter != nullptr; )
	{
		Node* nextNode = iter->next;
		delete iter;
		iter = nextNode;
	}
	
}

double GameManger::GetPlayerArea()
{
	return 0.0;
}

void GameManger::MoveCursor(int wParam)
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

void GameManger::IsCollid(Enemy enemy)
{
}
