#pragma once
#include "BloodUnit.h"
#include"Calendar.h"
int roll_research();
class BloodBank
{
	std::vector <BloodUnit*> BloodPool;
	std::vector <BloodUnit*> BloodPoolB;
	Calendar* calendar;
	int bloodUnitsWasted;
	int bloodUnitsUsed;
	int bloodUnitsGivenForResearch;
	bool emergencyOrderFlag;
	bool nonEmergencyFlag;
	bool emergencyOrderFlagB;
	bool nonEmergencyFlagB;
	
public:
	void incBloodUnitsUsed(int n);
	bool getEmergencyFlag();
	bool getNonEmergencyFlag();
	void setNonEmergencyFlag(bool a);
	void setEmergencyFlag(bool a);
	bool getEmergencyFlagB();
	bool getNonEmergencyFlagB();
	void setNonEmergencyFlagB(bool a);
	void setEmergencyFlagB(bool a);
	int get_blood_bank_size();
	int get_blood_bank_sizeB();
	void add_blood_unit(BloodUnit *bunit);
	void add_blood_unitB(BloodUnit *bunit);
	void sortBlood();
	int showTopId();
	void showBloodBankByAge();
	bool DoWeHaveXBloodUnits(int X);
	bool DoWeHaveXBloodUnitsB(int X);
	void popBloodUnit(int numberOfBloodUnits);
	void popBloodUnitB(int numberOfBloodUnits);
	void ageBloodBy(int time);
	void utilizeOldBlood();
	int getBloodUnitsWasted();
	int getBloodUnitsUsed();
	static bool isOlder(const BloodUnit* a, const BloodUnit* b);
	BloodBank(Calendar* _calendar);
	~BloodBank();
};

