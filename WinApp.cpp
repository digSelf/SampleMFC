// WinApp.cpp: implementation of the CWinApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinApp.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinApp::CWinApp()
{
	m_pCurrentWinApp = this;
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
