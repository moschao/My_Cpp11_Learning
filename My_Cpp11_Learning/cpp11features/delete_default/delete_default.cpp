#include <iostream>
#include <string>
#include <vector>
using namespace std;

/***               delete �� default
������ж������κ�һ�ֹ��캯������������������Ĭ�ϵĹ��캯����
���ǣ����һ�������ָ���˹��캯����ͬʱ������Ҫ����������һ��Ĭ�ϵĹ��캯����
C++ 11��������ʽ��ʹ�û���ɾ��ָ���ĳ�Ա����

delete �� ��ʾ��������Ĳ��ɵ��õ�
***/
struct NonCopyable
{
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable & operator=(const NonCopyable&) = delete;

	void foo(double i){ }
	void foo(int) = delete;  //������ͨ�����β�������foo��Ҳ��ֹ��int->double��ת��
	template<class T> void f(T) = delete;  //��ֹ�˳�����double���д������������е�ʹ�÷�ʽ
private:
	//NonCopyable(const NonCopyable&);  // C++11֮ǰ������
	//NonCopyable & operator=(const NonCopyable&);
};

class NonA : public NonCopyable
{

};

int main()
{
	NonA a;
	//NonA b = a;  //Error
	//NonA c(a);   //Error

	a.foo(1.0);
	//a.foo(1); //Error

	getchar();
	return 0;
}