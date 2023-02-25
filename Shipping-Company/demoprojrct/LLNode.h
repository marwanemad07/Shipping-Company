//#pragma once
//#include <cstddef>
//
//template <class itemType>
//class LLNode
//{
//
//public:
//	itemType item;
//	LLNode<itemType>* next;
//	//
//	LLNode();
//	LLNode(const itemType& anItem);
//	LLNode(const itemType& anItem, LLNode<itemType>* nextPtr);
//	void setItem(const itemType& anItem);
//	void setNext(LLNode<itemType>* nextPtr);
//	itemType getItem() const;
//	LLNode<itemType>* getNext() const;
//};
//
//template <class itemType>
//LLNode<itemType>::LLNode() : next(nullptr)
//{
//}
//
//template <class itemType>
//LLNode<itemType>::LLNode(const itemType& anItem) : item(anItem), next(nullptr)
//{
//}
//
//template <class itemType>
//LLNode<itemType>::LLNode(const itemType& anItem, LLNode<itemType>* nextPtr) : item(anItem), next(nextPtr)
//{
//}
//
//template <class itemType>
//void LLNode<itemType>::setItem(const itemType& anItem)
//{
//	item = anItem;
//}
//
//
//template <class itemType>
//void LLNode<itemType>::setNext(LLNode<itemType>* nextPtr)
//{
//	next = nextPtr;
//}
//
//template <class itemType>
//itemType LLNode<itemType>::getItem() const
//{
//	return item;
//}
//
//template <class itemType>
//LLNode<itemType>* LLNode<itemType>::getNext() const
//{
//	return next;
//}