#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//1. C++11�����캯�������������캯����Ҳ��ί�л�ת��(delegation).
class SomeType 
{	
public:
	SomeType() : SomeType(0, "invalid"){ }
	SomeType(int i) : SomeType(i, "guest"){ }
	SomeType(const std::string& s) : SomeType(1, s){ }

	SomeType(int i, const std::string& s) : id(i), name(s)
	{ 
		std::cout << id << "\t" << name << "\n";
	}
private:
	int id;
	std::string name;
};

//2. C++11�����������ֶ��̳л���Ĺ��캯��������������ʹ�û���Ĺ��캯�����������Ĺ��졣
class BaseClass
{
public:
	explicit BaseClass(int iValue){ }
};

class DerivedClass : public BaseClass
{
public:
	using BaseClass::BaseClass; //���﷨��ͬ������һ��DerivedClass(int)�Ĺ��캯��
};

//3. C++11����ʹ�����µ��﷨��ɳ�Ա��ʼ��:
class SomeClass
{
public:
	SomeClass() { print(); }
	SomeClass(int iNewValue, const std::vector<int> v) : iValue(iNewValue),vvv(v){ print(); }
public:
	void print()
	{
		std::cout << "iValue : " << iValue << "\n"; 
		std::copy(vvv.begin(), vvv.end(), std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << "\n";
	}
private:
	int iValue = 5;  //���ǹ��캯����û������iValue�ĳ�ʼֵ���������ඨ���еĳ�Ա��ʼ������iValue��ֵΪ5
	std::vector<int> vvv;// = { 1, 2, 3, 4 }; //�ݲ�֧�ֳ�ʼ���б�Ĭ��ֵ
};

void test_obj_ctor()
{
	{
		SomeType s1;
		SomeType s2(1);
		SomeType s3("lizheng");
		SomeType s4(100, "sometype");
		std::cout << "-----------------------------\n";
	}
	{		
		BaseClass b1(1);
		//DerivedClass d1(2);   //�ðɣ��ƺ���VS2013����֧��
		//DerivedClass d2;    //Error,��ΪDerivedClass����һ���̳ж����Ĺ��캯�������Բ�����Ĭ�Ϲ��캯��
		std::cout << "-----------------------------\n";
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		SomeClass s1;          // ʹ����Ĭ�϶����ֵ
		SomeClass s2(2,v);     // 
		std::cout << "-----------------------------\n";
	}
}

int main()
{
	test_obj_ctor();

	getchar();
	return 0;
}