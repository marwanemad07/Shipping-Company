#include "UI.h"
#include"Preparation.h"
#include "Promotion.h"
#include"Cancellation.h"
#include "windows.h"
#include <conio.h>
#include "LinkedList.h"
UI::UI(company*a) :Ttime(0, 0){
	comp = a;
	flag = false;
	flagc = true;
}
void UI::printTrucksQueue(Queue<VIPcargos*>*vt, Queue<Normalcargos*>*nt, Queue<Specialcargos*>*st, char type){
	Normalcargos*TN; //temp normal cargo 
	VIPcargos*TV;//temp vip cargo 
	Specialcargos *TS; //temp special cargo 
	int size = nt->getSize();
	while (size--){
		nt->dequeue(TN);
		if (type != 'n')cout << ",[";
		cout << TN->getmainID();
		if (type != 'n')cout << "]";
		if (nt->getSize() != 0) cout << ",";
		nt->enqueue(TN);
	}
	size = vt->getSize();
	while (size--){
		vt->dequeue(TV);
		if (type != 'v')cout << ",{";
		cout << TV->getmainID();
		if (type != 'v')cout << "}";
		if (vt->getSize() != 0) cout << ",";
		vt->enqueue(TV);
	}
	size = st->getSize();
	while (!st->isEmpty()){
		st->dequeue(TS);
		if (type != 's')cout << ",(";
		cout << TS->getmainID();
		if (type != 's')cout << ")";
		if (st->getSize() != 0) cout << ",";
		st->enqueue(TS);
	}
}
void UI::printDeliveredCargos(Queue<Cargos*>*del)
{
	int sz = del->getSize();
	while (sz--){
		Cargos*T;
		del->dequeue(T);
		if (T == NULL)return;
		Normalcargos*TN = dynamic_cast<Normalcargos*>(T);
		VIPcargos*TV = dynamic_cast<VIPcargos*>(T);
		Specialcargos *TS = dynamic_cast<Specialcargos*>(T);
		if (TN){
			cout << "[" << TN->getmainID() << "] ";
		}
		else if (TV){
			cout << "{" << TV->getmainID() << "} ";
		}
		else{
			cout << "(" << TS->getmainID() << ") ";
		}
		del->enqueue(T);
	}
	cout << endl;
}

void UI::printLoadingTrucks(LinkedList<NormalTruck*>*NT, LinkedList<SpecialTruck*>*ST, LinkedList<VIPTruck*>* VT)//change
{
	Node<NormalTruck*>*NTK= NT->getHead();
	Node<SpecialTruck*>*STK = ST->getHead();
	Node<VIPTruck*>*VTK= VT->getHead();

	while (NTK)
	{
		
		cout << "[" << NTK->getItem()->getID() << "][";
		printTrucksPrQueue(NTK->getItem()->getVC(), NTK->getItem()->getNC(), NTK->getItem()->getSC(), 'n');
		cout << "] ";
		NTK = NTK->getNext();
	}
	while (STK)
	{
	
		cout << "(" << STK->getItem()->getID() << ")(";
		printTrucksPrQueue(STK->getItem()->getVC(), STK->getItem()->getNC(), STK->getItem()->getSC(), 'S');
		cout << ") ";
		STK = STK->getNext();
	}
	while (VTK)
	{
	
		cout << "{" << VTK->getItem()->getID() << "}{";
		printTrucksPrQueue(VTK->getItem()->getVC(), VTK->getItem()->getNC(), VTK->getItem()->getSC(), 'V');
		cout << "} ";
		VTK = VTK->getNext();
	}
	cout << endl;
}

void UI::printEmptyTrucks(Queue<NormalTruck*>*NTK, Queue<SpecialTruck*>*STK, Queue<VIPTruck*>*VTK){
	int size = NTK->getSize();
	int sz = size;
	while (sz--)
	{
		NormalTruck*NrmlTrk;
		NTK->dequeue(NrmlTrk);
		cout << "[" << NrmlTrk->getID() << "]";
		NTK->enqueue(NrmlTrk);
	}
	if (size)
	cout << ",";
	size = STK->getSize();
	sz = size;
	while (sz--)
	{
		SpecialTruck*Spcltrk;
		STK->dequeue(Spcltrk);
		cout << "(" << Spcltrk->getID() << ")";
		STK->enqueue(Spcltrk);
	}
	sz = VTK->getSize();
	if (size&&sz)
	cout << ",";
	while (sz--)
	{
		VIPTruck*vptrk;
		VTK->dequeue(vptrk);
		cout << "{" << vptrk->getID() << "}";
		VTK->enqueue(vptrk);
	}
	cout << endl;
}

