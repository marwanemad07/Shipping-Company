#pragma once
#include "company.h"
#include <string>

#include<iostream>
using namespace std;
class UI
{
private:
	
	company*comp;
	ofstream out;
	TIME_cnt Ttime;
	bool flag;
	bool flagc;
	void print();
	void printDeliveredCargos(Queue<Cargos*>*);
	void printLoadingTrucks(LinkedList<NormalTruck*>*NTK, LinkedList<SpecialTruck*>*STK, LinkedList<VIPTruck*>* VTK);
	void printTrucksPrQueue(PriorityQueue<VIPcargos*, int>*, PriorityQueue<Normalcargos*, int>*, PriorityQueue<Specialcargos*, int>*, char);
	void printTrucksQueue(Queue<VIPcargos*>*, Queue<Normalcargos*>*, Queue<Specialcargos*>*, char);
	void printEmptyTrucks(Queue<NormalTruck*>*, Queue<SpecialTruck*>*, Queue<VIPTruck*>*);
	void PrintWaitingCargos();
	void PrintReturnTrucks();
	void PrintMovingCargos();
public:
	UI(company*);
	void CreatFile();
	void  UiModes(char t);
	void Intro(string &name,char&t);
	void Interactive_Mode();
	void StepByStep();
	void Silent();
	~UI();
};

