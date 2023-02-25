#include "NormalTruck.h"

NormalTruck::NormalTruck(int i) :truck(i)
{
}

int NormalTruck::capacity = 0;
int NormalTruck::mainTime = 0;
int NormalTruck::speed = 0;

NormalTruck::NormalTruck(int cap, int MT, int Sp) :truck()
{
	capacity = cap;
	mainTime = MT;
	speed = Sp;
}

int NormalTruck::getSpeed() const
{
	return speed;
}

int NormalTruck::getMT()const
{
	return mainTime;
}

int NormalTruck::getCapacity()const
{
	return capacity;
}

double NormalTruck::getdelivertTime()
{
	return 0.0;
}

NormalTruck::~NormalTruck()
{
	
}
