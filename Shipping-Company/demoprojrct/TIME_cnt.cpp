#include "TIME_cnt.h"


TIME_cnt::TIME_cnt()
{
	hours = 0;
	days = 0;
}

TIME_cnt::TIME_cnt(int h, int d)
{
	hours = d;
	days = h;
}

void TIME_cnt::setHour(int h)
{
	hours = h;
}

void TIME_cnt::setDay(int d)
{
	days = d;
}

int TIME_cnt::getHour() const
{
	return hours;
}

int TIME_cnt::getDay() const
{
	return days;
}