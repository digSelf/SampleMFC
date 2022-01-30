// FrameWnd.h: interface for the CFrameWnd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMEWND_H__CF88DD8A_A9FE_4FC6_92BB_7752813B27ED__INCLUDED_)
#define AFX_FRAMEWND_H__CF88DD8A_A9FE_4FC6_92BB_7752813B27ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Wnd.h"

class CFrameWnd : public CWnd  
{
	DECLARE_DYNAMIC(CFrameWnd)
public:
	CFrameWnd();
	virtual ~CFrameWnd();

};

#endif // !defined(AFX_FRAMEWND_H__CF88DD8A_A9FE_4FC6_92BB_7752813B27ED__INCLUDED_)
