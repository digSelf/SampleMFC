// UserApp.cpp: implementation of the CUserApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserApp.h"

// �������û�Ӧ�ó�������CUserApp
CUserApp theApp;

CWinApp* AFXAPI AfxGetApp()
{
	return theApp.m_pCurrentWinApp;
}

CWinThread* AFXAPI AfxGetThread()
{
	return theApp.m_pCurrentWinThread;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_RUNTIMECLASS(CUserApp, CWinApp, 0, NULL)

CUserApp::CUserApp()
{

}

CUserApp::~CUserApp()
{

}

BOOL CUserApp::InitInstance()
{
	MessageBoxA(NULL, "CUserApp::InitInstance", NULL, MB_OK);
	return TRUE;
}
