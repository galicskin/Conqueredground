#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
#include <stack>
#include "Enemy.h"

enum parallel { Xaxis = 1, Yaxis, FrontPos, AfterPos, NOT };
enum can_ocuppy { Only = 100, Both, Nothing };


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
	

	CirculyDoublyLinkedList* splitList(std::stack<POINT> OCLine,Node*StartFront, Node* EndFront);
	void InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, Node* baseNode);
	//Node* compareAreaBig(Node* A, Node* B);//�ΰ��� ����� ���̸� ����� �� ū���� ��ȯ
	CirculyDoublyLinkedList* compareArea(CirculyDoublyLinkedList*splitLine, Node* StartFront, Node* EndFront);//�ΰ��� ����Ʈ�� ������ �� ū ���̸� ��ȯ
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

	void SetImg( Gdiplus::Image* img);

	//�ʱ⼳��, �÷��̾ �����ɶ� �� �ѹ� ȣ��
	void init_SetFront_AfterNode(); 
	// �������� �����Ҷ� ���� �߻��ϴ� �Լ���(�ʱ⼳���� ���ؾ���)
	void SetNextLine(); 
	void SetBackLine();
	
	//���� ������ ���ͱ��ϱ�
	POINT GetVector() const;

	//���� ������ ���ͱ��ϱ�
	POINT GetprevVector()const;

	bool backline();
	

	PlayerData GetPlayerData() const;
	Gdiplus::Image* GetPlayerImage() const;
	void SetPlayerPos(const int X, const int Y);
	void SetPlayerVel(const int V);
	
	void SetList( CirculyDoublyLinkedList::Node*head,  CirculyDoublyLinkedList::Node*tail);


	//�÷��̾ ������ ������ �������� �ִ���
	int onObjectLine() const;

	//�������� ������ ���� �� �� �ִ� �� �Ǻ�
	POINT ableLine() const;

	//�����ϱ�
	int OcuppyLine();
	//��迡 �ִ���
	//���Ϸ��� ��谡 x�� �����϶�
	bool isXboader(CirculyDoublyLinkedList::Node*cursor,int directions);
	//���Ϸ��� ��谡 y�� �����϶�
	bool isYboader(CirculyDoublyLinkedList::Node* cursor, int directions);

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();


	double GetPlayerArea();
	POINT* GetPolygonPoints();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);
	//��
};
