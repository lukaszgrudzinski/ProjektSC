#include "stdafx.h"
#include "Calendar.h"
#include<stdio.h>
#include "iostream"

void Calendar::addEvent(Event * newEvent)
{
	if (newEvent->getType() == 4)
	{
		for (int i = 0; i < eventList.size(); i++)
		{
			if (eventList[i]->getType()==4&&eventList[i]->getTimeToExecution() == newEvent->getTimeToExecution())
				return;
		}
	}
	eventList.push_back(newEvent);
}

int Calendar::passTime()
{
	int time = eventList[0]->getTimeToExecution();
	for (Event* element : eventList)
	{
		if (element->getTimeToExecution() < time&&element->getTimeToExecution() != 0)
			time = element->getTimeToExecution();
	}
	//time = 1;
	for (Event* element : eventList)
	{
		element->passTime(time);
	}

	absoluteTime += time;
	return time;
}

int Calendar::getTimeOfNthEvent(int n)
{
	if (n > eventList.size())
		return 999;
	return eventList[n]->getTimeToExecution();
}

int Calendar::getSizeOfEventList()
{
	return eventList.size();
}

void Calendar::executeNthElement(int n)
{
	if (eventList[n]->getType() == 4)
		numberOfEmergencyOrders++;
	eventList[n]->execute();
	//eventList.erase(eventList.begin() + n);
	Event* temp = eventList.back();
	eventList.pop_back();
	if (eventList.size() > 0 && n < eventList.size())
	{
		eventList[n] = temp;
		
	}
	//Conditional Events:

}

void Calendar::showEvents()
{
	std::cout << "Events planned: " << std::endl<<"	";
	for (int i = 0; i < eventList.size(); i++)
	{
		if (i % 6 == 5)
			std::cout << std::endl << "	";
		switch (eventList[i]->getType())
		{
		case 0:
			std::cout << "Blood Order";
			break;
		case 1:
			std::cout << "Emergency Blood Order";
			break;
		case 2:
			std::cout << "New Blood Donor";
			break;
		case 3:
			std::cout << "New Patient";
			break;
		case 4:
			std::cout << "Utilize Blood";
			break;
		case 5:
			std::cout << "Awareness Campaign";
			break;
		case 6:
			std::cout << "End of Awareness Campaign";
			break;
		case 10:
			std::cout << "Send Patient home";
			break;
		default:
			break;
		}
		std::cout << "[" << eventList[i]->getTimeToExecution() << "] ";
	}
	std::cout << std::endl;
}

void Calendar::getRidOfUtilizationsWithTimeN(int N)
{
	for (int i = 0; i < eventList.size(); i++)
	{
		if (eventList[i]->getType() == 4 && eventList[i]->getTimeToExecution() == N)
		{
			Event* bunit = eventList.back();
			eventList.pop_back();

			if (eventList.size() > 0 && i < eventList.size())
			{
				eventList[i] = bunit;
				i--;
			}
		}
	}
}

void Calendar::deleteSendHome()
{
	for (int n = 0; n < getSizeOfEventList(); n++)
	{
		if (eventList[n]->getType() == 10 && eventList[n]->getTimeToExecution() == 0)
		{
			eventList[n]->execute();
			Event* temp = eventList.back();
			eventList.pop_back();
			if (eventList.size() > 0 && n < eventList.size())
			{
				eventList[n] = temp;

			}
		}
	}
}

int Calendar::getNumberOfEmergencyOrders()
{
	return numberOfEmergencyOrders;
}

int Calendar::getCurrentTime()
{
	return absoluteTime;
}

Calendar::Calendar()
{
	
	numberOfEmergencyOrders = 0;
	absoluteTime = 0;
}


Calendar::~Calendar()
{
}
