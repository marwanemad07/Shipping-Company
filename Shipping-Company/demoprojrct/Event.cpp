#include "Event.h"
Event::Event():ET(0, 0)
{
}
Event::Event(int id, int day,int hour):ET(day,hour) {
	ID = id;
}

int Event::getID() const
{
	return ID;
}
void Event::SetDay(int d){
	ET.setDay(d);
}
void Event::SetHour(int h){
	ET.setHour(h);
}
TIME_cnt Event::getTime(){
	return ET;
}
int Event::getDay() const
{
	return ET.getDay();
}
int Event::getHour() const
{
	return ET.getHour();
}
Event::~Event() {

}
