#include "stdafx.h"
#include "NewBloodDonor.h"
#include"BloodOrder.h"
#include"EmergencyBloodOrder.h"
#include"SendPatientHome.h"
#include <ostream>
#include <iostream>
#include <fstream>
using namespace std;




void NewBloodDonor::execute()
{
	if(bloodType)
		bloodBank->add_blood_unitB(new BloodUnit(500));
	else
		bloodBank->add_blood_unit(new BloodUnit(500));
	calendar->addEvent(new NewBloodDonor(bloodBank, calendar,bloodPoint));
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
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 0, bloodPoint, calendar));
	}
	if (bloodPoint->DoWeCallForAEmergencyBloodOrderB() && !bloodBank->getEmergencyFlagB())		//Zamówienie awaryjne krwii B
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 1, bloodPoint, calendar));
	}
	if (bloodPoint->DoWeSendPatientWithBloodTypeA())												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank,calendar));
	}
	if (bloodPoint->DoWeSendPatientWithBloodTypeB())												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
	}
}

NewBloodDonor::NewBloodDonor(BloodBank * _bloodBank, Calendar * _calendar, BloodDonationPoint* _bloodPoint)
{
	bloodPoint = _bloodPoint;
	setTimetoExecution(roll_donor() - _bloodPoint->getCorrectionDueToAwarenessCampaign());
	calendar = _calendar;
	bloodBank = _bloodBank;
	bloodBank->bloodPoint = bloodPoint;
	setType(2);
	bloodType = roll_blood_type();
	//For debugging
	//ofstream myfile;
	//myfile.open("TimesBetweenDonors.txt", ios_base::app);
	//myfile << getTimeToExecution()<<endl;
	//myfile.close();
}




NewBloodDonor::~NewBloodDonor()
{
}

int roll_donor()
{
	static double a = 0.175555987;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return round( -950 * log(a));
}
bool roll_blood_type()
{
	static double a = 0.175555987;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return a>0.6;	
}