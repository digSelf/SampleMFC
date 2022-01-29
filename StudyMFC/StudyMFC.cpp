// StudyMFC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WINMAIN.h"

#include <tchar.h>

extern "C" 
int WINAPI _tWinMain(HINSTANCE hInstance,      // handle to current instance
					 HINSTANCE hPrevInstance,  // handle to previous instance
					 LPSTR lpCmdLine,          // command line
					 int nCmdShow              // show state
)
{
	return AfxWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
