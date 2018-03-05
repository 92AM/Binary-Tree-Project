#pragma once

#include <string>
using namespace std;

class Aircraft
{
public:
	Aircraft(void);		//constructor 
	~Aircraft(void);	//destructor
	Aircraft(int callSign);

	//operator overloaders (for Aircraft callSign comparison)
	bool operator<(Aircraft cP);
	bool operator>(Aircraft cP);
	bool operator!=(Aircraft cP);
	bool operator==(Aircraft cP);
	bool operator<=(Aircraft cP);
	bool operator>=(Aircraft cP);

	//Setters
	void setCallSign(int);
	void setSerialNumber(int);
	void setOwnerName(string);
	void setProductionDate(string);
	void setManufacturer(string);
	void setMinSpeed(double);
	void setMaxSpeed(double);
	void setMaxClimbRate(double);
	void setType(string);
	
	//Getters
	int getCallSign(void);
	int getSerialNumber(void);
	string getOwnerName(void);
	string getProductionDate(void);
	string getManufacturer(void);
	double getMinSpeed(void);
	double getMaxSpeed(void);
	double getMaxClimbRate(void);
	string getType(void);

private:

	//aircraft variables
	string _type;
	int _callSign;		//stores unique number 
	int _serialNumber;
	string _ownerName;
	string _productionDate;
	string _manufacturer;
	int _minSpeed;
	int _maxSpeed;
	int _maxClimbRate;
};