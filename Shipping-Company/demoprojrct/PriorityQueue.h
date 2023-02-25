#pragma once
#include "PQNode.h"
template<class T, class P >
class PriorityQueue
{
	PQNode<T, P>* node;
	int size;
public:
	PriorityQueue()
	{
		node = nullptr;
		size = 0;
	}
	void enqueue(T item, P cost)
	{
		PQNode<T, P>* newNode = new PQNode<T, P>(item, cost);
	
		if (node == nullptr || cost > node->getPriority())
		{
			newNode->setNext(node);
			node = newNode;
		}
		else
		{
			PQNode<T, P>* temp = node;

			while (temp->getNext() != nullptr && temp->getNext()->getPriority() >= cost)
			{
				temp = temp->getNext();

			}
			newNode->setNext(temp->getNext());
			temp->setNext(newNode);

		}
		size++;
	}

	bool isEmpty()
	{
		return node == nullptr;
	}

	bool peek(T& entry)
	{
		if (isEmpty()){
			entry = NULL;
			return false;
		}
		entry = node->getItem();
		return true;
	}
	int getSize(){
		return size;
	}
	void dequeue(T &item, P &cost)
	{
		if (isEmpty())
		{
			
			cost = -1;

			return;
		}
		PQNode<T, P>* temp = node;
		cost = temp->getPriority();
		item = temp->getItem();
		node = node->getNext();
		delete temp;
		temp = nullptr;
		size--;
	}

	~PriorityQueue()
	{
	/*	while (node != nullptr)
		{
			dequeue();
		}*/
	}
};

