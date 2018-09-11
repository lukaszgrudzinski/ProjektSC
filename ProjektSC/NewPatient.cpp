#include "stdafx.h"
#include "NewPatient.h"
#include "Patient.h"
#include "BloodOrder.h"
#include "EmergencyBloodOrder.h"
#include "SendPatientHome.h"
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
	calendar->addEvent(new NewPatient(bloodPoint, calendar,bloodBank));
	bloodPoint->addPatient();
	//Conditional events:
	if (bloodBank->get_blood_bank_size() < 10 && !bloodBank->getNonEmergencyFlag())							//Zamówienie krwii A
	{
		calendar->addEvent(new BloodOrder(bloodBank, 0, calendar, bloodPoint));
	}
	if (bloodBank->get_blood_bank_sizeB() < 10 && !bloodBank->getNonEmergencyFlagB())							//Zamówienie krwii B
	{
		calendar->addEvent(new BloodOrder(bloodBank, 1, calendar, bloodPoint));
	}
	if (!bloodPoint->isLineEmpty() && bloodPoint->getPatientsBloodTypeNeeded() == 0 && bloodBank->get_blood_bank_size() < bloodPoint->getPatientsBloodNeeded() && !bloodBank->getEmergencyFlag())		//Zamówienie awaryjne krwii A
	{
		calendar->addEvent(new EmergencyBloodOrder(bloodBank, 0, bloodPoint, calendar));
	}
	if (!bloodPoint->isLineEmpty() && bloodPoint->getPatientsBloodTypeNeeded() == 1 && bloodBank->get_blood_bank_sizeB() < bloodPoint->getPatientsBloodNeeded() && !bloodBank->getEmergencyFlagB())		//Zamówienie awaryjne krwii B
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

NewPatient::NewPatient(BloodDonationPoint* _bloodPoint,Calendar* _calendar,BloodBank* _bloodBank)
{
	setTimetoExecution(roll_patient());
	bloodBank = _bloodBank;
	calendar = _calendar;
	bloodPoint = _bloodPoint;
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