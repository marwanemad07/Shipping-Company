#include "Preparation.h"


Preparation::Preparation(company* a) :Event(-1, 0,0)
{
	cPtr = a;
	type = 'A';
	LT = -1;
	Cost = -1;
	CargosCTR++;


}
int Preparation::CargosCTR = 0;
int Preparation::NCargoCTR = 0;
int Preparation::VCargoCTR = 0;
int Preparation::SCargoCTR = 0;
Preparation::Preparation(company* a, char t, int id, int d, int l, int c, int day,int hour) :Event(id, day,hour)
{
	cPtr = a;
	type = t;
	DIST = d;
	LT = l;
	Cost = c;
	CargosCTR++;
}

void Preparation::setType(char tpe)
{
	type = tpe;
}

void Preparation::setDistance(int distance)
{
	DIST = distance;
}

void Preparation::setLT(int hours)
{
	LT = hours;
}

void Preparation::setCost(int cost)
{
	Cost = cost;
}

void Preparation::Execute()
{
	if (type == 'V') {
		VIPcargos* VCargo = new VIPcargos(getID(), DIST, LT, Cost, getDay(), getHour());
		int priority = VCargo->VIPeq();
		cPtr->GetwaitingVC()->enqueue(VCargo, priority);
		VCargoCTR++;
	}
	else if (type == 'N')
	{
		Normalcargos* NCargo = new Normalcargos(getID(), DIST, LT, Cost, getDay(), getHour());

		cPtr->GetwaitingNC()->InsertEnd(NCargo);
		NCargoCTR++;
	}
	else if (type == 'S')
	{
		Specialcargos* SCargo = new Specialcargos(getID(), DIST, LT, Cost, getDay(), getHour());
		cPtr->GetwaitingSC()->enqueue(SCargo);
		SCargoCTR++;
	}
	CargosCTR++;
}
