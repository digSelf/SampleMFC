// UserApp.cpp: implementation of the CUserApp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UserApp.h"

// 定义在用户应用程序类中CUserApp
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

IMPLEMENT_DYNAMIC(CUserApp, CWinApp)

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
