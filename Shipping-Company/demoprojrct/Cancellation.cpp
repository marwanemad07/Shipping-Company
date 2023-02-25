#include "Cancellation.h"

void Cancellation::Execute()
{

	Node<Normalcargos*>* temp = cPtr->GetwaitingNC()->getHead();
	Node<Normalcargos*>* prev = NULL;
	Normalcargos* NC;

	if (temp == NULL) return;
	if (temp->getNext() == NULL){
		if (temp->getItem()->getmainID() == getID())
		{
			cPtr->GetwaitingNC()->deletebeg(NC);
			delete temp;
			return;
		}
		else{
			return;
		}
	}
	prev = temp;
	temp = temp->getNext();
	while (temp)
	{
		if (temp->getItem()->getmainID() == getID())
		{
			prev->setNext(temp->getNext());
			temp->setNext(nullptr);
			NC = temp->getItem();
			cPtr->GetwaitingNC()->decrementSize();
			delete NC;
			delete temp;
		    temp = nullptr;
			NC = nullptr;
		}
		else {
			prev = temp;
			temp = temp->getNext();
		}
	}
}

Cancellation::Cancellation(company* a,int id , int  day,int hour):Event(id, day,hour)
{
	cPtr = a;
	
}
