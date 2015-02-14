#include "Leap.h"

#include <windows.h>
#include <shlobj.h>
#include <exdisp.h>
#include <stdio.h>

using namespace Leap;
using namespace std;

class LeapListener: public Listener {
	public:
		// Will be called when the Leap Motion Controlled is Connected.
		virtual void onConnect(const Controller&);
		// Called on every frame, good place to perform our control logic.
		virtual void onFrame(const Controller&);
		// Will ve called when the Leap Motion Controller is Disconnected.
		virtual void onDisconnect(const Controller &);

	private:
		IShellDispatch* _pShell;
		HRESULT _hr ;
		bool _bMinimized; 
		void restoreWindows();
		void minimizeWindows();
		

};
