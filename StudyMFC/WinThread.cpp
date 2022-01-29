// WinThread.cpp: implementation of the CWinThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinThread.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_RUNTIMECLASS(CWinThread, CCmdTarget, 0, NULL)

CWinThread::CWinThread()
{
	// m_pCurrentWinThread = this;
}

CWinThread::~CWinThread()
{

}

BOOL CWinThread::InitInstance()
{
	MessageBoxA(NULL, "CWinThread::InitInstance", NULL, MB_OK);
	return TRUE;
}

int CWinThread::Run()
{
	return 0;
}
