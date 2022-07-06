#pragma once
#include "framework.h"
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;
ULONG_PTR g_GdiToken;

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
		~Node() {}

	};
	CirculyDoublyLinkedList() { tail = nullptr;  head = tail; size = 0; }
	~CirculyDoublyLinkedList() {} ; 
	Node* head;
	Node* tail;
	int size;

	

	void InsertLinkedList(Node* head, Node* tail, int index)
	{
		tail->next = (this->head);//this->tail->next;
		(this->tail)->next = head;
	}


};




struct PlayerData
{

	int xCursor;
	int yCursor;
	int velocity;
	Image playerImg;

	CirculyDoublyLinkedList Conquered;
	//정복된 이라는뜻
};
