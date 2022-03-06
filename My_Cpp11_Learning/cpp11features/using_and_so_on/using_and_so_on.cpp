#include <iostream>
#include <string>
#include <vector>
using namespace std;

template< typename first, typename second, int third>
class SomeType;

//typedef�ɶ���ģ������һ���µ��������ƣ����ǲ��ܹ�ʹ��typedef������ģ��ı���
typedef std::vector<int> IntVec;    // Ok

//template< typename second>
//typedef SomeType<int, second, 5> TypedefName;   // Error

//ʹ��using����ģ�����
template< typename second>
using TypedefName = SomeType<int, second, 5>;   // Ok

//usingҲ����C++11�ж���һ�����͵ı�������ͬtypedef��
typedef void(*PFD)(double);		// Ok
using PFD = void(*)(double);	// Ok

//���ͱ���
typedef std::string MyStr1;     // Ok
using MyStr2 = std::string;     // Ok

//�ⲿģ��
extern template class std::vector<std::string>; //���߱�������Ҫ�ڸñ��뵥Ԫ�ڽ���ģ��ʵ������

//�Ҽ����ţ�C++11 �ṩ���µĽ������򣬶���Ҽ����ŵ�ʱ�򣬻�����Ϊģ����������������ŵ�ʱ�򣬻��Ƚ�������
//VS2013��֧��
//template<bool Test> class SomeType { };
//std::vector<SomeType<1>2>> x1; // Interpreted as a std::vector of SomeType<true> 2>, which is not legal syntax. 1 is true.
//std::vector<SomeType<(1>2)> > x1; // Interpreted as a std::vector of SomeType<false>, which is legal C++11 syntax, (1>2) is false.

int main()
{
	//ģ�����
	IntVec v;

	//���ͱ���
	MyStr2 ss;

	//C++11���һ���µ����� long long int������֤��СҪ��long intһ�����Ҳ���С�� 64 - bit
	std::cout << sizeof(long int) << "\n";       // 4	
	std::cout << sizeof(long long int) << "\n";  // 8

	//��ʽ���Է�ΧΪ������forѭ�������Ա���Cʽ���顢��ʼ���б�(initializer lists)���Ͷ�����begin()/end()����(���ص�����)�����͡�
	int my_array[5] = { 1, 2, 3, 4, 5 };
	for (int &x : my_array)
	{
		x *= 2;
	}

	getchar();
	return 0;
}