#include "LeapListener.h"


/*
* Handle the initialization when our controller 
* is plugged in. Here need to make sure to
* enable the gestures that we want to recognize.
*/
void LeapListener::onConnect(const Controller & controller) {
	std::cout<< "Leap Controller Connected" << std::endl;

	// Currently the Leap Motion has support for four gestures
	// - Circle
	// - Swipe
	// - Screen Tap
	// - Key Tap 
	// For more information on each gesture I recommend taking
	// a look at their API Overview: 
	// https://developer.leapmotion.com/documentation/cpp/devguide/Leap_Overview.html

	// In order to use gestures we must first enable the 
	// recognition for each gesture we want in our app. 
	// We are going to be using 3 gestures here: 
	// - Circle and Swipe
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_SWIPE);

	// Initialize the use of COM objects...
	CoInitialize(NULL);
 
	// Create a Shell object pointer...
	_pShell = NULL;
	_hr = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_SERVER, IID_IDispatch, (void**)&_pShell);
	_bMinimized = false;

	
}

/*
* On every frame explore the recognized gestures.
* If we recognize a SWIPE then minimize all windows.
* If we recognize a CIRCLE then restore all windows that 
* were minimized.
*/
void LeapListener::onFrame(const Controller & controller) {
	Frame currFrame = controller.frame();
	
	GestureList currGestures = currFrame.gestures();
	std::cout<< "Frame Available" << std::endl;
	
	bool gestureHandled = false;

	// Go through the list of gestures in this frame and
	// only handle the first gesture that matches one of our
	// expected gestures and ignore the rest.
	for(GestureList::const_iterator gl = currGestures.begin(); gl != currGestures.end() && !gestureHandled
		; gl++)
	{
		Gesture tempGest = (*gl);

		if(tempGest.isValid())
		{
			
			switch (tempGest.type())
			{
				case Gesture::TYPE_CIRCLE:
					cout<< "Cicle Gesture Detected" <<endl;
					restoreWindows();
					gestureHandled = true;
				break;
		
				case Gesture::TYPE_SWIPE:
					cout<< "Swipe Gesture Detected" << endl;
					minimizeWindows();
					gestureHandled = true;
					break;

				default:
					cout<< "Gesture not Recognized" <<endl;
					break;
			}
		}
	}
	
}

/*
* Release any and all resources allocated when 
* the controller was connected so we don't leak
* any memory.
*/
void LeapListener::onDisconnect(const Controller & controller) 
{
	std::cout<< "Leap Controller Disconnected" << std::endl;

	if (SUCCEEDED(_hr)) 
	{
		// Release the COM object when we're finished...
		_pShell->Release();
		CoUninitialize();
	}

}

/*
* Attempts to minimize all windows. 
*/ 
void LeapListener::minimizeWindows() 
{
	if (SUCCEEDED(_hr) && !_bMinimized)
	{
		// Call minimize all windows.
		_pShell->MinimizeAll();
		_bMinimized = true;
	}
}

/*
* Attempts to restore all previously minimized 
* windows.
*/
void LeapListener::restoreWindows() 
{
	if (SUCCEEDED(_hr) && _bMinimized)
	{
		cout<< "Restoring Desktop" << endl;
		// Restore all minimized windows.
		_pShell->UndoMinimizeALL();
		_bMinimized = false;
	}
}
