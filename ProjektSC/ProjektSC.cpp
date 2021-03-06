#include "stdafx.h"
#include "stdio.h"
#include "iostream"
#include "BloodUnit.h"
#include "BloodDonationPoint.h"
#include "UtilizeBlood.h"
#include "BloodOrder.h"
#include"EmergencyBloodOrder.h"
#include"NewBloodDonor.h"
#include"NewPatient.h"
#include"SendPatientHome.h"
#include"AwarenessCampaign.h"
#include <vector>
#include "Calendar.h"


using namespace std;
int main()
{
	double percentagewasted, percentageUsed, percentageGivenAway, averageNofEmergencyOrdersInASim;
	percentagewasted = percentageUsed = percentageGivenAway = averageNofEmergencyOrdersInASim = 0;
	int total = 0;
	const int howManySimulations = 1000;
	double avrTimeBetweenDonors = 0;
	//Choosing simulation mode:
	cout << "Please choose simulation mode(c-continuous , s-step)"<<endl;
	char trybPracy;
	cin >> trybPracy;
	if (trybPracy != 'c' && trybPracy != 's')
	{
		cout << "Wrong input" << endl;
		getchar();
		return 0;
	}

	//Main loop
	for (int j = 0; j < howManySimulations; j++)
	{
		//Initializing the model:
		Calendar calendar;
		BloodBank bloodbank(&calendar);
		BloodDonationPoint hospital(&bloodbank);
		calendar.addEvent(new NewBloodDonor(&bloodbank, &calendar,&hospital));
		calendar.addEvent(new NewPatient(&hospital, &calendar,&bloodbank));
		calendar.addEvent(new AwarenessCampaign(&bloodbank, &calendar, &hospital));
		calendar.addEvent(new BloodOrder(&bloodbank, 0, &calendar, &hospital));
		calendar.addEvent(new BloodOrder(&bloodbank, 1, &calendar, &hospital));

		while (calendar.getCurrentTime()<100000)
		{
			

			if (trybPracy == 's')
				getchar();
			int iterator = calendar.getSizeOfEventList();
			for (int j = 0; j < iterator; j++)
			{
				if (calendar.getTimeOfNthEvent(j) == 0)
				{
					calendar.executeNthElement(j);
					j=0;
					iterator= calendar.getSizeOfEventList();	//refresh so it includes newly added events
				}
			}
			
			if (trybPracy == 's')
			{
				std::cout << " _________________________ " << endl;
				std::cout << "Current time:" << calendar.getCurrentTime()<<std::endl;
				bloodbank.showBloodBankByAge();
				calendar.showEvents();
				hospital.showPatients();
			}
			bloodbank.ageBloodBy(calendar.passTime());

			//if (trybPracy == 's')
			//{
			//	std::cout << " _________________________ " << endl;
			//	bloodbank.showBloodBankByAge();
			//	std::cout << endl;
			//	calendar.showEvents();
			//}
		}
		//std::cout << "Wasted:" << bloodbank.getBloodUnitsWasted() << endl;
		//std::cout << "Used:" << bloodbank.getBloodUnitsUsed() << endl;
		//std::cout << "Given for research:" << bloodbank.getBloodGivenForResearch() << endl;
		//std::cout << "Awaryjnych:"<<calendar.getNumberOfEmergencyOrders()<<std::endl;
		total += bloodbank.getBloodUnitsWasted() + bloodbank.getBloodUnitsUsed();
		percentagewasted +=bloodbank.getBloodUnitsWasted();
		percentageUsed +=bloodbank.getBloodUnitsUsed();
		
		averageNofEmergencyOrdersInASim += calendar.getNumberOfEmergencyOrders();
	}
	std::cout << "Srednia liczba zamowien awaryjnych na symulacje to: " << averageNofEmergencyOrdersInASim / howManySimulations << std::endl;
	std::cout << "Sredni procent jednostek krwii danych pacjentom to: " << percentageUsed*100 / total <<"%"<< std::endl;
	std::cout << "Sredni procent jednostek krwii zmarnowanych to: " << percentagewasted * 100 / total << "%" << std::endl;
	
	std::cin >> trybPracy;

				
    return 0;
}

