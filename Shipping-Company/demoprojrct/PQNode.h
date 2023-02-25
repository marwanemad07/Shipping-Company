#pragma once
template<class T, class P>
class PQNode
{
	PQNode<T, P>* next;
	T item;
	P prio;
public:
	PQNode() : next(nullptr)
	{
	}
	PQNode(const T& data, const P& priority) : item(data), prio(priority), next(nullptr)
	{
	}
	PQNode(const T& data, const P& priority, PQNode<T, P>* nextptr) : item(data), prio(priority), next(nextptr)
	{

	}
	void setItem(const T& data)
	{
		item = data;
	}

	void setPriority(const P& Priority)
	{
		prio = Priority;
	}

	void setNext(PQNode<T, P>* nextNode)
	{
		next = nextNode;
	}

	T getItem() const
	{
		return item;
	}

	P getPriority() const
	{
		return prio;
	}

	PQNode<T, P>* getNext() const
	{
		return next;
	}


};

