#pragma once
#include<string>
#include "TIME_cnt.h"
using namespace std;
class Cargos
{
private:
	TIME_cnt Preparation_Time, WT;
	int MT;
	int ID;
	int LT;  // load time
	int Cost;
	double DeliveryDistance;
	int TID;
	TIME_cnt CDT;
	bool Assigned;
public:
	Cargos(int id, double distance, int loadtime, int cost, int prep_day, int prep_hour);
	virtual double GetCost();
	double GetDeliveryDistance();
	void setCDT(int day, int hour);
	/*virtual bool assign();*/
	void  SetDeliveryDistance(double);
	int getTID();
	void setTID(int);
	int getWTHour();
	void setWTHour(int);
	int getWTDay();
	void setWTDay(int);
	void SetCost(double);
	int getmainID() const;
	int getCost() const;
	int getCDTday() const;
	int getCDThour()const;
	int getDelDist()  const; // getter for DeliveryDistance
	int getLoadTime() const;
	bool getAssigned() const;
	int getPrepDay() const;
	int getPrepHour() const;
	void setAssigned(bool flag);

	virtual~Cargos()=0;
};

