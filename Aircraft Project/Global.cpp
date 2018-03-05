#include "Global.h"


Global::Global(void)
{
	_isRunning = true;
}


Global::~Global(void)
{
	//destroy database
	_database.destroy();
}


void Global::_load(string fileName)
{
	try
	{
		//load file
		ifstream file;
		file.open(fileName);

		//check if file opened successfully 
		if(file.is_open())
		{
			//for loop control
			bool fileLoading = true;

			while(fileLoading)
			{
				//make a temp aircraft pointer
				Aircraft* temp = new Aircraft;

				string input;

				//get data from file and store it in tree 
				getline(file, input, ',');
				temp->setCallSign(atoi(input.c_str()));

				getline(file, input, ',');
				temp->setType(input);

				getline(file, input, ',');
				temp->setSerialNumber(atoi(input.c_str()));

				getline(file, input, ',');
				temp->setOwnerName(input);

				getline(file, input, ',');
				temp->setManufacturer(input);

				getline(file, input, ',');
				temp->setProductionDate(input);

				getline(file, input, ',');
				temp->setMinSpeed(atoi(input.c_str()));

				getline(file, input, ',');
				temp->setMaxSpeed(atoi(input.c_str()));

				getline(file, input, ',');
				temp->setMaxClimbRate(atoi(input.c_str()));

				//for fixed wing add wingspan
				if (temp->getType() == "Jet" || temp->getType() == "Glider" || temp->getType() == "Propeller Driven Aircraft")
				{
					getline(file, input, ',');
					((FixedWing*) temp)->setWingSpan(atoi(input.c_str()));

					_database.insert(temp);
				}

				//for helicopter add rotor diameter and no of rotor blades
				else if(temp->getType() == "Helicopter")
				{
					getline(file, input, ',');
					((Helicopter*) temp)->setRotorDiameter(atoi(input.c_str()));

					getline(file, input, ',');
					((Helicopter*) temp)->setNoOfRotorBlades(atoi(input.c_str()));

					_database.insert(temp);
				}

				//if finished reading file, break from loop and exit function
				if( file.eof() )
				{
					fileLoading = false;
				}
			}
		}
		else //if file didn't open successfully that means the text file is either corrupt orr doesn't exist ... in that case throw exception
		{
			throw exception(NO_TEXT_FILE);
		}
	}
	catch(exception excp)
	{
		throw excp;
	}
}


void Global::_save(string fileName)
{
	bool isSaved = false;

	try
	{
		//open file 
		ofstream file;
		file.open(fileName, ios::trunc);

		//create vector to store all nodes from binary tree
		vector<Aircraft*> getAllAircraft = _database.vectorConversion();

		//iterate through the vector outstream it to the file
		for( unsigned int airIdx = 0; airIdx < getAllAircraft.size(); airIdx++ )
		{
			file << getAllAircraft[airIdx]->getCallSign() << "," << getAllAircraft[airIdx]->getType() << "," 
				<< getAllAircraft[airIdx]->getSerialNumber() << "," << getAllAircraft[airIdx]->getOwnerName() 
				<< "," << getAllAircraft[airIdx]->getManufacturer() << "," << getAllAircraft[airIdx]->getProductionDate() 
				<< "," << getAllAircraft[airIdx]->getMinSpeed() << "," << getAllAircraft[airIdx]->getMaxSpeed() << "," 
				<< getAllAircraft[airIdx]->getMaxClimbRate() << "," ;
			if (getAllAircraft[airIdx]->getType()=="Jet" || 
				getAllAircraft[airIdx]->getType()== "Glider" || 
				getAllAircraft[airIdx]->getType() == "Propeller Driven Aircraft")
			{
				file<<((FixedWing*)getAllAircraft[airIdx])->getWingSpan()<<",\n";
			}
			else if(getAllAircraft[airIdx]->getType()=="Helicopter")
			{
				file <<((Helicopter*)getAllAircraft[airIdx])->getRotorDiameter()<<","<<((Helicopter*)getAllAircraft[airIdx])->getNoOfRotorBlades()<<",\n";
			}
		}

		file.close();

		isSaved = true;
		if(isSaved)
		{
			throw exception(AIRCRAFT_SAVED);
		}
	}
	catch(exception excp)
	{
		throw excp;
	}
}


