#include<iostream>
#include "company.h"
#include"Preparation.h"
#include"UI.h"
#include"truck.h"
#include "PriorityQueue.h"
#include "PQNode.h"
#include<fstream>
using namespace std;
int main(){
	company* c=new company(1,5);
	c->simulator();
	delete c;
	return 0;
}