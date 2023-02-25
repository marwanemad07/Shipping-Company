#include "company.h"
#include"Preparation.h"
#include "Promotion.h"
#include"Cancellation.h"
#include "windows.h"
#include"UI.h"
#include <conio.h>
#include<Windows.h>
#include<cmath>
company::company(int day, int hour) :Time(day, hour), IntialTime(day, hour)
{

	uptr = new UI(this);
	Eventcounter = 0;
	AutoProSize = 0;
	TruckActTime = 0;
}
TIME_cnt company::getIntialTime(){
	return IntialTime;
}
int company::getActTime()
{
	return TruckActTime;
}
Event** company::getEvents() {
	return Events;
}
Queue<Cargos*>*company:: getDeliverdCargos()
{
	return &DeliverdCargos;
}
int company::getEventcounter(){
	return Eventcounter;
}
PriorityQueue<VIPcargos*, int>* company::GetwaitingVC() {
	return &waitingVC;
}
LinkedList<Normalcargos*>* company::GetwaitingNC()
{
	return &waitingNC;
}
Queue<Specialcargos*>* company::GetwaitingSC() {
	return &waitingSC;
}
int company::getLoadingTrucksSize(){
	return LoadingNT.getSize() + LoadingST.getSize() + LoadingVT.getSize();
}

Queue<VIPcargos*>* company::GetMovingVC() {
	return &MovingVC;
}
Queue<Normalcargos*>* company::GetMovingNC() {
	return &MovingNC;
}
Queue<Specialcargos*>* company::GetMovingSC() {
	return &MovingSC;
}
int company::WaitingCargosFullsize() {
	return waitingNC.getSize() + waitingSC.getSize() + waitingVC.getSize();
}
int company::getPromtionLimit() {
	return AutoP;
}
TIME_cnt company::getTime() {
	return Time;
}
Queue<NormalTruck*>* company::getavlbl_N() {
	return &avlbl_N;
}
Queue<SpecialTruck*>* company::getavlbl_S() {
	return &avlbl_S;
}
Queue<VIPTruck*>* company::getavlbl_VIP() {
	return& avlbl_VIP;
}
PriorityQueue<truck*, int>* company::getMovingTrucks() {
	return&MovingTrucks;
}

LinkedList<NormalTruck*>*company::getLoadingNT(){
	return&LoadingNT;
}
LinkedList<SpecialTruck*>*company::getLoadingST(){
	return& LoadingST;
}
LinkedList<VIPTruck*>* company::getLoadingVT(){
	return &LoadingVT;
}

Queue<NormalTruck*>* company::getCheck_UpNormal() {
	return &Check_UpNormal;
}
Queue<SpecialTruck*>* company::getCheck_UpSpecial() {
	return &Check_UpSpecial;
}
Queue<VIPTruck*>* company::getCheck_UpVIP() {
	return &Check_UpVIP;
}

