#include "stdafx.h"
#include "BloodOrder.h"
#include <fstream>
using namespace std;


char BloodOrder::getBloodType()
{
	return type;
}

void BloodOrder::execute()
{
	if (type)
	{
		for (int i = 0; i < 25; i++)
		{
			bloodBank->add_blood_unitB(new BloodUnit(300));
		}
		bloodBank->setNonEmergencyFlagB(false);
	}
	else
	{
		for (int i = 0; i < 25; i++)
		{
			bloodBank->add_blood_unit(new BloodUnit(300));
		}
		bloodBank->setNonEmergencyFlag(false);
	}
}

BloodOrder::BloodOrder(BloodBank* _bloodBank,bool _type)
{
	setTimetoExecution(roll_time());
	bloodBank = _bloodBank;
	setType(0);
	type = _type;
	if(type)
		bloodBank->setNonEmergencyFlagB(true);
	else 
		bloodBank->setNonEmergencyFlag(true);
	//For debugging
	//ofstream myfile;
	//myfile.open("TimesBetweenNonEmergencyOrders.txt", ios_base::app);
	//myfile << getTimeToExecution()<<endl;
	//myfile.close();
}


BloodOrder::~BloodOrder()
{
	//bloodBank->setNonEmergencyFlag(false);
}

int roll_time()
{
	static double a= 0.175555987;//This is the seed
	a = a * 79 - (int)(a * 79);
	return round(-1700 * log(a));
}