void Global::run()
{
	//call _run()
	_run();
}


void Global::_run()
{
	cout << "  AIRCRAFT SYSTEM  " << endl << endl;

	//variable to keep track of menu options
	int option = 0;

	//variable to store call sign
	int inputCallSign = 0;

	//load text file
	try
	{
		_load("aircraft.txt");
	}
	catch(exception excp)
	{
		cout << excp.what() << endl;
	}

	//main loop starts
	while(_isRunning)
	{
		cout << "   1 - INSERT \n   2 - REMOVE \n   3 - SEARCH\n   4 - EDIT\n   5 - BROWSE \n   6 - CLEAR \n   7 - LOAD \n   8 - SAVE \n   9 - EXIT" << endl;
		cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
		cin >> option;

		//INSERT
		if( option == 1 )
		{
			try
			{
				// variable to keep track of sub menu (aircraft type selection menu)
				int aircraftChoice = 0;
				cout << "   1 - JET\n   2 - PROPELLER DRIVEN AIRCRAFT\n   3 - GLIDER\n   4 - HELICOPTER\n   9 - GO BACK TO MAIN MENU" << endl;
				cout << "-----------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cin >> aircraftChoice;
					
				//call add (global version) function
				_add(aircraftChoice);
			}
			catch (exception excp)
			{
				cout << excp.what() << endl;
			}
		}

		//REMOVE
		if(option == 2)
		{
			int toDelete;
			string confirm;
			cout << "Please enter a Call Sign of an aircraft for deletion" << endl;
			cin >> toDelete;
			cout << "Are you sure you want to delete this aircraft? y/n" << endl;
			cin  >> confirm;
			if((confirm == "y") || (confirm == "Y"))
			{
				try
				{
					//call remove function
					_database.remove(toDelete);
					cout << "Aircraft " << toDelete << " has been removed.\n";
				}
				catch ( exception excp)
				{
					cout << excp.what() << endl;
				}
			}

		}

		//SEARCH
		if(option == 3)
		{
			try
			{
				cout << "Enter a Call Sign: ";
				cin >> inputCallSign;
				cout << endl;
				
				//call search function
				_search(inputCallSign);
			}
			catch( exception ex )
			{
				cout << ex.what() << endl;
			}
		}

		//EDIT
		if(option == 4)
		{
			try
			{
				cout << "Enter a Call Sign to edit : " << endl;
				cin >> inputCallSign ;

				//call edit
				_edit(inputCallSign);
			}
			catch( exception excp )
			{
				cout << excp.what() << endl;
			}
		}

		//BROWSE
		if(option == 5)
		{
			try
			{
				//call browse function
				_browse();
			}
			catch (exception excp)
			{
				cout << excp.what() << endl;
			}
		}

		//CLEAR
		if(option == 6)
		{
			string confirm;
			cout << "Are you sure you want to clear the database? y/n" << endl;
			cin  >> confirm;
			if((confirm == "y") || (confirm == "Y"))
			{
				try
				{
					//call destroy function
					_database.destroy();
					cout << "database cleared" << endl;
				}
				catch(exception excp)
				{
					cout << excp.what() << endl;
				}
			}
			else
			{
				
			}
		}

		//LOAD
		if(option ==7)
		{
			try
			{
				//destroy database first
				_database.destroy();

				//then load text file
				_load("aircraft.txt");

				cout << "database loaded" << endl;
			}
			catch(exception excp)
			{
				cout << excp.what() << endl;
			}
		}

		//SAVE
		if(option ==8)
		{
			string confirm;
			cout << "Are you sure you want to save data? Existing data will get overwriten. y/n" << endl;
			cin  >> confirm;
			if((confirm == "y") || (confirm == "Y"))
			{
				try
				{
					//save to text file 
					_save("aircraft.txt");
				}
				catch(exception excp)
				{
					cout << excp.what() << endl;
				}
			}
		}

		//EXIT
		if (option== 9)
		{
			//exit system 
			_isRunning = false;
		}
	}
}


