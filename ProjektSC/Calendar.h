#pragma once
#include "Event.h"
#include<vector>

class Calendar
{
	std::vector <Event*> eventList;
	unsigned long int absoluteTime;
	int numberOfEmergencyOrders;
	int numberOfEvents[5];
public:
	void addEvent(Event* newEvent);
	int passTime();
	int getTimeOfNthEvent(int n);
	int getSizeOfEventList();
	void executeNthElement(int n);
	void showEvents();
	void getRidOfUtilizationsWithTimeN(int N);
	void deleteSendHome();
	int getNumberOfEmergencyOrders();
	int getCurrentTime();
	Calendar();
	~Calendar();
};

