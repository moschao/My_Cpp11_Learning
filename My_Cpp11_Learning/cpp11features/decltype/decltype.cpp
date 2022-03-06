//http://www.devbean.net/2012/05/cpp11-decltype/
#include <iostream>
using namespace std;



//decltype�ؼ������ڲ�ѯ���ʽ������,�����ڱ����ھ����Ƶ������ʽ����
/***
����decltype( e )���ԣ����б���������������Ӱ�죺
1. ���e��һ����ʶ���������Ա�ķ��ʱ��ʽ����decltype(e)����e�������ʵ������͡�
���û���������ͻ���e��һ�����غ���������ô�����Ǵ���ģ������е� (2) �� (3)����
2. ���e��һ���������û���һ�����ز��������ã�����e��������ţ�����ôdecltype(e)���Ǹú����ķ������ͣ������е� (1)����
3. ���e��������������������������e�������� T����e��һ����ֵʱ��decltype(e)����T&��
����e��һ����ֵ����decltype(e)��T�������е� (4) ���������������
����������У�eʵ����(a->x)��������������ţ������������ǰ���������������Ӧ���Ա�����Ϊ�б����ݡ���(a->x)��һ����ֵ����˻᷵��double &����
4. decltype((e))�Ľ����Զ�����ã���decltype(e)���ֻ�е� e �������һ������ʱ��������
***/
const int&& foo();
struct A { double x; };
void test_decltype()
{
	{
		int i;
		const A* a = new A();

		decltype(foo())  x1 = 2;  // const int&&    (1)
		decltype(i)      x2;      // int			(2)
		decltype(a->x)   x3;      // double			(3)
		decltype((a->x)) x4 = 1;  // double&		(4)
	}
	{
		int    i;
		float  f;
		double d;

		typedef decltype(i + f) type1;  // float
		typedef decltype(f + d) type2;  // double
		typedef decltype(f < d) type3;  // bool
	}
}

//decltype��ģ�������ô�
//��������������ģ��ʱ��������֪�� T �� U ��ʵ�����͡���ʹ������ģ��ֵʵ�ʶ��� C++ �������ͣ�����Ҳ�޷�ȷ�е�֪�����ǵĺ͵����͡�
template<typename T, typename U>
auto foo(T t, U u) -> decltype(t + u) { return t + u; }
//template<typename T, typename U>
//decltype(t + u) foo(T t, U u){ return t + u; }  //Error!��Ϊt��u�ڶ���ǰ�ͳ����ˣ���ֱ������������������ԭ�͵ĺ�벿ʱ��t��u�����������

void test_decltype_in_template()
{
	auto v = foo(1, 1.0);
}

int main()
{
	test_decltype();
	test_decltype_in_template();

	std::cout << "success\n";
	getchar();
	return 0;
}