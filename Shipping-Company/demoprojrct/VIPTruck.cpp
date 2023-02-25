#include "VIPTruck.h"

VIPTruck::VIPTruck(int i) :truck(i)
{
}

VIPTruck::VIPTruck(int cap, int MT, int Sp) : truck()
{
	capacity = cap;
	mainTime = MT;
	speed = Sp;
}

int VIPTruck::getSpeed() const
{
	return speed;
}

int VIPTruck::getMT() const
{
	return mainTime;
}

int VIPTruck::getCapacity() const
{
	return capacity;
}

int VIPTruck::capacity = 0;
int VIPTruck::mainTime = 0;
int VIPTruck::speed = 0;

double VIPTruck::getdelivertTime()
{
	return 0.0;
}
VIPTruck::~VIPTruck()
{
}