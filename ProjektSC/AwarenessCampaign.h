
#pragma once
#include "Event.h"
#include"BloodDonationPoint.h"
int roll_correction();
int roll_time_to_next();
class AwarenessCampaign :
	public Event
{
	Calendar* calendar;
	BloodBank* bloodBank;
	BloodDonationPoint* bloodPoint;
public:
	void execute() override;
	AwarenessCampaign(BloodBank* _bloodBank, Calendar* _calendar, BloodDonationPoint* _bloodPoint);
	~AwarenessCampaign();
};

