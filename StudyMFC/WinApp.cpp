// WinApp.cpp: implementation of the CWinApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinApp.h"
#include <tchar.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_RUNTIMECLASS(CWinApp, CWinThread, 0, NULL)

CWinApp::CWinApp(LPCTSTR lpszAppName)
{
	if (lpszAppName != NULL)
		m_pszAppName = _tcsdup(lpszAppName);
	else
		m_pszAppName = NULL;

	m_pCurrentWinApp = this;
	m_pCurrentWinThread = this;

	// in non-running state until WinMain
	m_hInstance = NULL;
	m_lpCmdLine = NULL;
}

CWinApp::~CWinApp()
{

}

BOOL CWinApp::InitApplication()
{
	return TRUE;
}

BOOL CWinApp::InitInstance()
{
	MessageBoxA(NULL, "CWinApp::InitInstance", NULL, MB_OK);
	return TRUE;
}

int CWinApp::Run()
{
	return CWinThread::Run();
}
