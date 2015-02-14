/***************************************************
* Hands-On Sample code for Leap Motion. 
* This project shows how to interact with the Leap
* motion controlled and perform some simple 
* operations based on recognized gestures. 
*
* Note: You will need to set up the Leap Motion
* Developer SDK before being able to run this 
* project.
*
* Author: Frank E. Hernandez
* 
***************************************************/
#include <iostream>
#include <string.h>
#include "Leap.h"
#include "LeapListener.h"

using namespace Leap;

int main(int argc, char ** argv)
{
	Controller controller;
	LeapListener listener;

	// All the work will be done by the listener, 
	// so we need to register it.
	controller.addListener(listener);

	// Keep this process running until Enter is pressed
	std::cout << "Press Enter to quit..." << std::endl;
	std::cin.get();

	// Remove the listener once we are done.
	controller.removeListener(listener);

	return 0;


}