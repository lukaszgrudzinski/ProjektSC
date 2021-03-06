﻿//Wydarzenie warunkowe odsyłające pacjenta do domu w przypadku gdy wystarczy dla niego krwii w banku krwii
//Brany pod uwage jest pierwszyw kolejce pacjent
#include "stdafx.h"
#include "SendPatientHome.h"
#include"BloodOrder.h"
#include"EmergencyBloodOrder.h"
#include <vector>
#include <iostream>


SendPatientHome::SendPatientHome(BloodDonationPoint* _bloodPoint,BloodBank* _bloodBank,Calendar * _calendar)
{
	setTimetoExecution(0);
	bloodPoint = _bloodPoint;
	bloodBank = _bloodBank;
	calendar = _calendar;
	setType(10);
}


SendPatientHome::~SendPatientHome()
{
}


void SendPatientHome::execute()
{
	if (bloodPoint->DoWeSendPatientWithBloodTypeA())
		bloodBank->popBloodUnit(bloodPoint->eraseFirstPatientWithAType());
	else if (bloodPoint->DoWeSendPatientWithBloodTypeB())
		bloodBank->popBloodUnitB(bloodPoint->eraseFirstPatientWithBType());
	
	//std::cout << "A patient got his blood!" << std::endl;
	

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

void SendPatientHome::execute(BloodDonationPoint * abc)
{
	;
}

