// WinApp.h: interface for the CWinApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINAPP_H__307BE8FB_298F_40C0_8CF3_018150202ABF__INCLUDED_)
#define AFX_WINAPP_H__307BE8FB_298F_40C0_8CF3_018150202ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinThread.h"

class CWinApp : public CWinThread  
{
public:
	CWinApp();
	virtual ~CWinApp();
	
	CWinApp *m_pCurrentWinApp;

public:
	virtual int Run();
	virtual BOOL InitInstance();
	virtual BOOL InitApplication();
	
};



#endif // !defined(AFX_WINAPP_H__307BE8FB_298F_40C0_8CF3_018150202ABF__INCLUDED_)
