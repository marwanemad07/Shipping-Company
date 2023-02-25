#pragma once
#include "Event.h"
#include "company.h"
#include <string>
using namespace std;
class Promotion :public Event
{
private:
	int PromotionCost;
	company* cPtr;
public:
	Promotion(company* a, int id, int ex, int day ,int hour);
	void Execute();

};
