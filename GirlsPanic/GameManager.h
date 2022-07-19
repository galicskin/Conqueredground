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

	void CreateSplitLine(std::stack<POINT> OCLine);
	
	void SetSize(int T) { size = T; }
	int GetSize();
	
	//���� �ݴ�� �ٲٱ�
	void reverseList();

	Node* Expand_frontPoint(POINT end);  //��������������� ���о��� ����ȯ �Ǵ� ��忡 �ִٸ� ��带 ��ȯ
	
	CirculyDoublyLinkedList* splitList(std::stack<POINT> OCLine,Node*StartFront, Node* EndFront);
	//�����鼭 ����Ʈ ����.
	void InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, bool ClockWise);
	//�ΰ��� ����Ʈ�� �ް� �� ����� ���̸� ����� �� ū���� ��ȯ
	CirculyDoublyLinkedList* compareArea(CirculyDoublyLinkedList*clockwise, CirculyDoublyLinkedList* counterclockwise);
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
	
	CirculyDoublyLinkedList::Node* GetcurrentFront();
	PlayerData GetPlayerData() const;
	Gdiplus::Image* GetPlayerImage() const;
	void SetPlayerPos(const int X, const int Y);
	void SetPlayerVel(const int V);
	
	void SetList( CirculyDoublyLinkedList::Node*head,  CirculyDoublyLinkedList::Node*tail);
	void SetcurrnetFE(CirculyDoublyLinkedList::Node* A, CirculyDoublyLinkedList::Node* B);

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


	//����Ʈ ��ü
	void changeList(CirculyDoublyLinkedList* T, bool clockwise);

	double GetPlayerArea();
	POINT* GetPolygonPoints();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);
	//��
};
