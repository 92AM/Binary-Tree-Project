	//PROGRAMMERS		: Arka Mitra (N0388235) & Kok Khong Thomas Cheong (N0382624)
	//SYSTEM NAME		: Aircraft Database System For Ministry Of Defense
	//MODULE CODE		: SOFT20091
	//MODULE TITLE		: Software Design and Implementation 2
	//MODULE LEADER		: Dr Lars Nolle

#include "Main.h"
#include "Global.h"
#include "BinaryTree.h"

//Client side
void main()
{
	Global global;		//make instance of Global class

	global.setupConsole();		//setup console

	global.run();		//call run function of Global class
}