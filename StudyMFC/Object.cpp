// Object.cpp: implementation of the CObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Object.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// 对于CObject类中的父类，暂时不能用RUNTIME_CLASS宏来替换，因为父类是要直接给NULL的
// 暂时无法统一的
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

// CRuntimeClass是运行时的类信息结构体
BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	// simple SI case
	// GetRuntimeClass是虚函数
	CRuntimeClass* pClassThis = GetRuntimeClass();
	return pClassThis->IsDerivedFrom(pClass);
}