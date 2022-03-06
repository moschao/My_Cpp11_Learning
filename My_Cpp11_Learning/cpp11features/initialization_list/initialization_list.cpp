#include <iostream>
#include <string>
#include <vector>
#include <complex>
using namespace std;


void foo1(std::string a[]) { }
void foo2(std::initializer_list<std::string> list) { }

struct BasicStruct
{
	int x;
	float y;
};

class SequenceClass
{
public:
	SequenceClass(int i = 0){}
	//��ʼ���б��캯��
	SequenceClass(std::initializer_list<int> list){}
	SequenceClass(std::initializer_list<string> list){}
};

void test_initialization_list()
{
	std::string a[] = { "Hello", "world" }; // ��ȷ����ʼ���������
	
	std::vector<std::string> v = { "hello", "world" };
	
	foo1(a);
	//foo1({ "foo", "bar" });   // �������cannot convert argument 1 from 'initializer-list' to 'std::string []'
	foo2({ "foo", "bar" });     // ��ȷ

	int aa[] = { 1, 2, 3 };     // �ó�ʼ���б���еĸ�ֵ���ĳ�ʼ��

	complex<double> zz(1, 2.0); // �������ĳ�ʼ��, �ȿ�����Ϊ��һ����ʼ����Ҳ������Ϊ��һ����������


	SequenceClass someVar1 = { 1, 2, 3, 4 };         //��һ�����ʼ�������ó�ʼ���б��캯��
	SequenceClass someVar2 = { "hello", "world" };   //ͬ��
	SequenceClass vsc1[]   = { 1, 2, 3, 4 };         //�����ʼ����ÿ��Ԫ�ص���SequenceClass(int i = 0)���캯��
	SequenceClass vsc2[]   = { { 1, 2 }, { 3, 4 } }; //�����ʼ����ÿ��Ԫ�ص��ó�ʼ���б��캯��

	BasicStruct var1{ 5, 3.2f };

	std::vector<int> vec1{ 4 };  //���ó�ʼ���б��캯������ʱvec1��ֻ��һ��Ԫ�أ�4
	std::vector<int> vec2( 4 );  //����std::vector����һ����С�����Ĺ��캯������ʱvec2��4����С�ռ䣬ÿ��Ԫ��ֵΪĬ��

}

int main()
{
	test_initialization_list();

	getchar();
	return 0;
}