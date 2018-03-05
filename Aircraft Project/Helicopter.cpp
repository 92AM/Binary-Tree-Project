#include "Helicopter.h"


Helicopter::Helicopter(void)
{
}


Helicopter::~Helicopter(void)
{
}

//Setters
void Helicopter::setRotorDiameter(int rotorDiameter)
{
	_rotorDiameter = rotorDiameter;
}

void Helicopter::setNoOfRotorBlades(int noOfRotorBlades)
{
	_noOfRotorBlades = noOfRotorBlades;
}

//Getters
int Helicopter::getRotorDiameter()
{
	return _rotorDiameter;
}

int Helicopter::getNoOfRotorBlades()
{
	return _noOfRotorBlades;
}