void Global::setupConsole()
{
	_setupConsole();
}


void Global::_setupConsole()
{
	//get current console size
	HWND console = GetConsoleWindow();
	RECT consoleRect;
	GetWindowRect(console, &consoleRect); 
	
	//reset to specification you prefer (this does not always work, but it was work a try)
	MoveWindow(console, consoleRect.left, consoleRect.top, 1000, 500 , TRUE);
}


void Global::_add(int userInput)
{
	//local variables to store aircraft specific information
	string type = "";
	int callSign = 0;
	int serialNumber = 0;
	string ownerName = "";
	string productionDate = "";
	string manufacturer= "";
	int minSpeed = 0;
	int maxSpeed = 0;
	int maxClimbRate = 0;
	int rotorDiameter = 0;
	int rotorBlades = 0;
	int wingSpan = 0;

	if (userInput == 1)
	{
		try
		{
			//For jet make a new jet pointer and call insert function
			Jet* jet = new Jet;

			cout << "Your choice of aircraft have been initialized (JET)" << endl;
			cout << "No space allowed, use underscore instead of spaces" << endl << endl;
			cout << "Please enter Call Sign" << endl;
			cin >> callSign;
			jet->setCallSign(callSign);
			type = "Jet";
			jet->setType(type);
			cout << "Please enter Serial Number" << endl;
			cin >> serialNumber;
			jet->setSerialNumber(serialNumber);
			cout << "Please enter Owner's Name" << endl;
			cin >> ownerName;
			jet->setOwnerName(ownerName);
			cout << "Please enter Manufacturer's Name" << endl;
			cin >> manufacturer; 
			jet->setManufacturer(manufacturer);
			cout << "Please enter Production Date (ddmmyyyy)" << endl;
			cin >> productionDate;
			jet->setProductionDate(productionDate);
			cout << "Please enter Minimum Speed" << endl;
			cin >> minSpeed;
			jet->setMinSpeed(minSpeed);
			cout << "Please enter Maximum Speed" << endl;
			cin >> maxSpeed;
			jet->setMaxSpeed(maxSpeed);
			cout << "Please enter Maximum Climb Rate" << endl;
			cin >> maxClimbRate;
			jet->setMaxClimbRate(maxClimbRate);
			cout << "Please enter Wing Span" << endl;
			cin >> wingSpan;
			jet->setWingSpan(wingSpan);

			_database.insert(jet);
			cout << "Jet Added" << endl;
		}
		catch(exception excp)
		{
			throw excp;
		}
	}
	else if (userInput == 2)
	{
		try
		{
			//For propeller driven aircraft make a new pointer and call insert function

			PropellerDrivenAircraft* pda = new PropellerDrivenAircraft;

			cout << "Your choice of aircraft have been initialized (PROPELLER DRIVEN AIRCRAFT)" << endl;
			cout << "No space allowed, use underscore instead of spaces" << endl<<endl;
			cout << "Please enter Call Sign" << endl;
			cin >> callSign;
			pda->setCallSign(callSign);
			type = "Propeller Driven Aircraft";
			pda->setType(type);
			cout << "Please enter Serial Number" << endl;
			cin >> serialNumber;
			pda->setSerialNumber(serialNumber);
			cout << "Please enter Owner's Name" << endl;
			cin >> ownerName;
			pda->setOwnerName(ownerName);
			cout << "Please enter Manufacturer's Name" << endl;
			cin >> manufacturer; 
			pda->setManufacturer(manufacturer);
			cout << "Please enter Minimum Speed" << endl;
			cout << "Please enter Production Date (ddmmyyyy)" << endl;
			cin >> productionDate;
			pda->setProductionDate(productionDate);
			cin >> minSpeed;
			pda->setMinSpeed(minSpeed);
			cout << "Please enter Maximum Speed" << endl;
			cin >> maxSpeed;
			pda->setMaxSpeed(maxSpeed);
			cout << "Please enter Maximum Climb Rate" << endl;
			cin >> maxClimbRate;
			pda->setMaxClimbRate(maxClimbRate);
			cout << "Please enter Wing Span" << endl;
			cin >> wingSpan;
			pda->setWingSpan(wingSpan);

			_database.insert(pda);
			cout << "Propeller Driven Aircraft Added" << endl;
		}
		catch(exception excp)
		{
			throw excp;
		}
	}
	else if (userInput == 3)
	{
		try
		{
			//For glider make a new glider pointer and call insert function

			Glider* glider = new Glider;

			cout << "Your choice of aircraft have been initialized (GLIDER)" << endl;
			cout << "No space allowed, use underscore instead of spaces" << endl<<endl;
			cout << "Please enter Call Sign" << endl;
			cin >> callSign;
			glider->setCallSign(callSign);
			type = "Glider";
			glider->setType(type);
			cout << "Please enter Serial Number" << endl;
			cin >> serialNumber;
			glider->setSerialNumber(serialNumber);
			cout << "Please enter Owner's Name" << endl;
			cin >> ownerName;
			glider->setOwnerName(ownerName);
			cout << "Please enter Manufacturer's Name" << endl;
			cin >> manufacturer; 
			glider->setManufacturer(manufacturer);
			cout << "Please enter Production Date (ddmmyyyy)" << endl;
			cin >> productionDate;
			glider->setProductionDate(productionDate);
			cout << "Please enter Minimum Speed" << endl;
			cin >> minSpeed;
			glider->setMinSpeed(minSpeed);
			cout << "Please enter Maximum Speed" << endl;
			cin >> maxSpeed;
			glider->setMaxSpeed(maxSpeed);
			cout << "Please enter Maximum Climb Rate" << endl;
			cin >> maxClimbRate;
			glider->setMaxClimbRate(maxClimbRate);
			cout << "Please enter Wing Span" << endl;
			cin >> wingSpan;
			glider->setWingSpan(wingSpan);

			_database.insert(glider);
			cout << "Glider Added" << endl;
		}
		catch(exception excp)
		{
			throw excp;
		}
	}
	else if (userInput == 4)
	{
		try
		{
			//For helicopter make a new helicopter pointer and call insert function

			Helicopter* helicopter = new Helicopter;

			cout << "Your choice of aircraft have been initialized (GLIDER)" << endl;
			cout << "No space allowed, use underscore instead of spaces" << endl<<endl;
			cout << "Please enter Call Sign" << endl;
			cin >> callSign;
			helicopter->setCallSign(callSign);
			type = "Helicopter";
			helicopter->setType(type);
			cout << "Please enter Serial Number" << endl;
			cin >> serialNumber;
			helicopter->setSerialNumber(serialNumber);
			cout << "Please enter Owner's Name" << endl;
			cin >> ownerName;
			helicopter->setOwnerName(ownerName);
			cout << "Please enter Manufacturer's Name" << endl;
			cin >> manufacturer; 
			helicopter->setManufacturer(manufacturer);
			cout << "Please enter Production Date (ddmmyyyy)" << endl;
			cin >> productionDate;
			helicopter->setProductionDate(productionDate);
			cout << "Please enter Minimum Speed" << endl;
			cin >> minSpeed;
			helicopter->setMinSpeed(minSpeed);
			cout << "Please enter Maximum Speed" << endl;
			cin >> maxSpeed;
			helicopter->setMaxSpeed(maxSpeed);
			cout << "Please enter Maximum Climb Rate" << endl;
			cin >> maxClimbRate;
			helicopter->setMaxClimbRate(maxClimbRate);
			cout << "Please enter Rotor Diameter" << endl;
			cin >> rotorDiameter;
			helicopter->setRotorDiameter(rotorDiameter);
			cout << "Please enter No Of Rotor Blades" << endl;
			cin >> rotorBlades;
			helicopter->setNoOfRotorBlades(rotorBlades);

			_database.insert(helicopter);
			cout << "Helicopter Added" << endl;
		}
		catch(exception excp)
		{
			throw excp;
		}
	}
	else if(userInput == 9)
	{
		cout << "Back to main menu" << endl;
	}
	else 
	{
		cout << "invalid key" << endl;
	}
}


