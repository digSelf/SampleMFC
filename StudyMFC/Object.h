// Object.h: interface for the CObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_H__1737FE8D_955D_4B18_BF09_B61CEF250566__INCLUDED_)
#define AFX_OBJECT_H__1737FE8D_955D_4B18_BF09_B61CEF250566__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CObject  
{
	DECLARE_DYNAMIC(CObject)
public:
	CObject();
	virtual ~CObject();

public:
	// 判断该对象是否是由指定类的子类对象，由于参数是运行时的类信息，在调用时需要如：RUNTIME_CLASS(class_name)的形式调用
	// IsKindOf函数不是虚函数，是定义在CObject类中的一个public型的成员函数，只要继承自CObject类的子类都可以直接调用
	// 为什么不是虚函数呢？因为不需要根据对象类型去调用自身的，而且每一个派生自CObject类的都可以调用该函数，因此这么设计
	BOOL IsKindOf(const CRuntimeClass* pClass) const;
};

#endif // !defined(AFX_OBJECT_H__1737FE8D_955D_4B18_BF09_B61CEF250566__INCLUDED_)
