#pragma once
#include <string>
#include"time.h"
#include "TIME_cnt.h"
using namespace std;
class Event
{
private:

	int ID;
	TIME_cnt ET; //EventTime
public:

	Event();
	Event(int id, int day,int hour);
	int getID()const;
	TIME_cnt getTime();
	int getDay() const;
	void SetDay(int);
	int getHour() const;
	void SetHour(int);
	virtual void Execute() = 0;
	virtual~Event()=0;
};

