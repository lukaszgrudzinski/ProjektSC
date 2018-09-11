#include "stdafx.h"
#include "NewPatient.h"
#include "Patient.h"
#include <fstream>
using namespace std;

void NewPatient::execute(BloodDonationPoint *bloodPoint)
{
	//zaplanuj kolejnego pacjeta
	bloodPoint->addPatient();
	//bloodPoint->addEvent(new NewPatient);
}

void NewPatient::execute()
{
	calendar->addEvent(new NewPatient(bloodBank, calendar));
	bloodBank->addPatient();
	
}

NewPatient::NewPatient(BloodDonationPoint* _bloodBank,Calendar* _calendar)
{
	setTimetoExecution(roll_patient());
	bloodBank = _bloodBank;
	calendar = _calendar;
	setType(3);
	//For testing
	//ofstream myfile;
	//myfile.open("TimesBetweenPatients.txt", ios_base::app);
	//myfile << getTimeToExecution() << endl;
	//myfile.close();
}


NewPatient::~NewPatient()
{
}

int roll_patient()
{
	static double a= 0.175555987;
	a = a * 79 - (int)(a * 79);
	return round( -250 * log(a));//-200
}