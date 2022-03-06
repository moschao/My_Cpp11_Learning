#include <iostream>
#include <string>
#include <vector>
using namespace std;

//              nullptr
/***
����0���������ͳ����Ϳ�ָ�볣����˫����ݡ�
Ϊ�˽��0�Ķ�����,C++11ͨ������һ���µĹؼ���������������⣬������־��ָ�볣��: nullptr��
����������nullptr_t(������ʽת�����κ�ָ����߳�Աָ��(pointer-to-member)���ͣ�����ת�����������ͣ�����bool)��
***/

void foo(char *) { std::cout << "foo(char *)\n"; }
void foo(int)    { std::cout << "foo(int)\n"; }

void test_nullptr()
{
	char *pc = nullptr; // ok
	int  *pi = nullptr; // ok
	bool  bb = nullptr; // ok, b is false
	//int   i1 = nullptr; // error,nullptr��������0

	int  *p1 = NULL;	// ok
	int   i2 = NULL;	// ok, NULL==0

	foo(NULL);     // �����߿���ϣ�����õ���foo(char *)����ʵ���ϵ���foo(int)����Ϊ#define NULL ((void*)0)
	foo(nullptr);  // call foo(char *), not foo(int);
}

//              constexpr
/***
�������ʽ(const expression) ��ֵָ����ı䲢���ڱ�����̾��ܵõ��������ı��ʽ��
C++11�涨��������������Ϊconstexpr�����Ա��ɱ���������֤�����Ƿ���һ���������ʽ��
����Ϊconstexpr �ı���һ����һ�����������ұ����ó������ʽ��ʼ����
***/
//?+ VS2013 �в�֧�ָùؼ���

#ifndef WIN32
int GetFive1() { return 5; }
constexpr int GetFive2() { return 5; }
//constexpr int GetFive3(int i) { return i + 1; } //Error,�Ǳ����ڳ���������ʹ��constexpr����
void test_constexpr()
{
	//int arr1[GetFive1() + 1]; //Error��C++�������С�����ڱ�����ȷ����������������֪��GetFive1�Ǹ�����
	int arr2[GetFive2() + 1];

	constexpr int i = 100;      // 100 �ǳ������ʽ
	constexpr int i2 = i + 1;   // i + 1 �ǳ������ʽ
	constexpr sz = GetFive2();  // ֻ�е�GetFive2��һ��constexpr����ʱ����ȷ

	const int *p = nullptr;     // p ��һ��ָ�����г�����ָ��, p �ǿɱ�ģ�pָ��Ķ����ǲ��ɱ��
	constexpr int *q = nullptr; // q ��һ��ָ�������ĳ���ָ��, �ǲ��ɱ�ģ�qָ��Ķ����ǿɱ��
}
#else
void test_constexpr()
{
	std::cout << "Visual Studio 2013 don't support constexpr\n";
}
#endif

int main()
{
	test_nullptr();

	test_constexpr();

	getchar();
	return 0;
}