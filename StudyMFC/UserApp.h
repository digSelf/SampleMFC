// UserApp.h: interface for the CUserApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERAPP_H__C7AC9803_89A8_4926_9173_CB8295D91D4D__INCLUDED_)
#define AFX_USERAPP_H__C7AC9803_89A8_4926_9173_CB8295D91D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WinApp.h"
#include "WinThread.h"

class CUserApp : public CWinApp  
{
	DECLARE_DYNAMIC(CUserApp)
public:
	virtual BOOL InitInstance();
	CUserApp();
	virtual ~CUserApp();
};

// CWinApp* AFXAPI AfxGetApp();
// CWinThread* AFXAPI AfxGetThread();
#endif // !defined(AFX_USERAPP_H__C7AC9803_89A8_4926_9173_CB8295D91D4D__INCLUDED_)
