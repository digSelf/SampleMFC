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

	pApp->IsKindOf(RUNTIME_CLASS(CObject));
	
	// App global initializations (rare)
	// 整个应用程序看作一个实体，应用程序实体初始化完毕后，才开始初始化主线程
	if (pApp != NULL && !pApp->InitApplication())
		goto InitFailure;
	
	// Perform specific initializations
	// 容器（应用程序 or 进程）初始化完毕后，再开始初始化线程实例
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