void UI::printTrucksPrQueue(PriorityQueue<VIPcargos*, int>*vt, PriorityQueue<Normalcargos*, int>*nt, PriorityQueue<Specialcargos*, int>*st, char type){
	Normalcargos*TN; //temp normal cargo 
	VIPcargos*TV;//temp vip cargo 
	Specialcargos *TS; //temp special cargo 
	PriorityQueue<VIPcargos*, int>vtt;
	PriorityQueue<Normalcargos*, int>ntt;
	PriorityQueue<Specialcargos*, int>stt;
	int t;
	while (!nt->isEmpty()){
		nt->dequeue(TN, t);
		if (type != 'n')cout << "[";
		cout << TN->getmainID();
		if (type != 'n')cout << "]";
		if (nt->getSize() != 0) cout << ",";
		ntt.enqueue(TN, t);
	}
	while (!ntt.isEmpty())
	{
		ntt.dequeue(TN, t);
		nt->enqueue(TN, t);
	}
	while (!vt->isEmpty()){
		vt->dequeue(TV, t);
		if (type != 'v')cout << "{";
		cout << TV->getmainID();
		if (type != 'v')cout << "}";
		if (vt->getSize() != 0) cout << ",";
		vtt.enqueue(TV, t);
	}
	while (!vtt.isEmpty()){
		vtt.dequeue(TV, t);
		vt->enqueue(TV, t);
	}
	while (!st->isEmpty()){
		st->dequeue(TS, t);
		if (type != 's')cout << "(";
		cout << TS->getmainID();
		if (type != 's')cout << ")";
		if (st->getSize() != 0) cout << ",";
		stt.enqueue(TS, t);
	}
	while (!stt.isEmpty()){
		stt.dequeue(TS, t);
		st->enqueue(TS, t);
	}
}
void UI:: PrintReturnTrucks(){
	int sz=comp->getreturnTrucks()->getSize();
	PriorityQueue<truck*, int>Temp;
	while (sz--){
		truck*truck;
		int x;
		comp->getreturnTrucks()->dequeue(truck,x);
		cout << truck->getID()<<" ";
		Temp.enqueue(truck, x);
	}
	 sz = Temp.getSize();
	while (sz--){
		truck*truck;
		int x;
		Temp.dequeue(truck, x);
		comp->getreturnTrucks()->enqueue(truck, x);
	}
	cout << endl;
}

void centerstring(string s)
{
	int l = s.length();
	int pos = (int)((100 - l) / 2);
	for (int i = 0; i<pos; i++)
		cout << " ";
	cout << s << endl;
}

void UI::PrintWaitingCargos(){
	Normalcargos*TN; //temp normal cargo 
	VIPcargos*TV;//temp vip cargo 
	Specialcargos *TS; //temp special cargo 
	PriorityQueue<VIPcargos*, int> TempwaitingVC;  //Waiting VIPCargos
	int t;   // for reading Priority
	//print normal
	Node<Normalcargos*>* temp = comp->GetwaitingNC()->getHead();
	if (temp){
		cout << "[";
		while (temp)
		{
			cout << temp->getItem()->getmainID();
			if (temp->getNext()) cout << ",";
			temp = temp->getNext();
		}
		cout << "] ";
	}
	//print special
	int size = comp->GetwaitingSC()->getSize();
	if (size){
		cout << "(";
		while (size--){
			comp->GetwaitingSC()->dequeue(TS);
			cout << TS->getmainID();
			if (size != 0) cout << ",";
			comp->GetwaitingSC()->enqueue(TS);
		}
		cout << ") ";
	}
	//print vip
	TV = nullptr;
	comp->GetwaitingVC()->peek(TV);
	if (TV)
	{
		cout << "{";

		while (!comp->GetwaitingVC()->isEmpty())
		{
			comp->GetwaitingVC()->dequeue(TV, t);
			cout << TV->getmainID();
			if (comp->GetwaitingVC()->getSize() != 0) cout << ",";
			TempwaitingVC.enqueue(TV, t);
		}
		while (!TempwaitingVC.isEmpty()){
			TempwaitingVC.dequeue(TV, t);
			comp->GetwaitingVC()->enqueue(TV, t);
		}
		cout << "} ";
	}
	cout << endl;
}

