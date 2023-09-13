#include <windows.h>
#include "AppEngine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	AppEngine appEngine;
	appEngine.start(hInstance, nCmdShow);
	return 0;
}
