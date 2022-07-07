
#include "GameManager.h"

CirculyDoublyLinkedList::~CirculyDoublyLinkedList()
{
	
}


void CirculyDoublyLinkedList::AddNode(Node* T)
{
	tail->next = T;
	T->next = head;

	head->prev = T;
	T->prev = tail;
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

PlayerData GameManager::player = { 0,0,0, new CirculyDoublyLinkedList };



PlayerData GameManager::GetPlayerData()
{
	return player;
}

Gdiplus::Image* GameManager::GetPlayerImage()
{
	return playerImg;
}

void GameManager::SetPlayerData(PlayerData T)
{
	player = T;
}

void GameManager::SetList(CirculyDoublyLinkedList::Node* head, CirculyDoublyLinkedList::Node* tail)
{
	GetPlayerData().Conquered->head = head;
	GetPlayerData().Conquered->tail = tail;
}



double GameManager::GetPlayerArea()
{
	return 0.0;
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


