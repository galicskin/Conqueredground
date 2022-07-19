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
	
	//방향 반대로 바꾸기
	void reverseList();

	Node* Expand_frontPoint(POINT end);  //선분위에있을경우 선분앞쪽 노드반환 또는 노드에 있다면 노드를 반환
	
	CirculyDoublyLinkedList* splitList(std::stack<POINT> OCLine,Node*StartFront, Node* EndFront);
	//끊으면서 리스트 삽입.
	void InsertLinkedList(Node* EnterDataHead, Node* EnterDataTail, bool ClockWise);
	//두개의 리스트를 받고 그 노드의 넓이를 계산후 더 큰것을 반환
	CirculyDoublyLinkedList* compareArea(CirculyDoublyLinkedList*clockwise, CirculyDoublyLinkedList* counterclockwise);
	void optimizateNode();//최적화-> 같은 선상에있는 점이라면 리스트에서 삭제해주는기능
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

	void SetImg( Gdiplus::Image* img);

	//초기설정, 플레이어가 생생될때 딱 한번 호출
	void init_SetFront_AfterNode(); 
	// 꼭지점에 도달할때 마다 발생하는 함수들(초기설정을 잘해야함)
	void SetNextLine(); 
	void SetBackLine();
	
	//현재 라인의 벡터구하기
	POINT GetVector() const;

	//이전 라인의 벡터구하기
	POINT GetprevVector()const;

	bool backline();
	
	CirculyDoublyLinkedList::Node* GetcurrentFront();
	PlayerData GetPlayerData() const;
	Gdiplus::Image* GetPlayerImage() const;
	void SetPlayerPos(const int X, const int Y);
	void SetPlayerVel(const int V);
	
	void SetList( CirculyDoublyLinkedList::Node*head,  CirculyDoublyLinkedList::Node*tail);
	void SetcurrnetFE(CirculyDoublyLinkedList::Node* A, CirculyDoublyLinkedList::Node* B);

	//플레이어가 선위에 있을때 꼭지점에 있는지
	int onObjectLine() const;

	//꼭짓점에 있을때 어디로 갈 수 있는 지 판별
	POINT ableLine() const;

	//점령하기
	int OcuppyLine();
	//경계에 있는지
	//비교하려는 경계가 x축 평형일때
	bool isXboader(CirculyDoublyLinkedList::Node*cursor,int directions);
	//비교하려는 경계가 y추 평형일때
	bool isYboader(CirculyDoublyLinkedList::Node* cursor, int directions);

	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();


	//리스트 교체
	void changeList(CirculyDoublyLinkedList* T, bool clockwise);

	double GetPlayerArea();
	POINT* GetPolygonPoints();
	void MoveCursor(int wParam);
	void IsCollid(Enemy enemy);
	//뭐
};
