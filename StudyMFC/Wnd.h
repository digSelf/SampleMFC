// Wnd.h: interface for the CWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WND_H__26965A63_D695_42D5_86CD_1F12CFEACDC7__INCLUDED_)
#define AFX_WND_H__26965A63_D695_42D5_86CD_1F12CFEACDC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdTarget.h"

class CWnd : public CCmdTarget  
{
	// DECLARE_DYNAMIC(CWnd)
	DECLARE_DYNCREATE(CWnd)
public:
	void SayHi();
	CWnd();
	virtual ~CWnd();
};

#endif // !defined(AFX_WND_H__26965A63_D695_42D5_86CD_1F12CFEACDC7__INCLUDED_)
