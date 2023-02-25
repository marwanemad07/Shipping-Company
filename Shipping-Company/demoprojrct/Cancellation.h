#pragma once
#include "Event.h"
#include "Cargos.h"
#include "company.h"
#include <string>
using namespace std;
class Cancellation:public Event
{
private:
	company* cPtr;
//	char TYP;
	int ID;
	//int DIST;
	int Cost;
public:
	Cancellation(company* a, int id, int day,int hour);
	void Execute();

};

