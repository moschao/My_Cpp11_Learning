#include <iostream>
#include <string>
#include <vector>
using namespace std;

//               override �� final
/***
override : ��������������Ƿ����һ���⺯�����������д�������override�����⺯������ͬ�ĺ���ǩ��(signature)���������ڣ���ᱨ��
final    : �����������ͱ��̳У����ǻ���ĺ�������д
***/
struct Base1
{
	virtual void foo1(float a)
	{
		std::cout << "Base: " << a << std::endl;
	}
	virtual void foo2(float a)
	{
		std::cout << "Base: " << a << std::endl;
	}
};

struct Derived1 : Base1 
{
	virtual void foo1(int a)  //���ﲢû�����ػ����е��麯��foo1����Ϊ����������ǩ������ͬ
	{
		std::cout << "Derived: " << a << std::endl;
	}
	virtual void foo2(float a) override //ͨ��overrideǿ�ƹ涨foo2�����ػ�����麯��foo2���������Ա�����д����
	{
		std::cout << "Derived: " << a << std::endl;
	}
};


struct NoInherit final {}; //ʹ��final��ʾ���಻�ܱ��̳�
//struct Child : NoInherit  {}; //Error
struct Base2
{
	virtual void foo(int) final { } //ʹ��final��ֹ����������д�ú���
};
struct Derived2 : Base2
{
	//virtual void foo(int); //Error,
};


int main()
{
	Base1 *b = new Derived1;
	b->foo1(1);	   // Base1 1, ��ΪBase��Derived�е�foo1���������麯�����أ���Ϊ����ǩ����ͬ�����������������д�����������⣡
	b->foo1(1.0);  // Base1 1
	b->foo2(1);    // Derived1 1
	b->foo2(1.0);  // Derived1 1

	getchar();
	return 0;
}