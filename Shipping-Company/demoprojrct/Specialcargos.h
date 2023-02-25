#pragma once
#include "Cargos.h"
class Specialcargos :public Cargos
{
private:
	bool Assigned;
	int daycounter;
	bool loaded;
public:
	Specialcargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour);
	int getdaycounter();
	void incrementDayCounter();
	~Specialcargos();
};