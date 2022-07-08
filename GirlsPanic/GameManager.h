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

	Node* Expand_frontPoint(POINT end);  //��������������� ���о��� ����ȯ �Ǵ� ��忡 �ִٸ� ��带 ��ȯ
	

	void splitList(Node* MoveStart, Node* MoveEnd);
	void InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, Node* baseNode);
	Node* compareAreaBig(Node* A, Node* B);//�ΰ��� ����� ���̸� ����� �� ū���� ��ȯ
	Node* compareAreaSmall(Node* A, Node* B);//�ΰ��� ����� ���̸� ����� �� �������� ��ȯ
	void optimizateNode();
};




struct PlayerData
{

	int xCursor;
	int yCursor;
	int velocity;
	
	CirculyDoublyLinkedList *Conquered;


	//������ �̶�¶�
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

	void init_SetFront_AfterNode(); //�ʱ⼳��, �÷��̾ �����ɶ� �� �ѹ� ȣ��
	void SetFront_AfterNode(); // �������� �����Ҷ� ���� �߻��ϴ� �Լ�(�ʱ⼳���� ���ؾ���)

	PlayerData GetPlayerData();
	Gdiplus::Image* GetPlayerImage();
	void SetPlayerData(PlayerData T);
	void SetList(CirculyDoublyLinkedList::Node*head, CirculyDoublyLinkedList::Node*tail);

	double GetPlayerArea();
	POINT* GetPolygonPoints();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);

};