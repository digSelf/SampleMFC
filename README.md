# SampleMFC
在XP XP3下，搭建一个学习用的MFC简易框架，以了解其原理

# RTTI动态类型识别

由于需要实现对象的序列化和范序列化，那么就需要能够识别序列化后的对象的类型及能够动态创建，因此，首先需要做的就是先做到动态类型识别。

想法：通过保存类名和识别类名，就能够实现对某一个类对象的类型识别了。

`struct CRuntimeClass`保存类型的信息，由于每个类都需要固定添加如以下形式的信息：
```cpp
// .h
public: 
	static const CRuntimeClass classCObject; 
	virtual CRuntimeClass* GetRuntimeClass() const; 

// .cpp
const CRuntimeClass CObject::classCObject 
	 = { "CObject", sizeof(class CObject), 0, NULL, NULL, NULL };

CRuntimeClass* CObject::GetRuntimeClass() const
{ 
	// return (CRuntimeClass*)(&CObject::classCObject); 
	return RUNTIME_CLASS(CObject);
} 
```
因此定义了几个工具宏：
```cpp
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
```
在使用时，只需要在`.h`文件中，添加`DECLARE_DYNAMIC(class_name)`语句；在`.cpp`文件中添加`IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, wSchema, pfnNew)`
信息，就可以实现动态类型识别了。

对于每个类，都需要`IsKindOf`函数来识别某一个类是否是由另一个类派生出来的，且不需要每个类定义自己专有的类型识别函数，因此将其定义在`CObject`类中且作为普通成员
函数即可：
```cpp

// CObject.h -> BOOL IsKindOf(const CRuntimeClass* pClass) const;
// CObject.cpp
// CRuntimeClass是运行时的类信息结构体
BOOL CObject::IsKindOf(const CRuntimeClass* pClass) const
{
	// simple SI case
	// GetRuntimeClass是虚函数
	CRuntimeClass* pClassThis = GetRuntimeClass();
	return pClassThis->IsDerivedFrom(pClass);
}

```
由于每个类中的`CRuntimeClass`信息是静态变量，在整个程序的运行中有且仅有一份，是唯一的，因此`IsDerivedFrom`定义运行时的类信息结构体中。具体实现如下：
```cpp
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
```
由于运行时类信息是唯一的，因此可以通过查找单向树并直接比较运行时类对象指针即可判断是否是由该类派生出来的完成动态类型识别。

# 动态创建

想要的效果是：`CreateObject(class_name)`就能返回对应类型的类对象指针。本项目版本的调用方式是：
```cpp
CRuntimeClass *pInfoClass = CRuntimeClass::Load(szClassName);
ClassName *pClass = (ClassName *)*pInfoClass->CreateObject();
```

## 构建注册类的运行时信息单链表

在MFC中使用的是一个类外加一个`SimpleList`来进行管理，本项目为了结构简单及代码简洁，使用的是静态成员，在执行`WinMain`函数之前，构建一个
静态的单链表。

```cpp
struct CRuntimeClass
{
	// Attributes
	LPCSTR m_lpszClassName;
	int m_nObjectSize;
	UINT m_wSchema; // schema number of the loaded class
	CObject* (PASCAL* m_pfnCreateObject)(); // NULL => abstract class
	CRuntimeClass* m_pBaseClass;
	
	// Operations
	CObject* CreateObject();	// 为了动态创建，与m_pfnCreateObject配合
	BOOL IsDerivedFrom(const CRuntimeClass* pBaseClass) const;
	
	// Implementation		// 根据所给类名，返回对应的类运行时信息
	static CRuntimeClass* PASCAL Load(LPCSTR lpszClassName);
	
	// CRuntimeClass objects linked together in simple list
	CRuntimeClass* m_pNextClass;       // linked list of registered classes

	// 添加静态数据成员，由于其优先于WinMain函数执行前进行初始化，因此可以在WinMain前就构造好一条单链表
	// 与m_pNextClass进行配合构成一个已经注册了类的单链表，用以动态类型创建
	// 但是需要注意，取消掉之前动态类型识别时使用的const限制，最好是自己构造一个单向链表类和一个管理该链表的对象来做
	static CRuntimeClass *m_pHeadNode;		// 这里是添加的单链表的头结点
};

```
为了配合在程序初始化时，构建单链表，引入`AFX_CLASSINIT`结构体：
```cpp
void AFXAPI AfxClassInit(CRuntimeClass* pNewClass);
struct AFX_CLASSINIT
{ 
	AFX_CLASSINIT(CRuntimeClass* pNewClass) 
	{ 
		AfxClassInit(pNewClass); 
	} 
};

void AFXAPI AfxClassInit(CRuntimeClass* pNewClass)
{
	// 构建单链表
	pNewClass->m_pNextClass = CRuntimeClass::m_pHeadNode->m_pNextClass;
	CRuntimeClass::m_pHeadNode->m_pNextClass = pNewClass;
}
```
以及在`IMPLEMENT_RUNTIMECLASS`宏中添加全局函数`AFX_CLASSINIT _init_##class_name(RUNTIME_CLASS(class_name));`。由于全局函数和静态
函数优先初始化，因此在执行`WinMain`函数之前，就已经建立好了类运行时信息结构的单链表了

## 根据类名查找对应的类的运行时信息
根据所给类名，查找单链表，如果有则返回对应的唯一的运行时信息，如果没有找到则返回NULL
```cpp
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
```

### 动态创建类对象

根据类运行时信息中存放的创建对象的指针，可以让类本身自己创建对象（工厂设计模式）
```cpp
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
		pObject = (*m_pfnCreateObject)();	// 调用所属类自身的工厂方法
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
```
### 动态创建的工具宏

```cpp
// 声明用来动态类型创建的工具宏
#define DECLARE_DYNCREATE(class_name) \
	DECLARE_DYNAMIC(class_name) \
	static CObject* PASCAL CreateObject();			// 新增工厂方法

#define IMPLEMENT_DYNCREATE(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
	{ return new class_name; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \ // 将`pfnNew`初始化为当前类的`CreateObject`函数
		class_name::CreateObject)
```

tip：编译选项中加入`/P`来观察预处理结果，可以看到宏的展开