// AFX.cpp: implementation of the CAFX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Object.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRuntimeClass* CRuntimeClass::m_pHeadNode = RUNTIME_CLASS(CObject);

void AFXAPI AfxClassInit(CRuntimeClass* pNewClass)
{
	pNewClass->m_pNextClass = CRuntimeClass::m_pHeadNode->m_pNextClass;
	CRuntimeClass::m_pHeadNode->m_pNextClass = pNewClass;
}

int AFXAPI AfxMessageBox(LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
	return MessageBoxA(NULL, lpText, lpCaption, uType);
}

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

CObject* CRuntimeClass::CreateObject()
{
	if (m_pfnCreateObject == NULL)
	{
		char szError[MAXBYTE] = {0};
		sprintf(szError, "Error: Trying to create object which is not \
			DECLARE_DYNCREATE \nor DECLARE_SERIAL: %hs.\n", m_lpszClassName);
		// MessageBoxA(NULL, szError, NULL, MB_OK);
		AfxMessageBox(szError);
		return NULL;
	}
	
	CObject* pObject = NULL;
	try
	{
		pObject = (*m_pfnCreateObject)();
	}
	catch(...)
	{
		DWORD dwError = GetLastError();
		char szError[MAXBYTE] = {0};
		sprintf(szError, "Exception %08x: Create Object Failed.", dwError);
		// MessageBoxA(NULL, szError, NULL, MB_OK);
		AfxMessageBox(szError);
		throw;
	}
		
	return pObject;
}

CRuntimeClass* PASCAL CRuntimeClass::Load(LPCSTR lpszClassName)
{
	for (CRuntimeClass* pClass = CRuntimeClass::m_pHeadNode; 
		 pClass != NULL;
		 pClass = pClass->m_pNextClass)
	{
		if (lstrcmpA(lpszClassName, pClass->m_lpszClassName) == 0)
		{
			return pClass;
		}
	}

	return NULL;
}