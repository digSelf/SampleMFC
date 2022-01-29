// CmdTarget.h: interface for the CCmdTarget class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMDTARGET_H__F5367F78_FEF0_40AF_8551_70D9127A1B16__INCLUDED_)
#define AFX_CMDTARGET_H__F5367F78_FEF0_40AF_8551_70D9127A1B16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"

class CCmdTarget : public CObject  
{
	DECLARE_DYNAMIC(CCmdTarget);
public:
	CCmdTarget();
	virtual ~CCmdTarget();

};

#endif // !defined(AFX_CMDTARGET_H__F5367F78_FEF0_40AF_8551_70D9127A1B16__INCLUDED_)
