#pragma once

#include <iostream>
#include <windows.h>
#include <exception>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//  error messages for exception handling
#define DUPLICATE_CALLSIGN "Error x082642 : This Call Sign already exists!"
#define AIRCRAFT_NOT_FOUND "Error x046683 : Aircraft was not found!"
#define NO_AIRCRAFT "Error x045767 : There are no aircrafts!"
#define NO_TEXT_FILE "Error x045653 : An error was encountered while trying to load aircraft.txt!"

#define AIRCRAFT_SAVED "Data saved!"