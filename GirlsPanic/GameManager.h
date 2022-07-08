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

	void Sethead(Node* T);
	void AddNode(Node* T);
	bool SubNode(Node* T);

	void DestroyList();

	Node* head;
	Node* tail;
	int size;

	

	void SetSize(int T) { size = T; }
	int GetSize(Node* anyhead);

	Node* Expand_frontPoint(POINT end);  //선분위에있을경우 선분앞쪽 노드반환 또는 노드에 있다면 노드를 반환
	

	void splitList(Node* MoveStart, Node* MoveEnd);
	void InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, Node* baseNode);
	Node* compareAreaBig(Node* A, Node* B);//두개의 노드의 넓이를 계산후 더 큰것을 반환
	Node* compareAreaSmall(Node* A, Node* B);//두개의 노드의 넓이를 계산후 더 작은것을 반환
	void optimizateNode();
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

	CirculyDoublyLinkedList::Node* currentFront;
	CirculyDoublyLinkedList::Node* currentAfter;
	Gdiplus::Image*playerImg;
public:
	GameManager();
	~GameManager();

	void init_SetFront_AfterNode(); //초기설정, 플레이어가 생생될때 딱 한번 호출
	void SetFront_AfterNode(); // 꼭지점에 도달할때 마다 발생하는 함수(초기설정을 잘해야함)

	PlayerData GetPlayerData();
	Gdiplus::Image* GetPlayerImage();
	void SetPlayerData(PlayerData T);
	void SetList(CirculyDoublyLinkedList::Node*head, CirculyDoublyLinkedList::Node*tail);

	double GetPlayerArea();
	POINT* GetPolygonPoints();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);

};