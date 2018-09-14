#include "stdafx.h"
#include "AwarenessCampaign.h"
#include"BloodOrder.h"
#include"EmergencyBloodOrder.h"
#include"SendPatientHome.h"
#include"EndOfCampaign.h"


void AwarenessCampaign::execute()
{
	bloodPoint->setCorrectionDueToAwarenessCampaign(roll_correction());
	calendar->addEvent(new EndOfCampaign(bloodBank, calendar, bloodPoint));
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

AwarenessCampaign::AwarenessCampaign(BloodBank * _bloodBank, Calendar * _calendar, BloodDonationPoint * _bloodPoint)
{
	bloodPoint = _bloodPoint;
	setTimetoExecution(roll_time_to_next());
	calendar = _calendar;
	bloodBank = _bloodBank;
	setType(5);
}


AwarenessCampaign::~AwarenessCampaign()
{
}

int roll_correction()
{
	static double a = 0.175555987;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return round(a * 100 + 100);
}
int roll_time_to_next()
{
	static double a = 0.175555987;	//This is the seed
	a = a * 79 - (int)(a * 79);
	return round(a * 2000 + 20000);
}