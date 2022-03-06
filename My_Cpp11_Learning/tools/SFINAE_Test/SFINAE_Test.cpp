#include <iostream>
#include "CheckClassMethod.hpp"
using namespace std;

class A
{
public:
	const char* ToString() const
	{ 
		return "This is Class A";
	}
};

struct B
{
};

template<bool>
struct AnyToStringAdviser;

template<>
struct AnyToStringAdviser<true>
{
	template<typename ClassType>
	static const char* ToString(const ClassType& ct)
	{
		return ct.ToString();
	}
};

template<>
struct AnyToStringAdviser<false>
{
	template<typename ClassType>
	static const char* ToString(const ClassType& ct)
	{
		/* Generic process */
		return typeid(ct).name();
	}
};

//ͨ�ú�����ʵ���������͵�����ת���ַ���
template<typename ClassType>
const char* AnyToString(const ClassType& ct)
{
	return AnyToStringAdviser
		<
		HasToStringFunction<ClassType>::Value
		>
		::ToString(ct);
}

//HasToStringFunction���ڻ��������������ͺͺ���������������ֻ��
//�̶���ѯĳ�������Ƿ��г�Ա������const char* ToString()const
void test_check_class_method()
{
	std::cout << HasToStringFunction<A>::Value << "\n";
	std::cout << HasToStringFunction<B>::Value << "\n";

	A a;
	B b;
	std::cout << AnyToString<A>(a) << "\n";
	std::cout << AnyToString<B>(b) << "\n";
}

template<class Type>
struct TestMethod
{
	typedef const char* (Type::*CacheData)()const;
	CacheData	action;

	TestMethod(Type *m)
	{

	}
	TestMethod(Type *m, CacheData _action)
	{

	}
};


int main()
{
	test_check_class_method();

	auto m = &A::ToString;

	A a;
	B b;
	TestMethod<A> l1(&a);
	TestMethod<A> l2(&a, &A::ToString);
	//CLruCache<A> l3(&a, &B::ToString);

	std::cout << "=========================OK=========================\n";
	getchar();
	return 0;
}