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
	// ����Ӧ�ó�����һ��ʵ�壬Ӧ�ó���ʵ���ʼ����Ϻ󣬲ſ�ʼ��ʼ�����߳�
	if (pApp != NULL && !pApp->InitApplication())
		goto InitFailure;
	
	// Perform specific initializations
	// ������Ӧ�ó��� or ���̣���ʼ����Ϻ��ٿ�ʼ��ʼ���߳�ʵ��
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