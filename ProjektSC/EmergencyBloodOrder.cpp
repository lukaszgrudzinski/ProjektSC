#include "stdafx.h"
#include "EmergencyBloodOrder.h"
#include <fstream>
using namespace std;

EmergencyBloodOrder::EmergencyBloodOrder(BloodBank* blood_bank,bool _bloodType)
{
	setTimetoExecution(roll_emergency());
	setType(1);
	bloodBank = blood_bank;
	type = _bloodType;
	if(type)
		bloodBank->setEmergencyFlagB(true);
	else
		bloodBank->setEmergencyFlag(true);

	//For debugging
	//ofstream myfile;
	//myfile.open("TimesBetweenEmergencyOrders.txt", ios_base::app);
	//myfile << getTimeToExecution() << endl;
	//myfile.close();
}


EmergencyBloodOrder::~EmergencyBloodOrder()
{
}



void EmergencyBloodOrder::execute()
{
	if (type)
	{
		for (int i = 0; i < 12; i++)
		{

			bloodBank->add_blood_unitB(new BloodUnit(300));
		}
		bloodBank->setEmergencyFlagB(false);
	}
	else
	{
		for (int i = 0; i < 12; i++)
		{

			bloodBank->add_blood_unit(new BloodUnit(300));
		}
		bloodBank->setEmergencyFlag(false);
	}
}
int roll_emergency()
{
	static double a = 0.12354376234;	//This is the seed
	a = a * 79 - (int)(a * 79);
	int s;
		if (a > 0.5)
			s = 1;
		else
			s = -1;
	a = a * 79 - (int)(a * 79);
	return round( s * 0.1*sqrt(3.1415 / 8)*log((1 + a) / (1 - a)) + 500);
}