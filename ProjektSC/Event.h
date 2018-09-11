#pragma once
#include<string.h>

class BloodDonationPoint;

class Event
{
	int timeToExecution;
	int type;		//For extracting the type of event
public:
	virtual void execute() = 0;
	int getTimeToExecution();
	void setTimetoExecution(int t);
	void passTime(int time);
	void setType(int a);
	int getType();
	Event();
	~Event();
};

