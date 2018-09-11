#include "stdafx.h"
#include "BloodBank.h"
#include <algorithm>
#include <iostream>
#include"UtilizeBlood.h"
#include "vector"

void BloodBank::ageBloodBy(int time)
{
	for (BloodUnit* element : BloodPool)
	{
		element->ageBy(time);
	}
	for (BloodUnit* element : BloodPoolB)
	{
		element->ageBy(time);
	}
}

void BloodBank::utilizeOldBlood()
{
	for (unsigned int i = 0; i < BloodPool.size(); i++)
	{
		if (BloodPool[i]->getTimeToGoingBad() < 1)
		{
			BloodUnit* bunit = BloodPool.back();
			BloodPool.pop_back();

			if (BloodPool.size() > 0 && i < BloodPool.size())
			{
				BloodPool[i] = bunit;
				i--;
			}
			
			bloodUnitsWasted++;
		}
	}
	for (unsigned int i = 0; i < BloodPoolB.size(); i++)
	{
		if (BloodPoolB[i]->getTimeToGoingBad() < 1)
		{
			BloodUnit* bunit = BloodPoolB.back();
			BloodPoolB.pop_back();

			if (BloodPoolB.size() > 0 && i < BloodPoolB.size())
			{
				BloodPoolB[i] = bunit;
				i--;
			}
			
			bloodUnitsWasted++;
		}
	}
}

int BloodBank::getBloodUnitsWasted()
{
	return bloodUnitsWasted;
}

int BloodBank::getBloodUnitsUsed()
{
	return bloodUnitsUsed;
}

bool BloodBank::isOlder(const BloodUnit* a, const BloodUnit* b)
{
	return a->getTimeToGoingBad()>b->getTimeToGoingBad();
}

void BloodBank::incBloodUnitsUsed(int n)
{
	bloodUnitsUsed +=n;
}





bool BloodBank::getEmergencyFlag()
{
	return emergencyOrderFlag;
}
bool BloodBank::getEmergencyFlagB()
{
	return emergencyOrderFlagB;
}
bool BloodBank::getNonEmergencyFlag()
{
	return nonEmergencyFlag;
}
bool BloodBank::getNonEmergencyFlagB()
{
	return nonEmergencyFlagB;
}

void BloodBank::setNonEmergencyFlag(bool a)
{
	nonEmergencyFlag = a;
}

void BloodBank::setEmergencyFlag(bool a)
{
	emergencyOrderFlag = a;
}
void BloodBank::setNonEmergencyFlagB(bool a)
{
	nonEmergencyFlagB = a;
}

void BloodBank::setEmergencyFlagB(bool a)
{
	emergencyOrderFlagB = a;
}
int BloodBank::get_blood_bank_size()
{
	return BloodPool.size();
}
int BloodBank::get_blood_bank_sizeB()
{
	return BloodPoolB.size();
}
void BloodBank::add_blood_unit(BloodUnit* bunit)
{
	BloodPool.push_back(bunit);
	calendar->addEvent(new UtilizeBlood(bunit->getTimeToGoingBad(), this));
}
void BloodBank::add_blood_unitB(BloodUnit* bunit)
{
	BloodPoolB.push_back(bunit);
	calendar->addEvent(new UtilizeBlood(bunit->getTimeToGoingBad(), this));
}
void BloodBank::sortBlood()
{
	std::sort(BloodPool.begin(), BloodPool.end(), isOlder);
	std::sort(BloodPoolB.begin(), BloodPoolB.end(), isOlder);
}

int BloodBank::showTopId()
{
	int id=0;
	if (BloodPool.size() == 0)
		return -1;
	for (int i = 0; i < BloodPool.size(); i++)
	{
		if (BloodPool[i]->getId() > id)
			id = BloodPool[i]->getId();
	}
	return id;
}

