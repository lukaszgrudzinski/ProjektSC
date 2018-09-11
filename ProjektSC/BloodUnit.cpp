//A class representing a single blood unit
#include "stdafx.h"
#include "BloodUnit.h"



BloodUnit::BloodUnit(int _timeToGoingBad,bool _type)
{
	id = ID();
	 timeToGoingBad = _timeToGoingBad;//TODO: same same same
	 type = _type;
	
}


BloodUnit::~BloodUnit()
{
}

int BloodUnit::getId() const
{
	return id;
}

int BloodUnit::getTimeToGoingBad() const
{
	return timeToGoingBad;
}

void BloodUnit::ageBy(int t)
{
	timeToGoingBad -= t;
}

int ID()
{
	 static int ID = 0;
	 return ID++;
}
int roll_type()
{
	static double a = 0.175555987;//This is the seed
	a = a * 79 - (int)(a * 79);
	return a>0.6;
}