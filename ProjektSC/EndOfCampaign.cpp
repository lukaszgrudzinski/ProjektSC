#include "stdafx.h"
#include "EndOfCampaign.h"
#include"BloodOrder.h"
#include"EmergencyBloodOrder.h"
#include"SendPatientHome.h"
#include"AwarenessCampaign.h"



EndOfCampaign::EndOfCampaign(BloodBank * _bloodBank, Calendar * _calendar, BloodDonationPoint * _bloodPoint)
{
	bloodPoint = _bloodPoint;
	calendar = _calendar;
	bloodBank = _bloodBank;
	setTimetoExecution(7200);
	setType(6);
}

void EndOfCampaign::execute()
{
	bloodPoint->setCorrectionDueToAwarenessCampaign(0);
	calendar->addEvent(new AwarenessCampaign(bloodBank, calendar, bloodPoint));
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

EndOfCampaign::~EndOfCampaign()
{
}
