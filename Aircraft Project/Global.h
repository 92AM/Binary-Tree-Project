#pragma once

//define all libraries required
#include "Main.h"
#include "BinaryTree.h"
#include "Aircraft.h"
#include "Helicopter.h"
#include "FixedWing.h"
#include "Jet.h"
#include "Glider.h"
#include "PropellerDrivenAircraft.h"

using namespace std;

class Global
{
public:

	//constructor
	Global(void);

	//destructor (destroy database i.e. the tree)
	~Global(void);

	//this function calls the private _setupConsole() function
	void setupConsole();

	//this calls the private _run() function
	void run();

private:

	//sets up console's window size
	void _setupConsole();
	
	//this function tackles user interaction
	void _run();

	//use this function for saving to text file 
	void _save(string fileName);

	//use this function for loading from text file
	void _load(string fileName);

	//make instance of binary tree (so taht it can store aircraft) 
	BinaryTree<Aircraft> _database;

	//keeps track in the main while loop, if this changes to false the program will close
	bool _isRunning;

	//add function 
	void _add(int userInput);

	//search function
	void _search(int enteredCallSign);

	//display all aircrafts
	void _browse();

	//edit aircraft
	void _edit(int enteredCallSign);

};

