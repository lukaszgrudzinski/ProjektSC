//Wydarzenie warunkowe polegające na zamówieniu ilosci krwii w przypadku gdy jest jej za mało w banku krwii aby obsłużyc pacjentów
#pragma once
#include "BloodDonationPoint.h"
#include "Event.h"
#include"BloodBank.h"
int roll_emergency();

class EmergencyBloodOrder : public Event
{
	BloodBank * bloodBank;
	bool type;
public:
	EmergencyBloodOrder(BloodBank* blood_bank,bool bloodType);
	~EmergencyBloodOrder();
	void execute() override;
};

