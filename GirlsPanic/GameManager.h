#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")

#include "Enemy.h"

enum parallel { Xaxis = 1, Yaxis, FrontPos ,AfterPos, NOT };

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
	void optimizateNode();//����ȭ-> ���� �����ִ� ���̶�� ����Ʈ���� �������ִ±��
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

	void SetImg(Gdiplus::Image* img);

	void init_SetFront_AfterNode(); //�ʱ⼳��, �÷��̾ �����ɶ� �� �ѹ� ȣ��
	void SetNextLine(); // �������� �����Ҷ� ���� �߻��ϴ� �Լ�(�ʱ⼳���� ���ؾ���)
	void SetBackLine();

	PlayerData GetPlayerData();
	Gdiplus::Image* GetPlayerImage();
	void SetPlayerPos( int X,int Y);
	void SetPlayerVel(int V);
	
	void SetList(CirculyDoublyLinkedList::Node*head, CirculyDoublyLinkedList::Node*tail);


	//�÷��̾ ������ �ִ��� ������ 
	int onObjectLine();
	//�������� ������ ���� �� �� �ִ� �� �Ǻ�
	POINT ableLine();

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();


	double GetPlayerArea();
	POINT* GetPolygonPoints();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);

};