void UI::PrintMovingCargos()
{
	PriorityQueue<truck*, int> movingTrucksTemp;
	truck* temp;
	int cost;
	Normalcargos* NC; Specialcargos* SC; VIPcargos* VIPC;
	int sz = comp->getMovingTruckSize();
	while (sz--&&comp->MovingCargosSize())
	{
		comp->getMovingTruck(temp, cost);
		movingTrucksTemp.enqueue(temp, cost);
		if (temp->peekNC(NC) || temp->peekSC(SC)||temp->peekVC(VIPC))
		cout << temp->getID();
		char c = 'n';
		if (temp->peekNC(NC))
		{ 
			c = 'n'; 
			if (temp->getVC()->getSize() || temp->getNC()->getSize() || temp->getSC()->getSize())
			{
				cout << " [";
				printTrucksPrQueue(temp->getVC(), temp->getNC(), temp->getSC(), c);
				cout << "] ";
			}
		}
		else if (temp->peekSC(SC))
		{
			c = 's'; 
			if (temp->getVC()->getSize() || temp->getNC()->getSize() || temp->getSC()->getSize()){
				cout << " (";
				printTrucksPrQueue(temp->getVC(), temp->getNC(), temp->getSC(), c);
				cout << ") ";
			}
		}
		else {
			c = 'v';
			if (temp->getVC()->getSize() || temp->getNC()->getSize() || temp->getSC()->getSize())
			{
				cout << " {";
				printTrucksPrQueue(temp->getVC(), temp->getNC(), temp->getSC(), c);
				cout << "} ";
			}
		}
	}
	while (movingTrucksTemp.getSize())
	{
		movingTrucksTemp.dequeue(temp, cost);
		comp->pushMovingTruck(temp, cost);
	}
	cout << endl;
}

void UI::print()
{
	centerstring("Current Time(Day:Hour):"+to_string(comp->getTime().getDay())+ ":"+ to_string( comp->getTime().getHour()));
	centerstring("**--------------------------**");
	cout << "  " << comp->WaitingCargosFullsize() << " Waiting Cargos : ";
	PrintWaitingCargos();
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "  " << comp->getLoadingTrucksSize() << " Loading Trucks : ";
	printLoadingTrucks(comp->getLoadingNT(), comp->getLoadingST(), comp->getLoadingVT());
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "  " << comp->getRetrunTruckssize() << " Return Trucks : ";
	PrintReturnTrucks();
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "  " << comp->getAvlTrucksSize() << " Empty Trucks : ";
	printEmptyTrucks(comp->getavlbl_N(), comp->getavlbl_S(), comp->getavlbl_VIP());
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "  " << comp->MovingCargosSize() << " Moving Cargos : ";
	PrintMovingCargos();
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "  " << comp->IncheckUpTrucksSize() << " In-Checkup Trucks : ";
	printEmptyTrucks(comp->getCheck_UpNormal(), comp->getCheck_UpSpecial(), comp->getCheck_UpVIP());
	cout << "------------------------------------------------------------------------------" << endl;
	cout << "  "<<comp->DeliveredCargosFullsize() << " Delivered Cargos : ";
	printDeliveredCargos(comp->getDeliverdCargos());
	cout << "------------------------------------------------------------------------------" << endl;

}

void UI::Interactive_Mode()
{
	if (_getch() == '\r')
	{
		if (comp->WorkingHours()){
			print();
		cout << "\n";
			}
		else{
			centerstring("");
			 centerstring( " * Sorry But we are not Working -  - come from (5:00 to 23:00) - *");
			 centerstring(" _______________________________________________________________");
		}	
	}
}

void UI::StepByStep()
{
	if (comp->WorkingHours()){
		print();
		cout << "\n";
	}
	else{
		centerstring("");
		centerstring(" * Sorry But we are not Working -  - come from (5:00 to 23:00) - *");
		centerstring(" _______________________________________________________________");
	}
	Sleep(900);
}

