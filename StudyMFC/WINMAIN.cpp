// WINMAIN.cpp: implementation of the CWINMAIN class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "WINMAIN.h"
#include "WinThread.h"
#include "WinApp.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int WINAPI AfxWinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	int nReturnCode = -1;
	CWinThread* pThread = AfxGetThread();
	CWinApp* pApp = AfxGetApp();
	
	// App global initializations (rare)
	if (pApp != NULL && !pApp->InitApplication())
		goto InitFailure;
	
	// Perform specific initializations
	if (!pThread->InitInstance())
	{
		goto InitFailure;
	}
	nReturnCode = pThread->Run();

InitFailure:
#ifdef _DEBUG
	if (nReturnCode == -1)
	{
		MessageBoxA(NULL, "Init Failure", NULL, MB_OK);
	}
#endif
	return nReturnCode;
}