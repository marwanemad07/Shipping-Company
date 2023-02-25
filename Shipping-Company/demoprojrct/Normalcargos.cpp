#include "Normalcargos.h"


Normalcargos::Normalcargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour) : Cargos(id, distance, loadtime, cost, prep_day, prep_hour)
{
	daycounter = 0;
}
int Normalcargos::getdaycounter() {
	return daycounter;
}



int Normalcargos::getNC_LoadTime()
{
	return getLoadTime();
}

void Normalcargos::incrementDayCounter() {
	daycounter++;
}
Normalcargos::~Normalcargos()
{
}
