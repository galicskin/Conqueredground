#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")

#include "Enemy.h"


class CirculyDoublyLinkedList
{
public:
	static class Node
	{
	public:
		POINT point;
		Node* next;
		Node* prev;
		Node() {
			next = this;
			prev = this;
		}
		Node(POINT T) :Node() { point = T; }
		
		~Node() {}

	};
	CirculyDoublyLinkedList() { tail = nullptr;  head = tail; size = 0; }
	~CirculyDoublyLinkedList() ; 


	void AddNode(Node* T);
	bool SubNode(Node* T);

	void DestroyList();

	Node* head;
	Node* tail;
	int size;


	void InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, Node* baseNode);

};




struct PlayerData
{

	int xCursor;
	int yCursor;
	int velocity;
	
	CirculyDoublyLinkedList *Conquered;
	//정복된 이라는뜻
};

class GameManager
{
protected:
	static PlayerData player;
	Gdiplus::Image*playerImg;
public:
	GameManager();
	~GameManager() { delete playerImg; }

	PlayerData GetPlayerData();
	Gdiplus::Image* GetPlayerImage();
	void SetPlayerData(PlayerData T);
	void SetList(CirculyDoublyLinkedList::Node*head, CirculyDoublyLinkedList::Node*tail);

	double GetPlayerArea();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);

};