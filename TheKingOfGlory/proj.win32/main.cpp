#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
//#define USE_WIN32_CONSOLE

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
	AllocConsole(); 
	freopen("CONIN$", "r", stdin);    
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