void Global::_search(int enteredCallSign)
{
	//make a temporary aircraft pointer
	Aircraft* temp = new Aircraft;

	//call search function and store the node in temp
	temp = _database.search(enteredCallSign);
	
	//display search result
	try
	{
		if(temp->getType() == "Jet" || temp->getType() == " Glider" || temp->getType() == "Propeller Driven Aircraft")
		{

			FixedWing* FWtemp = new FixedWing;
			FWtemp = (FixedWing*)_database.search(enteredCallSign);

			cout << "Call Sign:" << FWtemp->getCallSign() << endl;
			cout << "Aircraft type: "<<FWtemp->getType() << endl;
			cout << "Serial Number: " << FWtemp->getSerialNumber() << endl;
			cout << "Owner's Name: " <<FWtemp->getOwnerName() << endl;
			cout << "Manufacturer: " <<FWtemp->getManufacturer() << endl;
			cout << "Production Date:  " << FWtemp->getProductionDate() << endl;
			cout << "Minimum Speed:  " << FWtemp->getMinSpeed() << endl;
			cout << "Maximum Speed: " <<FWtemp->getMaxSpeed() << endl;
			cout << "Maximum Climb Rate:  " << FWtemp->getMaxClimbRate() << endl;
			cout << "Wing Span:  " << FWtemp->getWingSpan() << endl << endl;	
		}

		else if(temp->getType()=="Helicopter")
		{
			Helicopter* HeliTemp = new Helicopter;
			HeliTemp = (Helicopter*)_database.search(enteredCallSign);

			cout << "Call Sign:" << HeliTemp->getCallSign() << endl;
			cout << "Aircraft type: "<< HeliTemp->getType() << endl;
			cout << "Serial Number: " << HeliTemp->getSerialNumber() << endl;
			cout << "Owner's Name: " << HeliTemp->getOwnerName() << endl;
			cout << "Manufacturer: " << HeliTemp->getManufacturer() << endl;
			cout << "Production Date:  " << HeliTemp->getProductionDate() << endl;
			cout << "Minimum Speed:  " << HeliTemp->getMinSpeed() << endl;
			cout << "Maximum Speed: " << HeliTemp->getMaxSpeed() << endl;
			cout << "Maximum Climb Rate:  " << HeliTemp->getMaxClimbRate() << endl;
			cout << "Rotor Diameter:  " << HeliTemp->getRotorDiameter() << endl ;
			cout << "Number of Rotor Blades: " << HeliTemp->getNoOfRotorBlades() << endl;
		}
	}
	catch(exception excp)
	{
		throw excp;
	}
}


