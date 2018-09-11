#pragma once
#include "BloodDonationPoint.h"
#include "Event.h"
#include "BloodBank.h"
#include "Calendar.h"
int roll_patient();
class NewPatient : public Event
{
	BloodDonationPoint* bloodBank;
	Calendar* calendar;
public:
	void execute(BloodDonationPoint *bloodPoint);
	void execute() override;
	NewPatient(BloodDonationPoint * _bloodBank,Calendar* _calendar);
	~NewPatient();
};