void BloodBank::showBloodBankByAge()
{
	std::cout << "Current resources:" << std::endl;
	std::cout << "	Type A:";
	if (BloodPool.size() == 0)
		std::cout << "Empty";
	for (BloodUnit* o : BloodPool)
	{
		std::cout << o->getTimeToGoingBad() << " ";
	}
	std::cout << std::endl;
	std::cout << "	Type B:";
	if (BloodPoolB.size() == 0)
		std::cout << "Empty";
	for (BloodUnit* o : BloodPoolB)
	{
		std::cout << o->getTimeToGoingBad() << " ";
	}
	std::cout << std::endl;
}


bool BloodBank::DoWeHaveXBloodUnits(int X)
{
	if (BloodPool.size() >= X)
		return true;
	else
		return false;
}
bool BloodBank::DoWeHaveXBloodUnitsB(int X)
{
	if (BloodPoolB.size() >= X)
		return true;
	else
		return false;
}
void BloodBank::popBloodUnit(int numberOfBloodUnits)
{
	BloodUnit *temp;
	std::vector <int> utilizationEventsToGetRidOf;
	bool flag = 0;
	bool flag2 = 0;
	
	sortBlood();
	for (int i = 0; i < numberOfBloodUnits; i++) {
		temp = BloodPool.back();
		flag = 0;
		for (unsigned int i = 0; i < utilizationEventsToGetRidOf.size(); i++)
		{
			if (utilizationEventsToGetRidOf[i] == temp->getTimeToGoingBad())
				flag = 1;//means that there already is a utilization event of that time set for deletion
		}
		flag2 = 0;
		for (int i = 0; i < BloodPool.size() - 1; i++)//goes through all bloodunits exept for the last which we compare with
		{
			if (temp->getTimeToGoingBad() == BloodPool[i]->getTimeToGoingBad())
				flag2 = 1;//means that there is more blood units with same time to expiration so dont delete its utilization event
		}
		if (!flag && !flag2)
			utilizationEventsToGetRidOf.push_back(temp->getTimeToGoingBad());


		BloodPool.pop_back();
		bloodUnitsUsed++;
	}

	for (int i = 0; i < utilizationEventsToGetRidOf.size(); i++)
	{
		calendar->getRidOfUtilizationsWithTimeN(utilizationEventsToGetRidOf[i]);
	}
}
void BloodBank::popBloodUnitB(int numberOfBloodUnits)
{
	BloodUnit *temp;
	std::vector <int> utilizationEventsToGetRidOf;
	bool flag = 0;
	bool flag2 = 0;

	sortBlood();
	for (int i = 0; i < numberOfBloodUnits; i++) {
		temp = BloodPoolB.back();
		flag = 0;
		for (unsigned int i = 0; i < utilizationEventsToGetRidOf.size(); i++)
		{
			if (utilizationEventsToGetRidOf[i] == temp->getTimeToGoingBad())
				flag = 1;//means that there already is a utilization event of that time set for deletion
		}
		flag2 = 0;
		for (int i = 0; i < BloodPoolB.size() - 1; i++)//goes through all bloodunits exept for the last which we compare with
		{
			if (temp->getTimeToGoingBad() == BloodPoolB[i]->getTimeToGoingBad())
				flag2 = 1;//means that there is more blood units with same time to expiration so dont delete its utilization event
		}
		if (!flag && !flag2)
			utilizationEventsToGetRidOf.push_back(temp->getTimeToGoingBad());


		BloodPoolB.pop_back();
		bloodUnitsUsed++;
	}

	for (int i = 0; i < utilizationEventsToGetRidOf.size(); i++)
	{
		calendar->getRidOfUtilizationsWithTimeN(utilizationEventsToGetRidOf[i]);
	}
}

BloodBank::BloodBank(Calendar* _calendar)
{
	calendar = _calendar;
	bloodUnitsWasted = 0;
	bloodUnitsUsed = 0;
	
	nonEmergencyFlag = false;
	emergencyOrderFlag = false;
	nonEmergencyFlagB = false;
	emergencyOrderFlagB = false;
	
}


BloodBank::~BloodBank()
{
}
int roll_research()
{
	static double a = 0.123578;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return round(a * 5) + 5;
}