void Global::_browse()
{
	//make a vector to store all aircrafts
	vector<Aircraft*> getAllAircraft = _database.vectorConversion();

	//iterate through the vector and display everything 
	for( unsigned int airIdx = 0; airIdx < getAllAircraft.size(); airIdx++ )
	{
		cout << "   Call Sign : " << getAllAircraft[airIdx]->getCallSign() << "\n" << "   Type : " << getAllAircraft[airIdx]->getType() << "\n" 
			<< "   Serial Number : " << getAllAircraft[airIdx]->getSerialNumber() << "\n" << "   Owner Name : "<< getAllAircraft[airIdx]->getOwnerName() 
			<< "\n" << "   Manufacturer : "<< getAllAircraft[airIdx]->getManufacturer() << "\n" << "   Production Date : " << getAllAircraft[airIdx]->getProductionDate() 
			<< "\n" << "   Min Speed : " << getAllAircraft[airIdx]->getMinSpeed() << "\n" << "   Max Speed : " << getAllAircraft[airIdx]->getMaxSpeed() << "\n" 
			<< "   Max Climb Rate : "<< getAllAircraft[airIdx]->getMaxClimbRate() << "\n" ;
				
		if (getAllAircraft[airIdx]->getType()=="Jet" || 
			getAllAircraft[airIdx]->getType()== "Glider" || 
			getAllAircraft[airIdx]->getType() == "Propeller Driven Aircraft")
		{
			cout<< "   Wing Span : " << ((FixedWing*)getAllAircraft[airIdx])->getWingSpan()<<"\n" << endl;
		}
				
		else if(getAllAircraft[airIdx]->getType()=="Helicopter")
		{
			cout << "   Rotor Diameter : "<< ((Helicopter*)getAllAircraft[airIdx])->getRotorDiameter()<<"\n" 
				<< "   No Of Rotor Blades : " << ((Helicopter*)getAllAircraft[airIdx])->getNoOfRotorBlades()<<"\n" << endl;
		}
	}
}