void company::setTime(TIME_cnt a) {
	Time = a;
}
void centerstring(char* s)
{
	int l = strlen(s);
	int pos = (int)((100 - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";
	cout << s << endl;
}
void company::simulator()
{
	string FileName;
	char t;
	uptr->Intro(FileName,t);
	loading(FileName);
	if (t != 'C' && t != 'I' && t != 'S')t = 'I';
	while (Eventcounter < no_events || waitingNC.getSize()
			|| waitingSC.getSize() || waitingVC.getSize() || MovingTrucks.getSize() || LoadingNT.getSize() ||
			LoadingST.getSize() || LoadingVT.getSize() || returnTrucks.getSize() || IncheckUpTrucksSize()
	)
	{
		if (WorkingHours())
		{
			ExecuteEvent();
			AssignCargos();
		}
		uptr->UiModes(t);
		if (WorkingHours())
		{
			
			LoadingCargos();
		}
		MovingAction();
		CheckUpAction();
		incrementTime();
	}
	uptr->UiModes(t);
	Sleep(500);
	uptr->CreatFile();
	
}
PriorityQueue<truck*, int>*company::getreturnTrucks()
{
	return&returnTrucks;
}
int company:: getRetrunTruckssize(){
	return returnTrucks.getSize();
}

void company::ExecuteEvent()
{
	while(Eventcounter <no_events && getTime().getDay() >= Events[Eventcounter]->getDay() && getTime().getHour() >= Events[Eventcounter]->getHour())
	{
		Preparation*R = dynamic_cast<Preparation*>(Events[Eventcounter]);
		Promotion*Pro = dynamic_cast<Promotion*>(Events[Eventcounter]);
		Cancellation*C = dynamic_cast<Cancellation*>(Events[Eventcounter]);

		//execute events
		if (R){
			R->Execute();
		}
		else if (Pro){
			Pro->Execute();
		}
		else{
			C->Execute();
		}
		Eventcounter++;
	}
}
void company::incrementTime() {
	Time.setHour(Time.getHour() + 1);
	if (Time.getHour() == 24) {
		Time.setDay(Time.getDay() + 1);
		Time.setHour(0);
	}
}

int company::getno_events() {
	return no_events;
}
void company::calc_time(int& d, int& h, string Time) {
	int i = 0;
	while (Time[i] != ':') {
		i++;
	}
	string day, hour;
	day = Time.substr(0, i);
	d = stoi(day);
	hour = Time.substr(i + 1, 2);
	h = stoi(hour);

}

UI* company::getUi() {
	return uptr;
}
void company::loading(string FileName) {
	in.open(FileName+".txt");
	int arr[15];
	for (int i = 0; i < 15; i++) {
		in >> arr[i];
	}
	//size for each truck
	NormalCap = arr[6], SpecialCap = arr[7], VipCap = arr[8];
	NormalSize = arr[0]; VipSize = arr[2]; SpecialSize = arr[1];
	//Viptrucks
	VIPTruck(arr[8], arr[12], arr[5]);
	for (int i = 0; i < VipSize; i++)
	{
		VIPTruck* pt = new VIPTruck(i+1);
		pt->setNoJoureny(arr[12]);
		avlbl_VIP.enqueue(pt);
	}
	//Normal trucks
	NormalTruck(arr[6], arr[10], arr[3]);
	for (int i = 0; i < NormalSize; i++)
	{
		NormalTruck* pt = new NormalTruck(i + 1 + VipSize);
		pt->setNoJoureny(arr[12]);
		avlbl_N.enqueue(pt);
	}
	//Special trucks
	SpecialTruck(arr[7], arr[11], arr[4]);
	for (int i = 0; i < SpecialSize; i++)
	{
		SpecialTruck* pt = new SpecialTruck(i + 1 + VipSize + NormalSize);
		pt->setNoJoureny(arr[12]);
		avlbl_S.enqueue(pt);
	}
	mainTimeNormal = arr[9], mainTimeSpecial = arr[10], mainTimeVIP = arr[11];
	AutoP = arr[13];
	MaxW = arr[14];
	in >> no_events;
	Events = new Event * [no_events];
	for (int i = 0; i < no_events; i++)
	{
		char event, type;
		string time;
		int ID, DIST, LT, Cost;
		int day, hour;
		in >> event;

		if (event == 'R') {
			in >> type >> time >> ID >> DIST >> LT >> Cost;
			calc_time(day, hour, time);
			Events[i] = new Preparation(this, type, ID, DIST, LT, Cost, day, hour);
		}
		else if (event == 'P')
		{
			in >> time >> ID >> Cost;//cost=extra money
			calc_time(day, hour, time);
			Events[i] = new Promotion(this, ID, Cost, day, hour);

		}
		else {
			in >> time >> ID;
			calc_time(day, hour, time);
			Events[i] = new Cancellation(this, ID, day, hour);
		}
	}
}



void company::Waiting_VIP_push(VIPcargos* vipCargo)
{
	int priority = vipCargo->VIPeq();
	waitingVC.enqueue(vipCargo, priority); // 0 must be replaced by a vlue from the eq from pdf
}

bool company::WorkingHours() {
	return(Time.getHour() >= 5 && Time.getHour() <= 23);

}
void company::AssignCargos() {


	if (WorkingHours())
	{
		int firstprepday = 0, firstprephour = 0;
		int maxday = -1, maxhour = -1;
		int z = 1;
		int maxDist = -1;

		if (waitingVC.getSize() >= VipCap && avlbl_VIP.getSize())
		{
			maxday = -1, maxhour = -1;
			int sz = VipCap;
			int dummy = sz, day, hour;
			VIPTruck* temp;
			avlbl_VIP.dequeue(temp);
			VIPcargos* toLoad;
			temp->peekVC(toLoad);
			int x, loadTime = 0, prephour = 0, prepday = 0, firstprepday = 0, firstprephour = 0;
			if (z){
				z--;
				firstprepday = Time.getDay();
				firstprephour = Time.getHour();
			}
			while (sz--)
			{
				waitingVC.dequeue(toLoad, x);
				maxDist = max(toLoad->getDelDist(), maxDist);
				toLoad->setTID(temp->getID());
				loadTime += toLoad->getLoadTime();
				if (toLoad->getPrepDay() >= prepday)
				{
					prepday = toLoad->getPrepDay();
					if (toLoad->getPrepHour() >= prephour) prephour = toLoad->getPrepHour();
				}
				if (sz == 0)
				{
					if (LoadingVT.getSize())
					{
						Node<VIPTruck*>* node = LoadingVT.getHead();
						VIPTruck* lastLoadedTruck = LoadingVT.getHead()->getItem(); // temp to traverse linkedList  
						while (node->getNext())
						{
							node = node->getNext();
							lastLoadedTruck = node->getItem();
						}
						lastLoadedTruck->getMoveTime(day, hour);
					}
					else
					{
						day = toLoad->getPrepDay();
						hour = toLoad->getPrepHour();
					}
					if (day < Time.getDay())
					{
						day = Time.getDay();
						hour = Time.getHour();
					}
					else if (day == Time.getDay()) hour = Time.getHour() > hour ? Time.getHour() : hour;
					temp->setMoveTime(day, loadTime + hour);
				}
				temp->pushVC(toLoad, temp->getSpeed());
				temp->incrementTDC();
				temp->setAssigned(true);

			}
			temp->setReturnHours(maxDist / temp->getSpeed());
			sz = VipCap;
			PriorityQueue<VIPcargos*, int> q;
			while (sz--)
			{
				temp->getVC(toLoad);
				q.enqueue(toLoad, 0);
				int d, h;
				temp->getMoveTime(d, h);
				toLoad->setWTDay(d - toLoad->getPrepDay());
				toLoad->setWTHour(abs(h - toLoad->getPrepHour()));
				toLoad->setTID(temp->getID());
			
			}
			// calculate active time for a truck
			
			
			while (q.getSize())
			{
				int x;
				q.dequeue(toLoad, x);
				toLoad->setTID(temp->getID());
				temp->pushVC(toLoad, temp->getSpeed(), 1);
				if (toLoad->getCDTday() >= maxday)
				{
					maxday = toLoad->getCDTday();
					if (toLoad->getCDTday() > maxday)
					{
						maxhour = toLoad->getCDThour();
					}
					else {
						maxhour = maxhour > toLoad->getCDThour() ? maxhour : toLoad->getCDThour();
					}
				}

			}
			int z, c;
			temp->getMoveTime(z, c);
			TruckActTime += (maxday * 24 + maxhour + loadTime) - (z * 24 + c);
			temp->settotactive((maxday * 24 + maxhour + loadTime) - (z * 24 + c));
			temp->setReturnTime(maxday, maxhour);
			temp->setAssigned(true);
			LoadingVT.InsertEnd(temp);

		}
/**/		else if (waitingVC.getSize() >= NormalCap && avlbl_N.getSize())
		{
			int sz = NormalCap;
			NormalTruck* temp; avlbl_N.dequeue(temp);
			int maxday = -1, maxhour = -1, day, hour;
			VIPcargos* toLoad;
			waitingVC.peek(toLoad);
			int x, loadTime = 0, prephour = 0, prepday = 0, firstprepday = 0, firstprephour = 0;
			if (z){
				z--;
				firstprepday = Time.getDay();
				firstprephour = Time.getHour();
			}
			while (sz--)
			{
				waitingVC.dequeue(toLoad, x);
				toLoad->setTID(temp->getID());
				maxDist = max(toLoad->getDelDist(), maxDist); // maxCargoDistance
				temp->pushVC(toLoad, temp->getSpeed());
				temp->incrementTDC();
				loadTime += toLoad->getLoadTime();
				if (toLoad->getPrepDay() >= prepday)
				{
					prepday = toLoad->getPrepDay();
					if (toLoad->getPrepHour() >= prephour) prephour = toLoad->getPrepHour();
				}
				if (sz == 0)
				{
					if (LoadingNT.getSize())
					{
						Node<NormalTruck*>* node = LoadingNT.getHead();
						NormalTruck* lastLoadedTruck = LoadingNT.getHead()->getItem(); // temp to traverse linkedList  
						while (node->getNext())
						{
							node = node->getNext();
							lastLoadedTruck = node->getItem();
						}
						lastLoadedTruck->getMoveTime(day, hour);
					}
					else
					{
						day = toLoad->getPrepDay();
						hour = toLoad->getPrepHour();
					}
					if (day < Time.getDay())
					{
						day = Time.getDay();
						hour = Time.getHour();
					}
					else if (day == Time.getDay()) hour = Time.getHour() > hour ? Time.getHour() : hour;
					temp->setMoveTime(day, loadTime + hour);
				}
			}
			temp->setReturnHours(maxDist / temp->getSpeed());
			sz = NormalCap;
			PriorityQueue<VIPcargos*, int> q;
			while (sz--)
			{
				temp->getVC(toLoad);
				q.enqueue(toLoad, 0);
				int d, h;
				temp->getMoveTime(d, h);
				toLoad->setWTDay(d - toLoad->getPrepDay());
				toLoad->setWTHour(abs(h - toLoad->getPrepHour()));
				toLoad->setTID(temp->getID());
				
			}

			// calculate active time for a truck
			
			while (q.getSize())
			{
				int x;
				q.dequeue(toLoad, x);
				temp->pushVC(toLoad, temp->getSpeed(), 1);
				if (toLoad->getCDTday() >= maxday)
				{
					maxday = toLoad->getCDTday();
					if (toLoad->getCDTday() > maxday) {
						maxhour = toLoad->getCDThour();
					}
					else {
						maxhour = maxhour > toLoad->getCDThour() ? maxhour : toLoad->getCDThour();
					}
				}
			}
			int z, c;
			temp->getMoveTime(z, c);
			TruckActTime += (maxday * 24 + maxhour+loadTime) - (z * 24 + c);
			temp->settotactive((maxday * 24 + maxhour + loadTime) - (z * 24 + c));
			temp->setReturnTime(maxday, maxhour);
			temp->setAssigned(true);
			LoadingNT.InsertEnd(temp);
		}

		else if (waitingVC.getSize() >= SpecialCap && avlbl_S.getSize())
		{
			int sz = SpecialCap;
			SpecialTruck* temp; avlbl_S.dequeue(temp);
			int maxday = -1, maxhour = -1, day, hour;
			VIPcargos* toLoad;
			waitingVC.peek(toLoad);
			int x, loadTime = 0, prephour = 0, prepday = 0, firstprepday = 0, firstprephour = 0;
			if (z){
				z--;
				firstprepday = Time.getDay();
					firstprephour = Time.getHour();
			}
			while (sz--)
			{
				waitingVC.dequeue(toLoad, x);
				toLoad->setTID(temp->getID());

				maxDist = max(toLoad->getDelDist(), maxDist); // maxCargoDistance

				temp->pushVC(toLoad, temp->getSpeed());
				temp->incrementTDC();
				loadTime += toLoad->getLoadTime();
				if (toLoad->getPrepDay() >= prepday)
				{
					prepday = toLoad->getPrepDay();
					if (toLoad->getPrepHour() >= prephour) prephour = toLoad->getPrepHour();
				}
				if (sz == 0)
				{
					if (LoadingST.getSize())
					{
						Node<SpecialTruck*>* node = LoadingST.getHead();
						SpecialTruck* lastLoadedTruck = LoadingST.getHead()->getItem(); // temp to traverse linkedList  
						while (node->getNext())
						{
							node = node->getNext();
							lastLoadedTruck = node->getItem();
						}
						lastLoadedTruck->getMoveTime(day, hour);
					}
					else
					{
						day = toLoad->getPrepDay();
						hour = toLoad->getPrepHour();
					}

					if (day < Time.getDay())
					{
						day = Time.getDay();
						hour = Time.getHour();
					}
					else if (day == Time.getDay()) hour = Time.getHour() > hour ? Time.getHour() : hour;
					temp->setMoveTime(day, loadTime + hour);
				}
			}
			temp->setReturnHours(maxDist / temp->getSpeed());

			sz = SpecialCap;
			PriorityQueue<VIPcargos*, int> q;
			while (sz--)
			{
				temp->getVC(toLoad);
				q.enqueue(toLoad, 0);
				int d, h;
				temp->getMoveTime(d, h);
				toLoad->setWTDay(d - toLoad->getPrepDay());
				toLoad->setWTHour(abs(h - toLoad->getPrepHour()));
				toLoad->setTID(temp->getID());
				
			}

			// calculate active time for a truck
			 // active time not return time
			while (q.getSize())
			{
				int x;
				q.dequeue(toLoad, x);
				temp->pushVC(toLoad, temp->getSpeed(), 1);
				if (toLoad->getCDTday() >= maxday)
				{
					maxday = toLoad->getCDTday();
					if (toLoad->getCDTday() > maxday) {
						maxhour = toLoad->getCDThour();
					}
					else {
						maxhour = maxhour > toLoad->getCDThour() ? maxhour : toLoad->getCDThour();
					}
				}

			}
			int z, c;
			temp->getMoveTime(z, c);
			TruckActTime += (maxday * 24 + maxhour + loadTime) - (z * 24 + c);
			temp->settotactive((maxday * 24 + maxhour + loadTime) - (z * 24 + c));
			temp->setAssigned(true);
			temp->setReturnTime(maxday, maxhour);
			LoadingST.InsertEnd(temp);
		}

		firstprepday = 0, firstprephour = 0;
		maxday = -1, maxhour = -1;
		z = 1;
		Specialcargos* togetMaxW;
		int specialMaxW = -1;
		bool flag = waitingSC.peek(togetMaxW);
		if (flag)
		{
			int days = Time.getDay() - togetMaxW->getPrepDay();
			if (days == 0)
			{
				specialMaxW = Time.getHour() - togetMaxW->getPrepHour();
			}
			else if (days > 0)
				specialMaxW = days * 24 + (Time.getHour() - togetMaxW->getPrepHour());
		}
		maxDist = -1;
		if ((waitingSC.getSize() >= SpecialCap || MaxW <= specialMaxW) && avlbl_S.getSize())
		{
			int sz = (waitingSC.getSize() >= SpecialCap) ? SpecialCap : waitingSC.getSize();
			int dummy = sz;

			SpecialTruck* temp; avlbl_S.dequeue(temp);
			Specialcargos* toLoad;
			int maxday = -1, maxhour = -1, day, hour;
			waitingSC.peek(toLoad);
			int x, loadTime = 0, prephour = 0, prepday = 0, firstprepday = 0, firstprephour = 0;
			if (z){
				z--;
				firstprepday = Time.getDay();
				firstprephour = Time.getHour();
			}
			while (sz--)
			{
				waitingSC.dequeue(toLoad);
				toLoad->setTID(temp->getID());
				maxDist = max(toLoad->getDelDist(), maxDist); // maxCargoDistance

				temp->pushSC(toLoad, temp->getSpeed());
				temp->incrementTDC();
				loadTime += toLoad->getLoadTime();
				if (sz == 0)
				{
					if (LoadingST.getSize())
					{
						Node<SpecialTruck*>* node = LoadingST.getHead();
						SpecialTruck* lastLoadedTruck = LoadingST.getHead()->getItem(); // temp to traverse linkedList  
						while (node->getNext())
						{
							node = node->getNext();
							lastLoadedTruck = node->getItem();
						}
						lastLoadedTruck->getMoveTime(day, hour);
					}
					else
					{
						day = toLoad->getPrepDay(), hour = toLoad->getPrepHour();
					}
					if (day < Time.getDay())
					{
						day = Time.getDay();
						hour = Time.getHour();
					}
					else if (day == Time.getDay()) hour = Time.getHour() > hour ? Time.getHour() : hour;
					temp->setMoveTime(day, loadTime + hour);
				}
			}
			temp->setReturnHours(maxDist / temp->getSpeed());

			sz = dummy;
			PriorityQueue<Specialcargos*, int> q;
			while (sz--)
			{
				temp->getSC(toLoad);
				q.enqueue(toLoad, 0);
				int d, h;
				temp->getMoveTime(d, h);
				toLoad->setWTDay(d - toLoad->getPrepDay());
				toLoad->setWTHour(abs(h - toLoad->getPrepHour()));
				toLoad->setTID(temp->getID());
				
			}

			// calculate active time for a truck
			
			while (q.getSize())
			{
				int x;
				q.dequeue(toLoad, x);
				temp->pushSC(toLoad, temp->getSpeed(), 1);
				if (toLoad->getCDTday() >= maxday)
				{
					maxday = toLoad->getCDTday();
					if (toLoad->getCDTday() > maxday) {
						maxhour = toLoad->getCDThour();
					}
					else {
						maxhour = maxhour > toLoad->getCDThour() ? maxhour : toLoad->getCDThour();
					}
				}
			}
			int z, c;
			temp->getMoveTime(z, c);
			TruckActTime += (maxday * 24 + maxhour + loadTime) - (z * 24 + c);
			temp->settotactive((maxday * 24 + maxhour + loadTime) - (z * 24 + c));

			temp->setReturnTime(maxday, maxhour);
			temp->setAssigned(true);
			LoadingST.InsertEnd(temp);
		}
		//***********************************************************
		firstprepday = 0, firstprephour = 0;
		maxday = -1, maxhour = -1;
		z = 1;
		maxDist = -1;

		Normalcargos* togetMaxWNormal;
		int normalMaxW = -1;
		if (!waitingNC.getHead())return;
		togetMaxWNormal = waitingNC.getHead()->getItem();

		// to get max wait time of first Normal cargo
		if (togetMaxWNormal)
		{
			int days = Time.getDay() - togetMaxWNormal->getPrepDay();
			if (days == 0)
			{
				normalMaxW = Time.getHour() - togetMaxWNormal->getPrepHour();
			}
			else if (days > 0)
				normalMaxW = days * 24 + (Time.getHour() - togetMaxWNormal->getPrepHour());
		}


		if ((waitingNC.getSize() >= NormalCap || MaxW <= normalMaxW) && avlbl_N.getSize())
		{
			int sz = (waitingNC.getSize() >= NormalCap) ? NormalCap : waitingNC.getSize();
			int dummy = sz;
			NormalTruck* temp;
			avlbl_N.dequeue(temp);
			Normalcargos* toLoad;
			int maxday = -1, maxhour = -1,day, hour;
			temp->peekNC(toLoad);
			int x, loadTime = 0, prephour = 0, prepday = 0;
			if (z){
				z--;
				firstprepday = Time.getDay();
				firstprephour = Time.getHour();
			}
			while (sz--)
			{
				waitingNC.deletebeg(toLoad);
				toLoad->setTID(temp->getID());
				maxDist = max(toLoad->getDelDist(), maxDist); // maxCargoDistance

				temp->pushNC(toLoad, temp->getSpeed());
				temp->incrementTDC();
				loadTime += toLoad->getLoadTime();
				if (sz == 0)
				{
					if (LoadingNT.getSize())
					{
						Node<NormalTruck*>* node = LoadingNT.getHead();
						NormalTruck* lastLoadedTruck = LoadingNT.getHead()->getItem(); // temp to traverse linkedList  
						while (node->getNext())
						{
							node = node->getNext();
							lastLoadedTruck = node->getItem();
						}
						lastLoadedTruck->getMoveTime(day, hour);
					}
					else
					{
						day = toLoad->getPrepDay(), hour = toLoad->getPrepHour();
					}
					if (day < Time.getDay())
					{
						day = Time.getDay();
						hour = Time.getHour();
					}
					else if (day == Time.getDay()) hour = Time.getHour() > hour ? Time.getHour() : hour;
					temp->setMoveTime(day, loadTime + hour);
				}
			}
			temp->setReturnHours(maxDist / temp->getSpeed());

			sz = dummy;
			PriorityQueue<Normalcargos*, int> q;
			while (sz--)
			{
				temp->getNC(toLoad);
				q.enqueue(toLoad, 0);
				int d, h;
				temp->getMoveTime(d, h);
				toLoad->setWTDay(d - toLoad->getPrepDay());
				toLoad->setWTHour(abs(h - toLoad->getPrepHour()));
				toLoad->setTID(temp->getID());
				
			}

			// calculate active time for a truck

			while (q.getSize())
			{
				int x;
				q.dequeue(toLoad, x);
				temp->pushNC(toLoad, temp->getSpeed(), 1);
				if (toLoad->getCDTday() >= maxday)
				{
					maxday = toLoad->getCDTday();
					if (toLoad->getCDTday() > maxday) {
						maxhour = toLoad->getCDThour();
					}
					else {
						maxhour = maxhour > toLoad->getCDThour() ? maxhour : toLoad->getCDThour();
					}
				}

			}
			int z, c;
			temp->getMoveTime(z, c);
			TruckActTime += (maxday * 24 + maxhour + loadTime) - (z * 24 + c);
			temp->settotactive((maxday * 24 + maxhour + loadTime) - (z * 24 + c));

			temp->setReturnTime(maxday, maxhour);
			temp->setAssigned(true);
			LoadingNT.InsertEnd(temp);
		}
		else if ((waitingVC.getSize() >= VipCap || MaxW <= normalMaxW) && avlbl_VIP.getSize())
		{
			int sz = (waitingNC.getSize() >= VipCap) ? VipCap : waitingNC.getSize();
			int dummy = sz;
			VIPTruck* temp; avlbl_VIP.dequeue(temp);
			Normalcargos* toLoad;
			
			int x, loadTime = 0, prephour = 0, prepday = 0, day, hour;
			while (sz--)
			{
				waitingNC.deletebeg(toLoad);
				if (z)
				{
					z--;
					firstprepday =  Time.getDay();
					firstprephour = Time.getHour();
				}
				toLoad->setTID(temp->getID());
				maxDist = max(toLoad->getDelDist(), maxDist); // maxCargoDistance

				loadTime += toLoad->getLoadTime();
				if (sz == 0)
				{
					if (LoadingVT.getSize())
					{
						Node<VIPTruck*>* node = LoadingVT.getHead();
						VIPTruck* lastLoadedTruck = LoadingVT.getHead()->getItem(); // temp to traverse linkedList  
						while (node->getNext())
						{
							node = node->getNext();
							lastLoadedTruck = node->getItem();
						}
						lastLoadedTruck->getMoveTime(day, hour);
					}
					else
					{
						day = toLoad->getPrepDay(), hour = toLoad->getPrepHour();
					}
					if (day < Time.getDay())
					{
						day = Time.getDay();
						hour = Time.getHour();
					}
					else if (day == Time.getDay()) hour = Time.getHour() > hour ? Time.getHour() : hour;

					temp->setMoveTime(day, loadTime + hour);
				}
				temp->pushNC(toLoad, temp->getSpeed());
				temp->incrementTDC();
			}
			temp->setReturnHours(maxDist / temp->getSpeed());

			sz = dummy;
			PriorityQueue<Normalcargos*, int> q;
			while (sz--)
			{
				temp->getNC(toLoad);
				q.enqueue(toLoad, 0);
				int d, h;
				temp->getMoveTime(d, h);
				toLoad->setWTDay(d - toLoad->getPrepDay());
				toLoad->setWTHour(abs(h - toLoad->getPrepHour()));
				toLoad->setTID(temp->getID());
			}
			while (q.getSize())
			{
				int x;
				q.dequeue(toLoad, x);
				temp->pushNC(toLoad, temp->getSpeed(), 1);
				if (toLoad->getCDTday() >= maxday)
				{
					maxday = toLoad->getCDTday();
					if (toLoad->getCDTday() > maxday) {
						maxhour = toLoad->getCDThour();
					}
					else {
						maxhour = maxhour > toLoad->getCDThour() ? maxhour : toLoad->getCDThour();
					}
				}
				
			}
			int z, c;
			temp->getMoveTime(z, c);
			TruckActTime += (maxday * 24 + maxhour + loadTime) - (z * 24 + c);
			temp->settotactive((maxday * 24 + maxhour + loadTime) - (z * 24 + c));

			temp->setReturnTime(maxday, maxhour);

			temp->setAssigned(true);
			LoadingVT.InsertEnd(temp);
		}
		// to check autoP here
		if (waitingNC.getSize())
		{
			Normalcargos* topNC = waitingNC.getHead()->getItem();
			if ((Time.getDay() - topNC->getPrepDay() == AutoP) && Time.getHour() >= topNC->getPrepHour())
			{

				Promotion* P = new Promotion(this, topNC->getmainID(), 0, Time.getDay(), Time.getHour());
				autoPro[AutoProSize] = P;
				P->Execute();
				AutoProSize++;
				waitingNC.deletebeg(topNC);
			}
		}

	}


}


int company::getAutoProSize(){
	return AutoProSize;
}
void company::LoadingCargos()
{
	NormalTruck* tempNT = NULL; SpecialTruck* tempST = NULL; VIPTruck* tempVIPT = NULL;
	Normalcargos* tempNC = NULL; Specialcargos* tempSC = NULL; VIPcargos* tempVIPC = NULL;

	if (LoadingNT.getHead())
		tempNT = LoadingNT.getHead()->getItem();
	if (LoadingST.getHead())
		tempST = LoadingST.getHead()->getItem();
	if (LoadingVT.getHead())
		tempVIPT = LoadingVT.getHead()->getItem();
	int day, hour;
	if (tempVIPT)
	{
		tempVIPT->getMoveTime(day, hour);
		if (tempVIPT->getAssigned() && Time.getDay() >= day && Time.getHour() >= hour)
		{
			tempVIPT->setAssigned(false);
			LoadingVT.deletebeg(tempVIPT);
			int priority = 0;

			if (tempVIPT->peekNC(tempNC)) priority = -tempNC->getCDTday() * 100 - tempNC->getCDThour();
			else if (tempVIPT->peekSC(tempSC)) priority = -tempSC->getCDTday() * 100 - tempSC->getCDThour();
			else if (tempVIPT->peekVC(tempVIPC)) priority = -tempVIPC->getCDTday() * 100 - tempVIPC->getCDThour();
			MovingTrucks.enqueue(tempVIPT, priority);
		}
	}

	if (tempNT)
	{
		tempNT->getMoveTime(day, hour);
		if (tempNT->getAssigned() && Time.getDay() >= day && Time.getHour() >= hour)
		{
			tempNT->setAssigned(false);
			LoadingNT.deletebeg(tempNT);
			int priority = 0;

			if (tempNT->peekNC(tempNC)) priority = -tempNC->getCDTday() * 100 - tempNC->getCDThour();
			else if (tempNT->peekSC(tempSC)) priority = -tempSC->getCDTday() * 100 - tempSC->getCDThour();
			else if (tempNT->peekVC(tempVIPC)) priority = -tempVIPC->getCDTday() * 100 - tempVIPC->getCDThour();
			MovingTrucks.enqueue(tempNT, priority);
		}
	}

	if (tempST)
	{
		tempST->getMoveTime(day, hour);
		if (tempST->getAssigned() && Time.getDay() >= day && Time.getHour() >= hour)
		{
			tempST->setAssigned(false);
			LoadingST.deletebeg(tempST);
			int priority = 0;
			if (tempST->peekNC(tempNC)) priority = -tempNC->getCDTday() * 100 - tempNC->getCDThour();
			else if (tempST->peekSC(tempSC)) priority = -tempSC->getCDTday() * 100 - tempSC->getCDThour();
			else if (tempST->peekVC(tempVIPC)) priority = -tempVIPC->getCDTday() * 100 - tempVIPC->getCDThour();
			MovingTrucks.enqueue(tempST, priority);
		}
	}
}

void company::MovingAction()
{
	truck* temp;
	bool flag = MovingTrucks.peek(temp), anyDelivered = false;
	Normalcargos* tempNC = nullptr; Specialcargos* tempSC = nullptr; VIPcargos* tempVIPC = nullptr;
	if (flag && temp->peekNC(tempNC))
	{
		if (tempNC->getCDTday() <= Time.getDay() && tempNC->getCDThour() <= Time.getHour())
		{
			temp->getNC(tempNC);
			DeliverdCargos.enqueue(tempNC);
			anyDelivered = true;
		}
	}
	else if (flag && temp->peekSC(tempSC))
	{
		if (tempSC->getCDTday() <= Time.getDay() && tempSC->getCDThour() <= Time.getHour())
		{
			temp->getSC(tempSC);
			DeliverdCargos.enqueue(tempSC);
			anyDelivered = true;
		}
	}
	else if (flag && temp->peekVC(tempVIPC))
	{
		if (tempVIPC->getCDTday() <= Time.getDay() && tempVIPC->getCDThour() <= Time.getHour())
		{
			temp->getVC(tempVIPC);
			DeliverdCargos.enqueue(tempVIPC);
			anyDelivered = true;
		}
	}
	// here to sort the moving trucks again if any cargo has been deliverd 
	if (anyDelivered)
	{

		PriorityQueue<truck*, int> tempMoving;
		int x;
		while (MovingTrucks.getSize())
		{
			MovingTrucks.dequeue(temp, x);
			int priority = 0;
			if (temp->peekNC(tempNC)) priority = -tempNC->getCDTday() * 100 - tempNC->getCDThour();
			else if (temp->peekSC(tempSC)) priority = -tempSC->getCDTday() * 100 - tempSC->getCDThour();
			else if (temp->peekVC(tempVIPC)) priority = -tempVIPC->getCDTday() * 100 - tempVIPC->getCDThour();
			tempMoving.enqueue(temp, priority);
		}
		while (tempMoving.getSize())
		{
			tempMoving.dequeue(temp, x);
			MovingTrucks.enqueue(temp, x);
		}
	}

	//to enqueue in queue based on return time
	if (flag && !temp->peekVC(tempVIPC) && !temp->peekSC(tempSC) && !temp->peekNC(tempNC))
	{
		int x;
		MovingTrucks.dequeue(temp, x);
		int returnDay, returnHour; temp->getReturnTime(returnDay, returnHour);
		x = -returnDay * 100 - returnHour;
		returnTrucks.enqueue(temp, x);
	}

	//to check up or return to available trucks

	if(returnTrucks.peek(temp))
	{
		int returnDay, returnHour, x;
		temp->getReturnTime(returnDay, returnHour);
		if (Time.getDay() >= returnDay && Time.getHour() >= returnHour)
		{

			int x;
			returnTrucks.dequeue(temp, x);
			temp->incJourneyCnt();
			NormalTruck* tempNT = dynamic_cast<NormalTruck*>(temp);
			SpecialTruck* tempST = dynamic_cast<SpecialTruck*>(temp);
			VIPTruck* tempVT = dynamic_cast<VIPTruck*>(temp);
			if (temp->getJourenyCnt() == temp->getNoJoureny())
			{
				if (tempNT) Check_UpNormal.enqueue(tempNT);
				else if (tempST) Check_UpSpecial.enqueue(tempST);
				else Check_UpVIP.enqueue(tempVT);
			}
			else
			{
				if (tempNT) avlbl_N.enqueue(tempNT);
				else if (tempST) avlbl_S.enqueue(tempST);
				else avlbl_VIP.enqueue(tempVT);
			}
		}

	}


}

void company::CheckUpAction()
{
	NormalTruck* tempNT; SpecialTruck* tempST; VIPTruck* tempVT;
	if (Check_UpNormal.getSize())
	{
		Check_UpNormal.peek(tempNT);
		if (tempNT->getCheckUpCnt() >= mainTimeNormal)
		{
			Check_UpNormal.dequeue(tempNT);
			avlbl_N.enqueue(tempNT);
		}
		tempNT->IncCheckUpCnt();
	}
	if (Check_UpSpecial.getSize())
	{
		Check_UpSpecial.peek(tempST);
		if (tempST->getCheckUpCnt() >= mainTimeSpecial)
		{
			Check_UpSpecial.dequeue(tempST);
			avlbl_S.enqueue(tempST);
		}
		tempST->IncCheckUpCnt();
	}
	if (Check_UpVIP.getSize())
	{
		Check_UpVIP.peek(tempVT);
		if (tempVT->getCheckUpCnt() >= mainTimeVIP)
		{
			Check_UpVIP.dequeue(tempVT);
			tempVT->setCheckUpCnt(0);
			avlbl_VIP.enqueue(tempVT);
		}
		tempVT->IncCheckUpCnt();
	}
}
int company::getAvlTrucksSize(){
	return avlbl_N.getSize() + avlbl_S.getSize() + avlbl_VIP.getSize();
}

int company::getMovingTruckSize()
{
	return MovingTrucks.getSize();
}

int company::MovingCargosSize()
{
	PriorityQueue<truck*, int> tempq;
	truck* tempTruck = nullptr;
	int x, sz = 0;
	while (MovingTrucks.getSize())
	{
		MovingTrucks.dequeue(tempTruck, x);
		sz += tempTruck->getCargosSize();
		tempq.enqueue(tempTruck, x);
	}
	while (tempq.getSize())
	{
		tempq.dequeue(tempTruck, x);
		MovingTrucks.enqueue(tempTruck, x);
	}

	return sz;
}


int company::DeliveredCargosFullsize() {
	return DeliverdCargos.getSize();
}
int company::IncheckUpTrucksSize(){
	return Check_UpNormal.getSize() + Check_UpSpecial.getSize() + Check_UpVIP.getSize();
}

void company::pushMovingTruck(truck*& temp, int& cost)
{
	MovingTrucks.enqueue(temp, cost);
}

void company::getMovingTruck(truck*& temp, int &cost)
{
	MovingTrucks.dequeue(temp, cost);
}

void company::peekMovingTruck(truck* &temp, int& cost)
{
	MovingTrucks.dequeue(temp, cost);
	MovingTrucks.enqueue(temp, cost);
}

company::~company()
{
	delete uptr;
	while (!avlbl_N.isEmpty()){
		NormalTruck*a;
		avlbl_N.dequeue(a);
		delete a;
	}
	while (!avlbl_VIP.isEmpty()){
		VIPTruck*a;
		avlbl_VIP.dequeue(a);
		delete a;
	}
	while (!avlbl_S.isEmpty()){
		SpecialTruck*a;
		avlbl_S.dequeue(a);
		delete a;
	}
	while (!DeliverdCargos.isEmpty()){
		Cargos*a;
		DeliverdCargos.dequeue(a);
		delete a;
	}
	for (int i = 0; i < Eventcounter; i++)
	{
		delete Events[i];
	}
	for (int i = 0; i < AutoProSize; i++)
	{
		delete autoPro[i];
	}
}
