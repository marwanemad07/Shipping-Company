#pragma once
#include "Event.h"
#include "company.h"
#include "Cargos.h"
#include "VIPcargos.h"
#include "Normalcargos.h"
#include "Specialcargos.h"
using namespace std;
class Preparation:public Event
{
private:
	company* cPtr;
	char type;
	int DIST;
	int LT;
	int Cost;
	static int NCargoCTR, SCargoCTR, VCargoCTR, CargosCTR;


public:
	Preparation(company* a);
	Preparation(company* a, char t, int id, int d, int l, int c, int day,int hour);
	void setcPtr();
	void setType(char type);
	void setDistance(int distance);
	void setLT(int hours);
	void setCost(int cost);
	void Execute();

};

