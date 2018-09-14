//Class representing the whole Blood donation point and includes all objects inside

#include "stdafx.h"
#include <iostream>
#include "BloodDonationPoint.h"
#include "Patient.h"
#include "Patient.h"
#include <codecvt>
#include <algorithm>
#include <vector>
#include "UtilizeBlood.h"
#include <memory>
#include "Patient.h"



int BloodDonationPoint::getCorrectionDueToAwarenessCampaign()
{
	return correctionDueToAwarenessCampaign;
}

void BloodDonationPoint::setCorrectionDueToAwarenessCampaign(int x)
{
	correctionDueToAwarenessCampaign = x;
}

void BloodDonationPoint::showPatients()
{
	std::cout << "Current line of pacients:" << std::endl<<"	";
	if (lineOfPatients.size() == 0)
		std::cout << "Empty" << std::endl;
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		std::cout << "Patient nr " << i << " requires " << lineOfPatients[i]->bloodUnitsNeeded << " Units of blood type ";
		if (lineOfPatients[i]->typeeNeeded)
			std::cout << "B" << std::endl<<"	";
		else 
			std::cout << "A" << std::endl<<"	";
	}
	return;
}

void BloodDonationPoint::deleteFirstPatient()
{
	lineOfPatients.erase(lineOfPatients.begin());
}


bool BloodDonationPoint::canWeSendAPacientHome()
{
	if (isLineEmpty())
		return false;
	if (lineOfPatients[0]->bloodUnitsNeeded <= bloodBank->get_blood_bank_size())
		return true;
	else
		return false;
}

int BloodDonationPoint::getPatientsBloodNeeded()
{
	if (lineOfPatients.size() == 0)
		return 0;
	return lineOfPatients[0]->bloodUnitsNeeded;
}

bool BloodDonationPoint::getPatientsBloodTypeNeeded()
{
	if (lineOfPatients.size() == 0)
		return 0;
	return lineOfPatients[0]->typeeNeeded;
}

bool BloodDonationPoint::DoWeSendPatientWithBloodTypeA()
{
	
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		if (lineOfPatients[i]->typeeNeeded == 0)
		{
			if (bloodBank->DoWeHaveXBloodUnits(lineOfPatients[i]->bloodUnitsNeeded))
				return true;
		}

	}
	return false;
}

bool BloodDonationPoint::DoWeSendPatientWithBloodTypeB()
{
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		if (lineOfPatients[i]->typeeNeeded == 1)
		{
			if (bloodBank->DoWeHaveXBloodUnitsB(lineOfPatients[i]->bloodUnitsNeeded))
				return true;
		}

	}
	return false;
}

bool BloodDonationPoint::DoWeCallForAEmergencyBloodOrderA()
{
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		if (lineOfPatients[i]->typeeNeeded == 0 && bloodBank->get_blood_bank_size() < lineOfPatients[i]->bloodUnitsNeeded)
			return true;

	}
	return false;
}

bool BloodDonationPoint::DoWeCallForAEmergencyBloodOrderB()
{
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		if (lineOfPatients[i]->typeeNeeded == 1 && bloodBank->get_blood_bank_sizeB() < lineOfPatients[i]->bloodUnitsNeeded)
			return true;

	}
	return false;
}

bool BloodDonationPoint::isLineEmpty()
{
	if (lineOfPatients.size() == 0)
		return true;
	else
		return false;
}

int BloodDonationPoint::eraseFirstPatientWithAType()
{
	int numberOfBloodUnitsToDelete;
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		if (bloodBank->get_blood_bank_size() >= lineOfPatients[i]->bloodUnitsNeeded &&lineOfPatients[i]->typeeNeeded == 0)
		{
			numberOfBloodUnitsToDelete = lineOfPatients[i]->bloodUnitsNeeded;
			Patient* temp = lineOfPatients.back();						 //
			lineOfPatients.pop_back();									 //Deletes patient i
			if (lineOfPatients.size() > 0 && i < lineOfPatients.size())	 //
				lineOfPatients[i] = temp;								 //
			return numberOfBloodUnitsToDelete;
			
		}
		
	}
	return 0;//Returns number of blood units to delete from bloodbank
}

int BloodDonationPoint::eraseFirstPatientWithBType()
{
	int numberOfBloodUnitsToDelete;
	for (int i = 0; i < lineOfPatients.size(); i++)
	{
		if (bloodBank->get_blood_bank_sizeB() >= lineOfPatients[i]->bloodUnitsNeeded &&lineOfPatients[i]->typeeNeeded == 1)
		{
			numberOfBloodUnitsToDelete = lineOfPatients[i]->bloodUnitsNeeded;
			Patient* temp = lineOfPatients.back();						 //
			lineOfPatients.pop_back();									 //Deletes patient i
			if (lineOfPatients.size() > 0 && i < lineOfPatients.size())	 //
				lineOfPatients[i] = temp;								 //
			return numberOfBloodUnitsToDelete;

		}

	}
	return 0;//Returns number of blood units to delete from bloodbank
}

void BloodDonationPoint::addPatient()
{
	lineOfPatients.push_back(new  Patient(5)); //TODO: replace 5 with rand
}





BloodDonationPoint::BloodDonationPoint(BloodBank* _bloodBank)
{
	bloodBank = _bloodBank;
	correctionDueToAwarenessCampaign = 0;
}


BloodDonationPoint::~BloodDonationPoint()
{
}
