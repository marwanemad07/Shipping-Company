#pragma once
#include <iostream>
#include "truck.h"
using namespace std;
class NormalTruck :public truck
{
private:
	static int capacity; // Truck Capacity common for all same truck type
	static int mainTime; // maintainence time commn for all same truck type
	static int speed; // speed common for all same truck type

public:
	NormalTruck(int i);
	NormalTruck(int cap, int MT, int Sp);

	int getSpeed() const;
	int getMT() const; // get maintainence time
	int getCapacity() const;

	double getdelivertTime();
	~NormalTruck();
};

