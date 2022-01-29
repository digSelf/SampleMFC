// AFX.h: interface for the CAFX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AFX_H__0B495A02_2D1A_443F_A7B2_F8E6C8D44714__INCLUDED_)
#define AFX_AFX_H__0B495A02_2D1A_443F_A7B2_F8E6C8D44714__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObject;
struct CRuntimeClass
{
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class，用于序列化的
	
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
	// 基类类型信息的指针
	CRuntimeClass* m_pBaseClass;
	// CRuntimeClass objects linked together in simple list
	CRuntimeClass* m_pNextClass;       // linked list of registered classes

	// Operation
	BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const;
};

// helper MACRO
#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))
// 声明静态数据成员及虚函数
#define DECLARE_DYNAMIC(class_name) \
public: \
	static const CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const; 

#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
const CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
		RUNTIME_CLASS(base_class_name), NULL }; \
CRuntimeClass* class_name::GetRuntimeClass() const \
	{ return RUNTIME_CLASS(class_name); } \

#endif // !defined(AFX_AFX_H__0B495A02_2D1A_443F_A7B2_F8E6C8D44714__INCLUDED_)
