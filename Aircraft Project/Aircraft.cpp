#include "Aircraft.h"

//constructors 
Aircraft::Aircraft(void)
{

}

Aircraft::Aircraft(int callSign)
{
	_callSign = callSign;
}

//destructor
Aircraft::~Aircraft(void)
{

}

//operator overloading functions 
bool Aircraft::operator<(Aircraft cP)
{
	return (getCallSign() < cP.getCallSign());
}

bool Aircraft::operator>(Aircraft cP)
{
	return (getCallSign() > cP.getCallSign());
}

bool Aircraft::operator!=(Aircraft cP)
{
	return (getCallSign() != cP.getCallSign());
}

bool Aircraft::operator==(Aircraft cP)
{
	return (getCallSign() == cP.getCallSign());
}

bool Aircraft::operator<=(Aircraft cP)
{
	return (cP.getCallSign() <= cP.getCallSign());
}

bool Aircraft::operator>=(Aircraft cP)
{
	return (cP.getCallSign() >= cP.getCallSign());
}

//Setters
void Aircraft::setCallSign(int callSign)
{
	_callSign = callSign;
}

void Aircraft::setSerialNumber(int serialNumber)
{
	_serialNumber = serialNumber;
}

void Aircraft::setOwnerName(string ownerName)
{
	_ownerName = ownerName;
}

void Aircraft::setProductionDate(string proudctionDate)
{
	_productionDate = proudctionDate;
}

void Aircraft::setManufacturer(string manufacturer)
{
	_manufacturer = manufacturer;
}

void Aircraft::setMinSpeed(double minSpeed)
{
	_minSpeed = minSpeed;
}

void Aircraft::setMaxSpeed(double maxSpeed)
{
	_maxSpeed = maxSpeed;
}

void Aircraft::setMaxClimbRate(double maxClimbRate)
{
	_maxClimbRate = maxClimbRate;
}

void Aircraft::setType(string type)
{
	_type = type;
}

//Getters
int Aircraft::getCallSign(void)
{
	return _callSign;
}

int Aircraft::getSerialNumber(void)
{
	return _serialNumber;
}

string Aircraft::getOwnerName(void)
{
	return _ownerName;
}

string Aircraft::getProductionDate(void)
{
	return _productionDate;
}

string Aircraft::getManufacturer(void)
{
	return _manufacturer;
}

double Aircraft::getMinSpeed(void)
{
	return _minSpeed;
}

double Aircraft::getMaxSpeed(void)
{
	return _maxSpeed;
}

double Aircraft::getMaxClimbRate(void)
{
	return _maxClimbRate;
}

string Aircraft::getType(void)
{
	return _type;
}
