#include "stdafx.h"
#include "BloodOrder.h"
#include"BloodDonationPoint.h"
#include"EmergencyBloodOrder.h"
#include"SendPatientHome.h"
#include <fstream>
using namespace std;


void BloodOrder::execute()
{
	if (btype)
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
	//Conditional events:
	if (bloodBank->get_blood_bank_size() < 10 && !bloodBank->getNonEmergencyFlag())							//Zamówienie krwii A
	{
		calendar->addEvent(new BloodOrder(bloodBank, 0,calendar,bloodPoint));
	}
	if (bloodBank->get_blood_bank_sizeB() < 10 && !bloodBank->getNonEmergencyFlagB())							//Zamówienie krwii B
	{
		calendar->addEvent(new BloodOrder(bloodBank, 1, calendar, bloodPoint));
	}
	if (bloodPoint->DoWeCallForAEmergencyBloodOrderA() && !bloodBank->getEmergencyFlag())		//Zamówienie awaryjne krwii A
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 0, bloodPoint, calendar));
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

BloodOrder::BloodOrder(BloodBank* _bloodBank,bool _type, Calendar * _calendar, BloodDonationPoint *_bloodPoint)
{
	setTimetoExecution(roll_time());
	bloodBank = _bloodBank;
	bloodPoint = _bloodPoint;
	calendar = _calendar;
	setType(0);
	btype = _type;
	if(btype)
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

