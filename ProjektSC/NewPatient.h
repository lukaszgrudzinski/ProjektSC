#pragma once
#include "BloodDonationPoint.h"
#include "Event.h"
#include "BloodBank.h"
#include "Calendar.h"
int roll_patient();
class NewPatient : public Event
{
	BloodDonationPoint* bloodPoint;
	Calendar* calendar;
	BloodBank* bloodBank;
public:
	void execute(BloodDonationPoint *bloodPoint);
	void execute() override;
	NewPatient(BloodDonationPoint * _bloodPoint,Calendar* _calendar,BloodBank * _bloodBank);
	~NewPatient();
};

