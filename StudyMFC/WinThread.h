// WinThread.h: interface for the CWinThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINTHREAD_H__EC21044F_4841_48FF_BE3D_23B78E112100__INCLUDED_)
#define AFX_WINTHREAD_H__EC21044F_4841_48FF_BE3D_23B78E112100__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdTarget.h"


class CWinThread : public CCmdTarget
{
	DECLARE_DYNAMIC(CWinThread)
public:
	CWinThread *m_pCurrentWinThread;
public:
	virtual int Run();
	virtual BOOL InitInstance();
	CWinThread();
	virtual ~CWinThread();

};



#endif // !defined(AFX_WINTHREAD_H__EC21044F_4841_48FF_BE3D_23B78E112100__INCLUDED_)
