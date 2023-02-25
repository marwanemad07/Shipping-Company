#include "Cargos.h"


Cargos::Cargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour) :Preparation_Time(prep_day, prep_hour), CDT(0, 0), WT(0,0)
{
	ID = id;
	DeliveryDistance = distance;
	LT = loadtime;
	Cost = cost;
	Assigned = false;
	TID = 0;
	WT = 0;
}

void Cargos::setTID(int t){
	TID = t;
}
int Cargos::getTID(){
	return TID;
}
double Cargos::GetCost()
{
	return Cost;
}
int Cargos::getWTHour()
{
	return WT.getHour();
}
void Cargos::setWTHour(int w){
	WT.setHour(w);
}
int Cargos::getWTDay()
{
	return WT.getDay();
}
void Cargos::setWTDay(int w){
	WT.setDay (w);
}

double Cargos::GetDeliveryDistance()
{
	return DeliveryDistance;
}

void Cargos::setCDT(int day, int hour)
{
	CDT.setDay(day);
	CDT.setHour(hour);
}


void Cargos::SetDeliveryDistance(double a)
{
	DeliveryDistance = a;
}

void Cargos::SetCost(double)
{
}

int Cargos::getmainID() const
{
	return ID;
}

int Cargos::getCost() const
{
	return Cost;
}


int Cargos::getCDTday() const
{
	return CDT.getDay();
}

int Cargos::getCDThour() const
{
	return CDT.getHour();
}


int Cargos::getDelDist() const
{
	return DeliveryDistance;
}

int Cargos::getLoadTime() const
{
	return LT;
}

bool Cargos::getAssigned() const
{
	return Assigned;
}

int Cargos::getPrepDay() const
{
	return Preparation_Time.getDay();
}

int Cargos::getPrepHour() const
{
	return Preparation_Time.getHour();
}

void Cargos::setAssigned(bool flag)
{
	Assigned = flag;
}

Cargos::~Cargos()
{
}
