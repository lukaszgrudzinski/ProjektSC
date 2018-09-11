#include"BloodDonationPoint.h"
#include "Event.h"
#include "BloodBank.h"
#include"Calendar.h"
int roll_donor();
bool roll_blood_type();
class NewBloodDonor : public Event
{
	Calendar* calendar;
	BloodBank* bloodBank;
	BloodDonationPoint* bloodPoint;
	bool bloodType;
public:
	void execute(BloodDonationPoint *bloodPoint);
	void execute() override;
	NewBloodDonor(BloodBank* _bloodBank,Calendar* _calendar,BloodDonationPoint* _bloodPoint);
	~NewBloodDonor();
};
