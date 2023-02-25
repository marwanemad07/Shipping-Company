#include "Specialcargos.h"


Specialcargos::Specialcargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour) : Cargos(id, distance, loadtime, cost, prep_day, prep_hour)
{
	daycounter = 0;
}
int Specialcargos::getdaycounter() {
	return daycounter;
}

void Specialcargos::incrementDayCounter() {
	daycounter++;
}

Specialcargos::~Specialcargos()
{
}