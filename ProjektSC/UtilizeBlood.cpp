//Event for getting rid of old blood
#include "stdafx.h"
#include "UtilizeBlood.h"
#include"Calendar.h"
#include"BloodOrder.h"
#include"EmergencyBloodOrder.h"
#include"SendPatientHome.h"
#include <vector>


UtilizeBlood::UtilizeBlood(int bestBy, BloodBank* _bloodBank, Calendar* _calendar, BloodDonationPoint * _bloodPoint)
{
	setTimetoExecution(bestBy);
	setType(4);
	bloodBank = _bloodBank;
	calendar = _calendar;
	bloodPoint = _bloodPoint;
	
}


UtilizeBlood::~UtilizeBlood()
{
}


void UtilizeBlood::execute()
{
	bloodBank->utilizeOldBlood();
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
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
	}
	if (bloodPoint->DoWeSendPatientWithBloodTypeB())												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
	}
}

