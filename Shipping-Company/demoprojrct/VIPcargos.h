#pragma once
#include "Cargos.h"
class VIPcargos :public Cargos
{
private:
	bool Assigned;
	int daycounter;
	bool loaded;
	static int cnt; //used in priority equation
public:
	VIPcargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour);
	int getdaycounter();
	void incrementDayCounter();
	int VIPeq() const; // it return the equation of vipCargo, we will change it in phase 2
	~VIPcargos();
};