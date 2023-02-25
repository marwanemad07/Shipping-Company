#include "SpecialTruck.h"

SpecialTruck::SpecialTruck(int i) :truck(i)
{
}

SpecialTruck::SpecialTruck(int cap, int MT, int Sp) : truck()
{
	capacity = cap;
	mainTime = MT;
	speed = Sp;
}

int SpecialTruck::getSpeed() const
{
	return speed;
}

int SpecialTruck::getMT() const
{
	return mainTime;
}

int SpecialTruck::getCapacity() const
{
	return capacity;
}

int SpecialTruck::capacity = 0;
int SpecialTruck::mainTime = 0;
int SpecialTruck::speed = 0;



double SpecialTruck::getdelivertTime()
{
	return 0.0;
}
SpecialTruck::~SpecialTruck()
{

}
