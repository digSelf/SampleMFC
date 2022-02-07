// AFX.h: interface for the CAFX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AFX_H__0B495A02_2D1A_443F_A7B2_F8E6C8D44714__INCLUDED_)
#define AFX_AFX_H__0B495A02_2D1A_443F_A7B2_F8E6C8D44714__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef AFXAPI
#define AFXAPI __stdcall
#endif

class CObject;
class CWinApp;
class CWinThread;

CWinApp* AFXAPI AfxGetApp();
CWinThread* AFXAPI AfxGetThread();
int AFXAPI AfxMessageBox(LPCSTR lpText, LPCSTR lpCaption=NULL, UINT uType=MB_OK);

struct CRuntimeClass
{
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
	CRuntimeClass* m_pBaseClass;
	
	// Operations
	CObject* CreateObject();
	BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const;
	
	// Implementation
// 	void Store(CArchive& ar) const;
// 	static CRuntimeClass* PASCAL Load(CArchive& ar, UINT* pwSchemaNum);
	static CRuntimeClass* PASCAL Load(LPCSTR lpszClassName);

	// ��Ӿ�̬���ݳ�Ա��������������WinMain����ִ��ǰ���г�ʼ������˿�����WinMainǰ�͹����һ��������
	// ��m_pNextClass������Ϲ���һ���Ѿ�ע������ĵ��������Զ�̬���ʹ���
	// ������Ҫע�⣬ȡ����֮ǰ��̬����ʶ��ʱʹ�õ�const���ƣ�������Լ�����һ�������������һ�����������Ķ�������
	// CRuntimeClass objects linked together in simple list
	CRuntimeClass* m_pNextClass;       // linked list of registered classes
	static CRuntimeClass *m_pHeadNode;
};

// helper MACRO
#define RUNTIME_CLASS(class_name) ((CRuntimeClass*)(&class_name::class##class_name))\

// ����������̬����ʶ��ľ�̬���ݳ�Ա���麯��
#define DECLARE_DYNAMIC(class_name) \
public: \
	static CRuntimeClass class##class_name; \
	virtual CRuntimeClass* GetRuntimeClass() const; 


#define IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew) \
	CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
		RUNTIME_CLASS(base_class_name), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); } \
	AFX_CLASSINIT _init_##class_name(RUNTIME_CLASS(class_name)); 

#define IMPLEMENT_DYNAMIC(class_name, base_class_name) \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, NULL)

// ����������̬���ʹ����Ĺ��ߺ�
#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();			// Ϊÿһ���඼�����һ����̬�ĳ�Ա����

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
	{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)

// generate static object constructor for class registration
void AFXAPI AfxClassInit(CRuntimeClass* pNewClass);
struct AFX_CLASSINIT
{ 
	AFX_CLASSINIT(CRuntimeClass* pNewClass) 
	{ 
		AfxClassInit(pNewClass); 
	} 
};

#endif // !defined(AFX_AFX_H__0B495A02_2D1A_443F_A7B2_F8E6C8D44714__INCLUDED_)
