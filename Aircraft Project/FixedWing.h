#pragma once
#include "Aircraft.h"

class FixedWing: public Aircraft
{
public:
	FixedWing(void); 	//constructor
	~FixedWing(void); 	//destructor

	//Setters
	void setWingSpan(int);

	//Getters
	int getWingSpan(void);

private:

	//fixed wing specific variable
	int _wingSpan;
};