void UI::Silent(){
	if (flagc){
		cout << "Simulation Starts";
		cout << ".";
		Sleep(500);
		cout << ".";
		Sleep(500);
		cout << "." << endl;
		flagc = false;
	}
}
void UI::UiModes(char t)
{
	switch (t)
	{
	case 'S': 
		if (!flag)
		{ 
			cout << "Welcome to Step by step mode " << endl; 
			flag = true; 
		}
		Sleep(300);
		StepByStep(); 
		break;
	case'I': 
		if (!flag){
			cout << "Welcome to interactive mode all You have to is pressing enter " << endl << endl;
					flag = true;
	}	
		Sleep(300); Interactive_Mode(); break;
	case'C':
		if (!flag){
			cout << "Welcome to Silent mode " << endl;
			flag = true;
		}
		Silent(); break;
	default:
		break;
	}
}
void avgwaiting(int&d, int&h,int t){
	d = (t - t % 24) / 24;
	h = t % 24;
}
void UI::CreatFile(){
	centerstring("*****************************************");
	centerstring("- Enter Output fileName -");
	centerstring("*****************************************");
	string name;
	cin >> name;
	out.open(name + ".txt");
	out << "CDT  ID  PT    WT   TID \n";
	int sz = comp->getDeliverdCargos()->getSize();
	int CargosSize = sz;
	int NCounter = 0, SCounter = 0, VCounter = 0;
	int h = 0, d = 0;
	while (sz--)
	{
			Cargos*T;
			comp->getDeliverdCargos()->dequeue(T);
			Normalcargos*TN = dynamic_cast<Normalcargos*>(T);
			VIPcargos*TV = dynamic_cast<VIPcargos*>(T);
			Specialcargos *TS = dynamic_cast<Specialcargos*>(T);
			if (TN){
				NCounter++;
			}
			else if (TV){
				VCounter++;
			}
			else{
				SCounter++;
			}
			out << T->getCDTday() << ":" << T->getCDThour();
			if (T->getCDThour() <= 9) out << "  ";
			else{ out << " "; } 
			out << T->getmainID() << "   " << T->getPrepDay() << ":" << T->getPrepHour();
			if (T->getPrepHour() <= 9) out << "   ";
			else{ out << "  "; }
			out << T->getWTDay() << ":" << T->getWTHour();
			if (T->getWTHour() <= 9) out << "  ";
			else{ out << " "; } 
			out<< T->getTID() << "\n";
			h += T->getWTHour();
			d += T->getWTDay();
			comp->getDeliverdCargos()->enqueue(T);
		
	}
	
	float avg=0;
	if (CargosSize!=0)
	avg = (h + d * 24) / CargosSize;
	avgwaiting(d, h, avg);
	out << "------------------------------------------------------" << "\n";
	out << "------------------------------------------------------" << "\n";
	out << "Cargos : " << CargosSize << "[ N: " << NCounter << ", " << "S :" << SCounter << "," << " V :" << VCounter << " ] \n";
	out << "Cargo Avg Wait = " << d << ":" << h<<"\n";
	out << "Auto-promoted Cargos: " << int(float(comp->getAutoProSize() / (NCounter + comp->getAutoProSize())) * 100) << "% \n";
	out << "Trucks : " << comp->getAvlTrucksSize() << "  [ N: " << comp->getavlbl_N()->getSize() << ", " << "S :" << comp->getavlbl_S()->getSize() << "," << " V :" << comp->getavlbl_VIP()->getSize() << " ] \n";
	
	sz = comp->getavlbl_N()->getSize();
	
	h = 0;
	float tu = 0.0;
	int totsum = float(abs(comp->getTime().getHour() - comp->getIntialTime().getHour()) + (24 * (abs(comp->getTime().getDay() - comp->getIntialTime().getDay()))));
	while (sz--){
	
		NormalTruck*truck;
		comp->getavlbl_N()->dequeue(truck);
		double a = truck->getCapacity() * truck->getJourenyCnt();
		double b = truck->gettotactive()/ (double)totsum;
		if (a!=0)
		tu += (truck->getTDC() / a)*b;

		comp->getavlbl_N()->enqueue(truck);
	}
	sz = comp->getavlbl_S()->getSize();
	while (sz--){

		SpecialTruck*truck;
		comp->getavlbl_S()->dequeue(truck);
		double a = truck->getCapacity() * truck->getJourenyCnt();
		double b = truck->gettotactive() / totsum;
		if (a != 0)
		tu +=( truck->getTDC()/a)* b;

		comp->getavlbl_S()->enqueue(truck);
	}
	sz = comp->getavlbl_VIP()->getSize();
	while (sz--){

		VIPTruck*truck;
		comp->getavlbl_VIP()->dequeue(truck);
		double a = truck->getCapacity() * truck->getJourenyCnt();
		double b = truck->gettotactive() / totsum;
		if (a != 0)
		tu += (truck->getTDC() / a)*b;
	
		comp->getavlbl_VIP()->enqueue(truck);

	}
	
	avg = (float)((( (float)(comp->getActTime()) /( (float)(totsum * comp->getAvlTrucksSize()) ))) *100.0);
	out << "Avg Active Time : " << avg << "% \n";
	out << "Avg utilization : " << (float(tu) / float(comp->getAvlTrucksSize())) * 100 << "%";
	cout << " Output file created " << endl;
}
void UI::Intro(string &FileName,char&t){
	centerstring("*---------------------------------------------------*");
	centerstring("Welcome to our Shipping Company");
	centerstring("*---------------------------------------------------*");
	// PlaySound(TEXT("project.wav"), NULL, SND_SYNC);
	centerstring("Enter Input File name");
	centerstring("*__________________________*");
	cin >> FileName;
	centerstring("*---------------------------------------------------*");
	centerstring(" please choose the print mode :: ");
	centerstring("'S' (stepBystep) -- 'I' (Interactive) -- 'C'(silance)");
	cin >> t;
}
UI::~UI(){

}