// WinThread.cpp: implementation of the CWinThread class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WinThread.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinThread::CWinThread()
{
	m_pCurrentWinThread = this;
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
