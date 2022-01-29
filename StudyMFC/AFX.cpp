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
	// ����ʱ������Ϣ�ڳ������й����У�����ֻ��һ�����ڲ����Ƿ���ĳһ��������������ʱ��
	// ��ṹ��һ�����������ѣ����ֻ��Ҫ��Ҷ�ӽڵ�����ڵ���Ҽ���
	const CRuntimeClass* pClassThis = this;
	while (pClassThis != NULL)
	{
		if (pClassThis == pBaseClass)
			return TRUE;
		pClassThis = pClassThis->m_pBaseClass;
	}
	return FALSE;       // walked to the top, no match
}
