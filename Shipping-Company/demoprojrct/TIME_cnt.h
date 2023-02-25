#pragma once
class TIME_cnt
{
private:
	int hours;
	int days;
public:
	TIME_cnt();
	TIME_cnt(int d = 0, int h = 0);
	void setHour(int h);
	void setDay(int d);
	int getHour() const;
	int getDay() const;
};

