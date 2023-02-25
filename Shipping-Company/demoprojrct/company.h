#pragma once
#include"truck.h"
#include "VIPcargos.h"
#include"LinkedList.h"
#include "Normalcargos.h"
#include "Specialcargos.h"
#include "NormalTruck.h"
#include<iostream>
#include "SpecialTruck.h"
#include "VIPTruck.h"
#include "Queue.h"
#include "PriorityQueue.h"
#include <string>
#include <fstream>
#include"NormalTruck.h"
#include"Event.h"
#include"time.h"
#include "TIME_cnt.h"
#include"LinkedList.h"
class UI;
class Promotion;
using namespace std;
class company
{
private:
	int CargoCTR;
	TIME_cnt Time;
	TIME_cnt IntialTime;

	int NormalCap;
	int SpecialCap;
	int VipCap;
	int mainTimeNormal;
	int mainTimeSpecial;
	int mainTimeVIP;
	int NormalSize; // No of normal trucks
	int SpecialSize; // No of special trucks
	int VipSize; //No of vip trucks
	
	int TruckActTime;

	int MaxW;
	int AutoP;
	Event** Events;
	int Eventcounter;
	int no_events;
	ifstream in;
	ofstream out;
	UI* uptr;
	void calc_time(int&, int&, string);
	Promotion* autoPro[100];
	int AutoProSize;
	LinkedList<Normalcargos*> waitingNC;			//Waiting NormalCargos
	PriorityQueue<VIPcargos*, int> waitingVC;  //Waiting VIPCargos
	Queue<Specialcargos*> waitingSC;			//Waiting SpecialCargos


	Queue<VIPcargos*> MovingVC;
	Queue<Normalcargos*> MovingNC;
	Queue<Specialcargos*> MovingSC;


	Queue<Cargos*> DeliverdCargos;

	Queue<NormalTruck*> avlbl_N; // normal truck available
	Queue<SpecialTruck*> avlbl_S; //special truck available
	Queue<VIPTruck*> avlbl_VIP; //  VIP truck available


	Queue<NormalTruck*> Check_UpNormal; // normal truck available
	Queue<SpecialTruck*> Check_UpSpecial; //special truck available
	Queue<VIPTruck*> Check_UpVIP; //  VIP truck available

	/*Queue<NormalTruck*> LoadingNT;
	Queue<SpecialTruck*> LoadingST;
	Queue<VIPTruck*> LoadingVT;*/

	LinkedList<NormalTruck*> LoadingNT;
	LinkedList<SpecialTruck*> LoadingST;
	LinkedList<VIPTruck*> LoadingVT;

	PriorityQueue<truck*, int>MovingTrucks;
	PriorityQueue<truck*, int> returnTrucks;

public:
	company(int day, int hour);
	PriorityQueue<VIPcargos*, int>* GetwaitingVC();
	LinkedList<Normalcargos*>* GetwaitingNC();
	Queue<Specialcargos*>* GetwaitingSC();

	Queue<VIPcargos*>* GetMovingVC();
	Queue<Normalcargos*>* GetMovingNC();
	Queue<Specialcargos*>* GetMovingSC();

	Queue<Normalcargos*>* getDeliveredNC();
	Queue<Specialcargos*>* getDeliveredSC();
	Queue<VIPcargos*>* getDeliveredVC();

	Queue<NormalTruck*>*getavlbl_N();
	Queue<SpecialTruck*>* getavlbl_S();
	Queue<VIPTruck*>* getavlbl_VIP();

	PriorityQueue<truck*, int>* getMovingTrucks();
	PriorityQueue<truck*, int>* getreturnTrucks();

	LinkedList<NormalTruck*>* getLoadingNT();
	LinkedList<SpecialTruck*>* getLoadingST();
	LinkedList<VIPTruck*>* getLoadingVT();

	Queue<NormalTruck*>* getCheck_UpNormal();
	Queue<SpecialTruck*> *getCheck_UpSpecial();
	Queue<VIPTruck*> *getCheck_UpVIP();

	Queue<Cargos*>*getDeliverdCargos();

	int getEventcounter();
	int WaitingCargosFullsize();
	int getno_events();
	UI* getUi();
	void simulator();
	int getPromtionLimit();
	TIME_cnt getTime();
	void setTime(TIME_cnt);
	void incrementTime();
	Event** getEvents();
	void loading(string FileName);
	void Waiting_VIP_push(VIPcargos* vipCargo);
	void AssignCargos();
	void LoadingCargos();
	void MovingAction();
	bool WorkingHours();
	void CheckUpAction();
	void ExecuteEvent();
	int getLoadingTrucksSize();
	int DeliveredCargosFullsize();
	int getAvlTrucksSize();
	int getMovingTruckSize();
	int MovingCargosSize();
	int IncheckUpTrucksSize();
	void pushMovingTruck(truck*& temp, int &cost);
	void getMovingTruck(truck*& temp, int& cost);
	void peekMovingTruck(truck*& temp, int &cost);
	int getAutoProSize();
	TIME_cnt getIntialTime();
	int getActTime();
	int getRetrunTruckssize();
	~company();
};