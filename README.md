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