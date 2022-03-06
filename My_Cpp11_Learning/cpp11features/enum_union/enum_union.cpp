#include <iostream>
#include <string>
#include <vector>
using namespace std;
//http://zh.wikipedia.org/zh-cn/C++11#.E7.B5.B1.E4.B8.80.E7.9A.84.E5.88.9D.E5.A7.8B.E5.8C.96

//                                ǿ����ö��
/***
�ڱ�׼C++�У�ö�����Ͳ������Ͱ�ȫ�ġ�ö�����ͱ���Ϊ��������ʹ�����ֲ�ͬ��ö������֮����Խ��бȽϡ�
C++03 Ψһ�ṩ�İ�ȫ������һ��������һ��ö����ֵ������ʽת������һ��ö�ٱ��͡�
���⣬ö����ʹ���������ͼ����С����ʵ�ַ������壬���޷���ȷָ���� 
���ö�ٵ�����ȫ����¶��һ�㷶Χ�У����������ͬ��ö�٣�����������ͬ��ö������ 
�ñ� enum Side{ Right, Left }; �� enum Thing{ Wrong, Right }; ����һ��ʹ�á�
C++11 ������һ���ر�� "ö����"�����Ա������������⡣ʹ�� enum class ���﷨��������

����ö��Ϊ���Ͱ�ȫ�ġ�ö�����Ͳ�����ʽ��ת��Ϊ������Ҳ�޷���������ֵ���Ƚϡ� (��ʾʽ Enumeration::Val4 == 101 �ᴥ�������ڴ���)��
ö��������ʹ�����ͱ�����ʽָ����
***/
enum class Enumeration1   //Ĭ��������int
{
	Val1,
	Val2,
	Val3 = 100,
	Val4 /* = 101 */,
};

enum class Enumeration2 : long
{
	Val1,
	Val2,
	Val3 = 100,
	Val4 /* = 101 */,
};

enum OldEnum1{ EOLDNUM1, EOLDNUM2 };
//enum OldEnum2{ EOLDNUM1, EOLDNUM2 }; //���ɶ��壬��Ϊ�ϵ�ö������������������ȫ�֣�ǰ������EOLDNUM1��EOLDNUM2������

void test_enum()
{
	//OldEnum1 ������֮����Ի�ת���ȽϵȲ���

	Enumeration1 e1 = Enumeration1::Val1;
	//Enumeration1 e2 = 2; //Error ����Ҳ����ת��Ϊö�������
	//int e = e1;          //Error ö������Ҳ����ת��Ϊ���� 

	Enumeration2 e21 = Enumeration2::Val1;
	//Enumeration2 e22 = Enumeration1::Val1;  //Error  Enumeration1��Enumeration2�ǲ�ͬ��ö����
	//if (e21 == 1)       //Error  ö�������޷���������ֵ���Ƚ�		
}

//                                �����Ƶ�union
/***
�ڱ�׼ C++ �У�������������Ͷ�����Ϊ union �ĳ�Ա��������� non-trivial ���캯�������;Ͳ����� union �ĳ�Ա��
���µı�׼��Ƴ������ж� union ��ʹ�����ƣ��������Ա��Ȼ�������������͡�

ע�⣺Ŀǰvisual studio 2013�в�֧�ָù��ܣ��뿴��http://msdn.microsoft.com/zh-cn/library/hh567368.aspx
http://www.csdn.net/article/2013-03-18/2814528-c11-compiler-support-shootout-visual-studio-gcc-clang-intel
***/
struct Point {
	Point() {}
	Point(int x, int y) : x_(x), y_(y) {}
	int x_, y_;
};

union U {
	int z;
	double w;
	//Point p;  // Illegal in C++03; legal in C++11
	U()// : p()
	{
		//new (&p) Point(); // Due to the Point member, a constructor definition is now required.
	}
};

int main()
{

	getchar();
	return 0;
}