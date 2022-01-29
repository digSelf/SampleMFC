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
	// �жϸö����Ƿ�����ָ���������������ڲ���������ʱ������Ϣ���ڵ���ʱ��Ҫ�磺RUNTIME_CLASS(class_name)����ʽ����
	// IsKindOf���������麯�����Ƕ�����CObject���е�һ��public�͵ĳ�Ա������ֻҪ�̳���CObject������඼����ֱ�ӵ���
	// Ϊʲô�����麯���أ���Ϊ����Ҫ���ݶ�������ȥ��������ģ�����ÿһ��������CObject��Ķ����Ե��øú����������ô���
	BOOL IsKindOf(const CRuntimeClass* pClass) const;
};

#endif // !defined(AFX_OBJECT_H__1737FE8D_955D_4B18_BF09_B61CEF250566__INCLUDED_)
