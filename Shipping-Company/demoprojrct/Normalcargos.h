#pragma once
#include "Cargos.h"
class Normalcargos :public Cargos
{
private:
	bool Assigned;
	int daycounter;
	bool loaded;
public:
	Normalcargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour);
	int getdaycounter();
	int getNC_LoadTime();
	void incrementDayCounter();
	~Normalcargos();
};