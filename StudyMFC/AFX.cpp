// AFX.cpp: implementation of the CAFX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AFX.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BOOL CRuntimeClass::IsDerivedFrom(const CRuntimeClass* pBaseClass) const
{
	// simple SI case
	// 运行时的类信息在程序运行过程中，有且只有一个，在查找是否是某一个类派生出来的时候
	// 其结构是一个单向树而已，因此只需要由叶子节点向根节点查找即可
	const CRuntimeClass* pClassThis = this;
	while (pClassThis != NULL)
	{
		if (pClassThis == pBaseClass)
			return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;       // walked to the top, no match
}
