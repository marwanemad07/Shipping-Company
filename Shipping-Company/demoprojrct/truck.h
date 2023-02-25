#pragma once
#include <iostream>
#include "PriorityQueue.h"
#include "Normalcargos.h"
#include "Specialcargos.h"
#include "VIPcargos.h"
#include "TIME_cnt.h"

using namespace std;
class truck
{
protected:
	int journeyCnt;
	int no_Journeys;
	int CheckUpCnt;
	int TDC;
	PriorityQueue<Normalcargos*, int> NC;
	PriorityQueue<Specialcargos*, int> SC;
	PriorityQueue<VIPcargos*, int> VC;
	int ID;
	bool VipAssigned;
	bool SpecialAssigned;
	bool NormalAssigned;
	bool Assigned;
	TIME_cnt MoveTime;
	TIME_cnt activeTime;
	TIME_cnt returnTime;
	double totactive;
	int returnHours;
public:
	truck();
	truck(int );
	void incJourneyCnt(); //increment journey counter
	void setJourenyCnt(); // setter after complete max journeys
	int getNoJoureny();
	void setNoJoureny(int s);
	int getJourenyCnt() const;
	int IncCheckUpCnt();
	int getCheckUpCnt() const;
	void setCheckUpCnt(int);
	void setMoveTime(int day, int hour);
	void getMoveTime(int& day, int& hour);
	// if type = 0 we push in loading ,otherwise we push based on (negative) CDT 
	void settotactive(double);
	double gettotactive();
	void pushNC(Normalcargos* temp, int speed = 0, int type = 0);
	void pushSC(Specialcargos* temp, int speed = 0, int type = 0);
	void pushVC(VIPcargos* temp, int speed = 0, int type = 0);

	PriorityQueue<Normalcargos*, int>*getNC();
	PriorityQueue<Specialcargos*, int>* getSC();
	PriorityQueue<VIPcargos*, int>* getVC();
	int getID();
	void setCDT(Cargos* cargo, int truckSpeed);

	void getactiveTime(int &d, int&h);
	void setactiveTime(int d, int h);
	void setAssigned(bool flag);
	bool getAssigned();

	bool peekNC(Normalcargos*& temp); // functions to peek first element int the queue
	bool peekSC(Specialcargos*& temp);
	bool peekVC(VIPcargos*& temp);

	bool getNC(Normalcargos*& temp);
	bool getSC(Specialcargos*& temp);
	bool getVC(VIPcargos*& temp);
	int getCargosSize() ;


	void setReturnTime(int day, int hour);
	void getReturnTime(int& day, int& hour);
	void setReturnHours(int hours);
	int getTDC();
	void incrementTDC();
	virtual double getdelivertTime() = 0;
	virtual ~truck();
};