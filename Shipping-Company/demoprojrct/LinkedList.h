#pragma once
#include"Node.h"
template <typename T>
class LinkedList
{
private:
	Node<T> *Head;
	int size;
public:

	LinkedList()
	{
		Head = nullptr;
		size = 0;
	}

	~LinkedList()
	{
		DeleteAll();
	}
	void decrementSize(){
		size--;
	}
	bool isEmpty()
	{
		return (Head) ? true : false;
	}

	Node<T>*&getHead(){
		return Head;
	}
	void deletebeg(T& frntEntry){
		 if (Head){
		
			 frntEntry = Head->getItem();
			 Head = Head->getNext();
			 decrementSize();
		 }
	}
	void PrintList()	const
	{
		Node<T> *p = Head;

		while (p)
		{
			cout << p->getItem() << " ";
			p = p->getNext();
		}
		cout << endl;
	}

	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	void InsertEnd(const T &data)
	{
		if (Head == nullptr)
		{
			Head = new Node<T>(data);
		}
		else
		{
			Node<T>* ptr = Head;
			while (ptr->getNext())
				ptr = ptr->getNext();
			ptr->setNext(new Node<T>(data));
		}
		size++;
	}
	int getSize()
	{
		return size;
	}
};