// Object.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Object.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// ����CObject���еĸ��࣬��ʱ������RUNTIME_CLASS�����滻����Ϊ������Ҫֱ�Ӹ�NULL��
// ��ʱ�޷�ͳһ��
const CRuntimeClass CObject::classCObject 
	 = { "CObject", sizeof(class CObject), 0, NULL, NULL, NULL };

CRuntimeClass* CObject::GetRuntimeClass() const
{ 
	// return (CRuntimeClass*)(&CObject::classCObject); 
	return RUNTIME_CLASS(CObject);
} 

CObject::CObject()
{
	
}

CObject::~CObject()
{

}

// CRuntimeClass������ʱ������Ϣ�ṹ��
BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	// simple SI case
	// GetRuntimeClass���麯��
	CRuntimeClass* pClassThis = GetRuntimeClass();
	return pClassThis->IsDerivedFrom(pClass);
}