void Global::_edit(int enteredCallSign)
{
	//variables to store aircraft specific values
	string type = "";
	int callSign = 0;
	int serialNumber = 0;
	string ownerName = "";
	string productionDate = "";
	string manufacturer= "";
	int minSpeed = 0;
	int maxSpeed = 0;
	int maxClimbRate = 0;
	int rotorDiameter = 0;
	int rotorBlades = 0;
	int wingSpan = 0;

	//make an aircraft pointer
	Aircraft* temp = new Aircraft;

	//call search to find the aircraft
	temp = _database.search(enteredCallSign);


	//this bit is similar to add function
	try
	{
		if(temp->getType() == "Jet" || temp->getType() == " Glider" || temp->getType() == "Propeller Driven Aircraft")
		{
			FixedWing* FWtemp = new FixedWing;
			FWtemp = (FixedWing*)_database.search(enteredCallSign);
		
			int editChoice = 0; //variable to keep track of user input for edit options

			cout << "Select a fixed wing Aircraft Type:\n 1 - JET\n 2 - PROPELLER DRIVEN AIRCRAFT\n 3 - GLIDER\n "<<endl;
			cin >> editChoice ;

			if (editChoice == 1)
			{
				type = "Jet";
				FWtemp->setType(type);
				cout << "No space allowed, use underscore instead of spaces" << endl <<endl;
				cout << "Current Serial No: "<< FWtemp->getSerialNumber() << "\nEnter a New Serial Number: "<<endl;
				cin >> serialNumber;
				FWtemp->setSerialNumber(serialNumber);
				cout << "Current Owner Name: "<< FWtemp->getOwnerName() << "\nEnter a New Owner's Name: " <<endl;
				cin >> ownerName;
				FWtemp->setOwnerName(ownerName);
				cout << "Current Manufacturer: "<< FWtemp->getManufacturer() << "\nEnter a New Manufacturer: " <<endl;
				cin >> manufacturer; 
				FWtemp->setManufacturer(manufacturer);
				cout << "Current Production Date: "<< FWtemp->getProductionDate() << "\nEnter a New Production Date (ddmmyyyy):  " <<endl;
				cin >> productionDate;
				FWtemp->setProductionDate(productionDate);
				cout << "Current Minimum Speed: "<< FWtemp->getMinSpeed() << "\nEnter a New Minimum Speed: " <<endl;
				cin >> minSpeed;
				FWtemp->setMinSpeed(minSpeed);
				cout << "Current Maximum Speed: "<< FWtemp->getMaxSpeed() << "\nEnter a New Maximum Speed: " <<endl;
				cin >> maxSpeed;
				FWtemp->setMaxSpeed(maxSpeed);
				cout << "Current Maximum ClimbRate: "<< FWtemp->getMaxClimbRate() << "\nEnter a New Maximum Climb Rate:  " <<endl;
				cin >> maxClimbRate;
				FWtemp->setMaxClimbRate(maxClimbRate);
				cout << "Current Wing Span: "<< FWtemp->getWingSpan() << "\nEnter a New Wing Span:  " <<endl;
				cin >> wingSpan;
				FWtemp->setWingSpan(wingSpan);

				cout << "Jet Edited" << endl;
			}
			else if (editChoice == 2)
			{
				type = "Propeller Driven Aircraft";
				FWtemp->setType(type);
				cout << "No space allowed, use underscore instead of spaces" << endl<<endl;
				cout << "Current Serial No: "<< FWtemp->getSerialNumber() << "\nEnter a New Serial Number: "<<endl;
				cin >> serialNumber;
				FWtemp->setSerialNumber(serialNumber);
				cout << "Current Owner Name: "<< FWtemp->getOwnerName() << "\nEnter a New Owner's Name: " <<endl;
				cin >> ownerName;
				FWtemp->setOwnerName(ownerName);
				cout << "Current Manufacturer: "<< FWtemp->getManufacturer() << "\nEnter a New Manufacturer: " <<endl;
				cin >> manufacturer; 
				FWtemp->setManufacturer(manufacturer);
				cout << "Current Production Date: "<< FWtemp->getProductionDate() << "\nEnter a New Production Date (ddmmyyyy):  " <<endl;
				cin >> productionDate;
				FWtemp->setProductionDate(productionDate);
				cout << "Current Minimum Speed: "<< FWtemp->getMinSpeed() << "\nEnter a New Minimum Speed: " <<endl;
				cin >> minSpeed;
				FWtemp->setMinSpeed(minSpeed);
				cout << "Current Maximum Speed: "<< FWtemp->getMaxSpeed() << "\nEnter a New Maximum Speed: " <<endl;
				cin >> maxSpeed;
				FWtemp->setMaxSpeed(maxSpeed);
				cout << "Current Maximum ClimbRate: "<< FWtemp->getMaxClimbRate() << "\nEnter a New Maximum Climb Rate:  " <<endl;
				cin >> maxClimbRate;
				FWtemp->setMaxClimbRate(maxClimbRate);
				cout << "Current Wing Span: "<< FWtemp->getWingSpan() << "\nEnter a New Wing Span:  " <<endl;
				cin >> wingSpan;
				FWtemp->setWingSpan(wingSpan);

				cout << "Propeller Driven Aircraft Edited" << endl;
			}
			else if (editChoice == 3)
			{			
				type = "Glider";
				FWtemp->setType(type);
				cout << "No space allowed, use underscore instead of spaces" << endl<<endl;
				cout << "Current Serial No: "<< FWtemp->getSerialNumber() << "\nEnter a New Serial Number: "<<endl;
				cin >> serialNumber;
				FWtemp->setSerialNumber(serialNumber);
				cout << "Current Owner Name: "<< FWtemp->getOwnerName() << "\nEnter a New Owner's Name: " <<endl;
				cin >> ownerName;
				FWtemp->setOwnerName(ownerName);
				cout << "Current Manufacturer: "<< FWtemp->getManufacturer() << "\nEnter a New Manufacturer: " <<endl;
				cin >> manufacturer; 
				FWtemp->setManufacturer(manufacturer);
				cout << "Current Production Date: "<< FWtemp->getProductionDate() << "\nEnter a New Production Date (ddmmyyyy):  " <<endl;
				cin >> productionDate;
				FWtemp->setProductionDate(productionDate);
				cout << "Current Minimum Speed: "<< FWtemp->getMinSpeed() << "\nEnter a New Minimum Speed: " <<endl;
				cin >> minSpeed;
				FWtemp->setMinSpeed(minSpeed);
				cout << "Current Maximum Speed: "<< FWtemp->getMaxSpeed() << "\nEnter a New Maximum Speed: " <<endl;
				cin >> maxSpeed;
				FWtemp->setMaxSpeed(maxSpeed);
				cout << "Current Maximum ClimbRate: "<< FWtemp->getMaxClimbRate() << "\nEnter a New Maximum Climb Rate:  " <<endl;
				cin >> maxClimbRate;
				FWtemp->setMaxClimbRate(maxClimbRate);
				cout << "Current Wing Span: "<< FWtemp->getWingSpan() << "\nEnter a New Wing Span:  " <<endl;
				cin >> wingSpan;
				FWtemp->setWingSpan(wingSpan);

				cout << "Glider Edited" << endl;				
			}
		}
		else if(temp->getType()=="Helicopter")
		{
			Helicopter* HeliTemp = new Helicopter;
			HeliTemp = (Helicopter*)_database.search(enteredCallSign);
			type = "Helicopter";
			HeliTemp->setType(type);
			cout << "No space allowed, use underscore instead of spaces" << endl<<endl;
			cout << "Current Serial No : "<< HeliTemp->getSerialNumber() << "\nEnter a new Serial Number: " << endl;
			cin >> serialNumber;
			HeliTemp->setSerialNumber(serialNumber);
			cout << "Current Owner Name : " <<  HeliTemp->getOwnerName()<< " \nEnter a new Owner's Name: " << endl;
			cin >> ownerName;
			HeliTemp->setOwnerName(ownerName);
			cout << "Current Manufacturer: " <<  HeliTemp->getManufacturer() << "\nEnter a New Manufacturer:" << endl;
			cin >> manufacturer; 
			HeliTemp->setManufacturer(manufacturer);
			cout << "Current Production Date:  " <<  HeliTemp->getProductionDate() << "\nEnter a New Production Date (ddmmyyyy):" << endl;
			cin >> productionDate;
			HeliTemp->setProductionDate(productionDate);
			cout << "Current Minimum Speed: "<< HeliTemp->getMinSpeed() << "\nEnter a New Minimum Speed:" << endl;
			cin >> minSpeed;
			HeliTemp->setMinSpeed(minSpeed);
			cout << "Current Maximum Speed: " << HeliTemp->getMaxSpeed() << "\nEnter a New Maximum Speed:" <<endl;
			cin >> maxSpeed;
			HeliTemp->setMaxSpeed(maxSpeed);
			cout << "Current Maximum Climb Rate:  " << HeliTemp->getMaxClimbRate() << "\nEnter a New Maximum Climb Rate: " <<endl;
			cin >> maxClimbRate;
			HeliTemp->setMaxClimbRate(maxClimbRate);
			cout << "Current Rotor Diameter:  " << HeliTemp->getRotorDiameter()<<"\nEnter a New Rotor Diameter:  " <<  endl ;
			cin >> rotorDiameter;
			HeliTemp->setRotorDiameter(rotorDiameter);
			cout << "Current Number of Rotor Blades: " <<HeliTemp->getNoOfRotorBlades() << "\nEnter a New Number of Rotor Blades: " << endl;
			cin >> rotorBlades;
			HeliTemp->setNoOfRotorBlades(rotorBlades);

			cout << "Helicopter Edited" << endl;
		}
	}
	catch (exception excp)
	{
		throw excp;
	}
}
