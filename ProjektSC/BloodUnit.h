//A class representing a single blood unit
#pragma once
#include <vector>
 int ID();
 int roll_type();
class BloodUnit
{
	int id;
	int timeToGoingBad;
	bool type;//0-A, 1-B
public:
	BloodUnit(int _timeToGoingBad=5,bool _type=0);
	~BloodUnit();
	int getId() const;
	int getTimeToGoingBad() const;
	void ageBy(int t);


};

