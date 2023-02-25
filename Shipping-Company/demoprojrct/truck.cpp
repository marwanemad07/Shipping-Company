#include "truck.h"

truck::truck() : MoveTime(1e9, 1e9), activeTime(0, 0), returnTime(0, 0)
{
	setJourenyCnt();
	VipAssigned = false;
	SpecialAssigned = false;
	NormalAssigned = false;
	Assigned = false;
	CheckUpCnt = 0;
	totactive = 0;
}
truck::truck(int id) : MoveTime(0, 0), activeTime(0, 0), returnTime(0, 0)
{
	setJourenyCnt();
	VipAssigned = false;
	SpecialAssigned = false;
	NormalAssigned = false;
	Assigned = false;
	CheckUpCnt = 0;
	ID = id;
	TDC = 0;
}

void truck::incJourneyCnt()
{
	journeyCnt++;
}
int truck::getNoJoureny(){
	return no_Journeys;
}
int truck::getID(){
	return ID;
}
void truck::setNoJoureny(int s){
	no_Journeys = s;
}
int truck::getJourenyCnt() const
{
	return journeyCnt;
}

void truck::pushNC(Normalcargos* temp, int speed, int type)
{
	if (type == 0)
	{
		NC.enqueue(temp, 0);
	}
	else
	{
		setCDT(temp, speed);
		int priority = temp->getCDTday() * 100 + temp->getCDThour();
		NC.enqueue(temp, -priority);
	}
}

void truck::pushSC(Specialcargos* temp, int speed, int type)
{
	setCDT(temp, speed);
	if (type == 0)
		SC.enqueue(temp, 0);
	else
	{
		int priority = temp->getCDTday() * 100 + temp->getCDThour();
		SC.enqueue(temp, -priority);
	}
}

void truck::pushVC(VIPcargos* temp, int speed, int type)
{
	setCDT(temp, speed);
	if (type == 0)
		VC.enqueue(temp, 0);
	else
	{
		int priority = temp->getCDTday() * 100 + temp->getCDThour();
		VC.enqueue(temp, -priority);
	}
}

void truck::setJourenyCnt()
{
	journeyCnt = 0;
}
int truck::IncCheckUpCnt()
{
	return CheckUpCnt++;
}
int truck::getCheckUpCnt() const
{
	return CheckUpCnt;
}
void truck::setCheckUpCnt(int x){
	CheckUpCnt = x;
}
PriorityQueue<Normalcargos*, int>*truck::getNC(){
	return &NC;
}
PriorityQueue<VIPcargos*, int>* truck::getVC(){
	return &VC;
}
PriorityQueue<Specialcargos*, int>* truck::getSC(){
	return &SC;
}
void truck::setMoveTime(int day, int hour)
{
	while (hour > 23)
	{
		hour -= 24;
		day++;
	}
	MoveTime.setDay(day);
	MoveTime.setHour(hour);
}

void truck::getMoveTime(int& day, int& hour)
{
	day = MoveTime.getDay();
	hour = MoveTime.getHour();
}

void truck::setCDT(Cargos* cargo, int truckSpeed)
{
	int distance = cargo->getDelDist();
	int h, d;
	getMoveTime(d, h);
	int hours = h + ceil((double)distance / (double)truckSpeed )+ cargo->getLoadTime();
	int days = d;
	while (hours > 23)
	{
		hours -= 24;
		days++;
	}
	cargo->setCDT(days, hours);
}

void truck::setAssigned(bool flag)
{
	Assigned = flag;
}

bool truck::getAssigned()
{
	return Assigned;
}

bool truck::peekNC(Normalcargos*& temp)
{
	return NC.peek(temp);
}

bool truck::peekSC(Specialcargos*& temp)
{
	return SC.peek(temp);
}

bool truck::peekVC(VIPcargos*& temp)
{
	return VC.peek(temp);
}

bool truck::getNC(Normalcargos*& temp)
{
	int x;
	bool flag = NC.getSize();
	if (flag)    NC.dequeue(temp, x);
	return flag;
}

bool truck::getSC(Specialcargos*& temp)
{
	int x;
	bool flag = SC.getSize();
	if (flag)    SC.dequeue(temp, x);
	return flag;
}

bool truck::getVC(VIPcargos*& temp)
{
	int x;
	bool flag = VC.getSize();
	if (flag)   
	VC.dequeue(temp, x);
	return flag;
}
void truck::getactiveTime(int &d, int&h)
{
	d = activeTime.getDay();
	h = activeTime.getHour();
}

void truck::setactiveTime(int d, int h)
{
	activeTime.setDay(d);
	activeTime.setHour(h);
}

int truck::getCargosSize() 
{
	return NC.getSize() + SC.getSize() + VC.getSize();
}
void truck::setReturnTime(int day, int hour)// day = CDT.day && hour = CDT.hour
{
	hour += returnHours;
	while (hour > 23)
	{
		hour -= 24;
		day++;
	}
	returnTime.setDay(day);
	returnTime.setHour(hour);
}
void truck::getReturnTime(int& day, int& hour)
{
	day = returnTime.getDay();
	hour = returnTime.getHour();
}
void truck::setReturnHours(int hours)
{
	returnHours = hours;
}
int truck::getTDC(){
	return TDC;
}
void  truck::incrementTDC(){
	TDC++;
}
void truck:: settotactive(double a){
	totactive += a;
}
double truck:: gettotactive(){
	return totactive;
}
truck::~truck(){

}