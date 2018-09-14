#include "stdafx.h"
#include "EmergencyBloodOrder.h"
#include"SendPatientHome.h"
#include"BloodOrder.h"
#include <fstream>
using namespace std;

EmergencyBloodOrder::EmergencyBloodOrder(BloodBank* blood_bank,bool _bloodType, BloodDonationPoint* _bloodPoint, Calendar* _calendar)
{
	setTimetoExecution(roll_emergency());
	setType(1);
	bloodBank = blood_bank;
	bloodPoint = _bloodPoint;
	calendar = _calendar;
	btype = _bloodType;
	if(btype)
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
	if (btype)
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
	//Conditional events:
	if (bloodBank->get_blood_bank_size() < 10 && !bloodBank->getNonEmergencyFlag())							//Zamówienie krwii A
	{
		calendar->addEvent(new BloodOrder(bloodBank, 0, calendar, bloodPoint));
	}
	if (bloodBank->get_blood_bank_sizeB() < 10 && !bloodBank->getNonEmergencyFlagB())							//Zamówienie krwii B
	{
		calendar->addEvent(new BloodOrder(bloodBank, 1, calendar, bloodPoint));
	}
	if (bloodPoint->DoWeCallForAEmergencyBloodOrderA() && !bloodBank->getEmergencyFlag())		//Zamówienie awaryjne krwii A
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 0,bloodPoint,calendar));
	}
	if (bloodPoint->DoWeCallForAEmergencyBloodOrderB() && !bloodBank->getEmergencyFlagB())		//Zamówienie awaryjne krwii B
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 1, bloodPoint, calendar));
	}
	if (bloodPoint->DoWeSendPatientWithBloodTypeA())												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
	}
	if (bloodPoint->DoWeSendPatientWithBloodTypeB())												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
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