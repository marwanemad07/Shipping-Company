#include "Promotion.h"

Promotion::Promotion(company* a, int id, int ex, int day, int hour) : Event(id, day, hour)
{
	cPtr = a;
	PromotionCost = ex;
}

void Promotion::Execute()
{
	Node<Normalcargos*>* ptrp = cPtr->GetwaitingNC()->getHead();
	Node<Normalcargos*>*ptr = nullptr;
	Normalcargos* tempPtr = nullptr, * promotedCargo = nullptr;

	
	if (!ptrp)return;
	if (ptrp->getNext()==NULL)
	{
		if (ptrp->getItem()->getmainID() == getID()){
			promotedCargo = ptrp->getItem();
			if (promotedCargo)
			{
				VIPcargos* newCargo = new VIPcargos(promotedCargo->getmainID(), promotedCargo->GetDeliveryDistance(), promotedCargo->getLoadTime(), promotedCargo->GetCost(), promotedCargo->getPrepDay(), promotedCargo->getPrepHour());
				cPtr->Waiting_VIP_push(newCargo);
			}
			cPtr->GetwaitingNC()->deletebeg(promotedCargo);

		}
		return;

	}
	if (ptrp->getItem()->getmainID() == getID()){
		promotedCargo = ptrp->getItem();
		
	}
	while (ptrp->getNext())
	{
		ptr = ptrp->getNext();
		if (getID() == ptr->getItem()->getmainID())
		{		
			ptrp->setNext(ptr->getNext());
			promotedCargo = tempPtr; break;
		}
		ptrp = ptr;

	}
	if(promotedCargo)
	{ 
		VIPcargos* newCargo = new VIPcargos(promotedCargo->getmainID(), promotedCargo->GetDeliveryDistance(), promotedCargo->getLoadTime(), promotedCargo->GetCost(), promotedCargo->getPrepDay(), promotedCargo->getPrepHour());
		cPtr->Waiting_VIP_push(newCargo);
	}
	if (promotedCargo)
	delete promotedCargo;
	promotedCargo = nullptr;
	
}