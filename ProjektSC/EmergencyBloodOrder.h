//Wydarzenie warunkowe polegające na zamówieniu ilosci krwii w przypadku gdy jest jej za mało w banku krwii aby obsłużyc pacjentów
#pragma once
#include "BloodDonationPoint.h"
#include "Event.h"
#include"BloodBank.h"
int roll_emergency();

class EmergencyBloodOrder : public Event
{
	BloodBank * bloodBank;
	Calendar * calendar;
	BloodDonationPoint * bloodPoint;
	bool btype;
public:
	EmergencyBloodOrder(BloodBank* blood_bank,bool bloodType,BloodDonationPoint* _bloodPoint,Calendar* _calendar);
	~EmergencyBloodOrder();
	void execute() override;
};

