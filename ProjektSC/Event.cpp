#include "stdafx.h"
#include "Event.h"


int Event::getTimeToExecution()
{
	return timeToExecution;
}

void Event::setTimetoExecution(int t)
{
	timeToExecution = t;
}

void Event::passTime(int time)
{
	if (time > timeToExecution)
		timeToExecution = 0;
	else
		timeToExecution -= time;
}

void Event::setType(int a)
{
	type = a;
}

int Event::getType()
{
	return type;
}

Event::Event() = default;


Event::~Event() = default;
