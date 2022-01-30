// WINMAIN.cpp: implementation of the CWINMAIN class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "WINMAIN.h"
#include "WinThread.h"
#include "WinApp.h"

//////////////////////////////////////////////////////////////////////
// MFC测试程序
//////////////////////////////////////////////////////////////////////
#include "Wnd.h"

void TestMFC()
{
	// 测试动态类型识别
	// AfxGetApp()->IsKindOf(RUNTIME_CLASS(CObject));

	// 测试动态类型创建功能
	CRuntimeClass *pWndInfoClass = CRuntimeClass::Load("CWnd");
	CWnd *pWnd = (CWnd *)pWndInfoClass->CreateObject();
	pWnd->SayHi();
}

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

	TestMFC();

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