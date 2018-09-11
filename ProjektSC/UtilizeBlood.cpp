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
	if (!bloodPoint->isLineEmpty() && bloodPoint->getPatientsBloodTypeNeeded() == 0 && bloodBank->get_blood_bank_size() < bloodPoint->getPatientsBloodNeeded() && !bloodBank->getEmergencyFlag())		//Zamówienie awaryjne krwii A
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 0, bloodPoint, calendar));
	}
	if (!bloodPoint->isLineEmpty() && bloodPoint->getPatientsBloodTypeNeeded() == 1 && bloodBank->get_blood_bank_sizeB() < bloodPoint->getPatientsBloodNeeded() && !bloodBank->getEmergencyFlagB())		//Zamówienie awaryjne krwii B
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 1, bloodPoint, calendar));
	}
	if (!bloodPoint->isLineEmpty() && bloodPoint->getPatientsBloodTypeNeeded() == 0 && bloodBank->get_blood_bank_size() > bloodPoint->getPatientsBloodNeeded() && bloodPoint->getPatientsBloodNeeded() != 0)												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
	}
	if (!bloodPoint->isLineEmpty() && bloodPoint->getPatientsBloodTypeNeeded() == 1 && bloodBank->get_blood_bank_sizeB() > bloodPoint->getPatientsBloodNeeded() && bloodPoint->getPatientsBloodNeeded() != 0)												//Giving a pacient needed blood and sending him home
	{
		calendar->addEvent(new SendPatientHome(bloodPoint, bloodBank, calendar));
	}
}

