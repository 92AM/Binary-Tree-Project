#pragma once
#include "Aircraft.h"

class Helicopter: public Aircraft
{
public:
	Helicopter(void);	//constructor
	~Helicopter(void); 	//destructor

	//Setters
	void setRotorDiameter(int);
	void setNoOfRotorBlades(int);

	//Getters
	int getRotorDiameter(void);
	int getNoOfRotorBlades(void);

private:

	//helicopter specific variables
	int _rotorDiameter;
	int _noOfRotorBlades;

};

