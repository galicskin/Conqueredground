
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
