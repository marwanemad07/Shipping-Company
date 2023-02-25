#include "VIPcargos.h"


VIPcargos::VIPcargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour) : Cargos(id, distance, loadtime, cost,  prep_day, prep_hour)
{
	
	daycounter = 0;
}

int VIPcargos::cnt = 5200;

int VIPcargos::getdaycounter() {
	return daycounter;
}

void VIPcargos::incrementDayCounter() {
	daycounter++;
}

int VIPcargos::VIPeq() const
{
	cnt -= 200;
	return getCost() + getDelDist() + cnt;
}

VIPcargos::~VIPcargos()
{
}
