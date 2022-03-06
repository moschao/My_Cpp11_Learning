/* http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/ */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//���ڰ�ȫ�����ɣ������Ĳ�������Զ�����϶�Ϊ��ֵ����ʹ���Ǳ���������ģ�Ϊ�˻����ֵ����ʹ�� std::move<T>()
bool is_r_value(int &&) { return true; }
bool is_r_value(const int &) { return false; }
bool forward_r_value(int && i) { return is_r_value(i); }
void test_rvr(int && i)
{
	cout << is_r_value(i) << "\n"; //false: iΪ������������ʹ����������ֵҲ�����Ƶ�����ֵ(������������ֻ������ֵ����)
	cout << is_r_value(std::move<int&>(i)) << "\n";  //true: ʹ�� std::move<T>() ȡ����ֵ
	cout << is_r_value(2) << "\n"; //true: 2����ֵ 
	cout << forward_r_value(2) << "\n";  //false: ��Ȼ2����ֵ�����Ǿ���ת�������˾������������ձ����ֵ
}

//                   ��ֵ�������ļ�ֵ֮һ�� ֧��ת������(Move Sementics)
/***
ת��������Խ���Դ(�ѣ�ϵͳ�����) ��һ������ת�Ƶ���һ�����������ܹ����ٲ���Ҫ����ʱ����Ĵ����������Լ����٣�
�ܹ��������� C++ Ӧ�ó�������ܡ�

��ʱ�����ά�� ( ���������� ) ������������Ӱ�졣ͨ��ת�����壬��ʱ�����е���Դ�ܹ�ת�������Ķ����

�����е�C++�����У����ǿ��Զ��忽�����캯���͸�ֵ������
Ҫʵ��ת�����壬��Ҫ����ת�ƹ��캯���������Զ���ת�Ƹ�ֵ��������
������ֵ�Ŀ����͸�ֵ�����ת�ƹ��캯����ת�Ƹ�ֵ��������
���ת�ƹ��캯����ת�ƿ���������û�ж��壬��ô����ѭ���еĻ��ƣ��������캯���͸�ֵ�������ᱻ���á�

��ͨ�ĺ����Ͳ�����Ҳ����������ֵ���ò�����ʵ��ת�����塣
***/

//������������ֻ������ֵ���ã������֪һ�����������ٱ�ʹ�ö����������ת�ƹ��캯����ת�Ƹ�ֵ������
//Ҳ���ǰ�һ����ֵ���õ�����ֵ������ʹ�ã�����ʹ�ñ�׼���ṩ��std::move��������������Էǳ��򵥵ķ�ʽ����ֵ����ת��Ϊ��ֵ���á�
std::string test(const std::string& str)
{
	printf("1: 0x%08x\n", str.c_str());
	std::string tmp(str);
	tmp.append("test!");  //ע�����д��룬2��3��ַ��ͬ����Ӵ��к�2��3��ַ��ͬ��
	printf("2: 0x%08x\n", tmp.c_str());
	//return std::move(tmp);  //�������ֱ�ӷ�����һ���ģ���Ϊstring�Ѿ�ʵ����ת������
	return tmp;
}

std::vector<int> test(const std::vector<int>& v)
{
	printf("1: 0x%x\n", &v[0]);
	std::vector<int> t(v);
	t.push_back(88);
	printf("2: 0x%x\n", &t[0]);
	return t; // ��std::move(t);���һ��
	//return std::move(t);
}

//                   ��ֵ�������ļ�ֵ֮���� ��ȷ���ݡ�����ת�� (Perfect Forwarding)
/***             
�ܹ��������ȷ�ض��巺�ͺ���
��ȷ���������������ĳ�������Ҫ��һ�����ԭ�ⲻ���Ĵ��ݸ���һ��������
��ԭ�ⲻ�����������ǲ�����ֵ���䣬�� C++ �У����˲���ֵ֮�⣬����һ���������ԣ���ֵ����ֵ�� const/non-const��
��ȷ���ݾ����ڲ������ݹ����У�������Щ���ԺͲ���ֵ�����ܸı䡣�ڷ��ͺ����У�����������ǳ��ձ顣
***/
//void process_value(int i) { std::cout << "int\n"; }
void process_value(int& i) { std::cout << "int&\n"; }
void process_value(const int& i) { std::cout << "const int&\n"; }
void process_value(int&& i) { std::cout << "int&&\n"; }
void process_value(const int&& i) { std::cout << "const int&&\n"; }

template<typename T>
void print_value(T& t)
{
	t++;
	cout << "lvalue " << t << "\n";
}

template<typename T>
void print_value(T && t)
{
	cout << "rvalue " << t << "\n";
}

template<typename T>
void do_forward(T && v)
{
	v++;
	print_value(v);
	print_value(std::forward<T>(v)); //���ղ���������������ת����ȥ
	print_value(std::move(v));       //��v�����ֵ����
}

void test_forward()
{
	int a = 0;
	const int& b = 1;
	process_value(a); // int& 
	process_value(b); // const int& 
	process_value(2); // int&&
	process_value(std::move(a)); // int&&
	process_value(std::move(2)); // int&&
	process_value(std::move(b)); // const int&&

	int x = 1;
	do_forward(1);  // lvalue rvalue rvalue
	do_forward(x);  // lvalue lvalue rvalue
	do_forward(std::forward<int>(x));  // lvalue rvalue rvalue	
}

//���ܺ�����װ������ֵ����+����ת��+�ɱ�ģ��������� ���Խ������еĺ�����������ֵ�ġ���������ֵ�ġ��������ġ�����������
template<typename Function, class... Args>
inline auto FuncWrapper(Function && func, Args && ... args) -> decltype(func(std::forward<Args>(args)...))
{
	//typedef decltype(func(std::forward<Args>(args)...)) ReturnType;
	return func(std::forward<Args>(args)...);
}

void func1(){ cout << "void" << endl; }
int  func2(){ return 1; }
int  func3(int x){ return x; }
std::string func4(std::string s1, std::string s2){ return s1 + s2; }

void test_func_wapper()
{
	FuncWrapper(func1);  // 1
	std::cout << FuncWrapper(func2) << "\n"; // 1
	std::cout << FuncWrapper(func3, 2) << "\n"; // 2
	std::cout << FuncWrapper(func4, "hello", " world") << "\n"; // hello  world
}

int main()
{
	test_rvr(0);
	cout << "----------------------------\n";

	test_forward();
	cout << "----------------------------\n";

	test_func_wapper();
	cout << "----------------------------\n";

	printf("3: 0x%08x\n", test("��ֵ���ò��ԣ�").c_str());
	cout << "----------------------------\n";

	std::vector<int> v(3); // �ı����ֵ�Ĵ�С(<3)�����ῴ��v2[0]��ַ�ı仯
	v.push_back(2);
	v.push_back(5);
	v.push_back(9);
	std::vector<int> v2 = test(v);
	printf("3: 0x%x\n", &v2[0]); 
	for (int i = 0; i < 100; ++i)
		v2.push_back(i);
	printf("4: 0x%x\n", &v2[0]);
	cout << "----------------------------\n";

	getchar();
	return 0;
}