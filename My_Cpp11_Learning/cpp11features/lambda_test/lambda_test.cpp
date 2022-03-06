#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std;

//                          Lambda
/***
C++11��ʼ֧������������Ҳ��Lambda������Lambda���ʽ��ʽ���£�
		[capture](parameters)->return-type{body}
��� parametersû��ֵ�Ļ������ſ���ʡ�ԡ����bodyֻ��һ������״̬���߷���ֵΪvoid��return-type ������ʡ�Ե������£�
		[capture]{body}
һЩ lambda ����������
	[](int x, int y) { return x + y; } // implicit return type from 'return' statement
	[](int& x) { ++x; }   // no return statement -> lambda function's return type is 'void'
	[]() { ++global_x; }  // no parameters, just accessing a global variable
	[]{ ++global_x; }     // the same, so () can be omitted
û��return-type��ʱ��C++11ʹ��decltype����������ֵ���ͣ���ȻҲ������ʽָ����
	[](int x, int y) -> int { int z = x + y; return z; }
lambda��������ʹ��lambda��������ı�־������Щ�����ļ���ͨ������Ϊ�հ����հ���lambda���ʽ��[]�ж��壬������ֵ�������á�������ʾ��
	[]        // ��ʹ���κ��ⲿ���������ʹ�ã��ͻᱨ��no variables defined. Attempting to use any external variables in the lambda is an error.
	[&]       // ��������Ҫʹ�õ��ⲿ�������������÷�ʽ���� any external variable is implicitly captured by reference if used
	[=]       // ��������Ҫʹ�õ��ⲿ���������Դ�ֵ��ʽ���� any external variable is implicitly captured by value if used
	[x, &y]   // x�Դ�ֵ��ʽʹ�ã�y�����÷�ʽ x is captured by value, y is captured by reference
	[&, x]    // x�Դ�ֵ��ʽʹ�ã����������÷�ʽ x is explicitly captured by value. Other variables will be captured by reference
	[=, &x]   // x�����÷�ʽʹ�ã������Դ�ֵ��ʽ x is explicitly captured by reference. Other variables will be captured by value
***/

void test_lambda()
{
	{
		std::vector<int> vec{ 1, 2, 3, 4, 5 };
		int total = 0;
		std::for_each(vec.begin(), vec.end(), [&total](int x) { total += x; });
		std::cout << total << "\n==========\n";   // 15 = 1 + 2 + 3 + 4 + 5

		//���Ҵ���2С��10��Ԫ�صĸ��� : ���ַ�ʽ�Ա�
		auto f = std::bind(std::logical_and<bool>(), bind(std::greater<int>(), std::placeholders::_1, 2),
												     bind(std::less_equal<int>(), std::placeholders::_1, 10));
		int count1 = count_if(vec.begin(), vec.end(), f);

		int count2 = count_if(vec.begin(), vec.end(), [](int x){return x>2 && x<10; });
		assert(count1 == count2);
	}
	{	//���ڲ�ͬ�Ĳ�������ֵ�����ÿ��Ի��ʹ�á� �ȷ�˵���û����������еĲ������Դ����õķ�ʽʹ�ã�������һ����ֵʹ�õĲ�����
		std::vector<int> vec{ 1, 2, 3, 4, 5 };
		int value = 5, total = 0;
		//total �����õķ�ʽ����lambda ��������value���Ǵ�ֵ��
		std::for_each(std::begin(vec), std::end(vec), [&, value](int x) { total += (x * value); });
		std::cout << total << "\n==========\n"; // 75 = 1*5 + 2*5 + 3*5 + 4*5 + 5*5
	}
	{
		struct Sc
		{
			int GetFour(){ return 4; }
			void AddFour(int& x){ x += 4; }
			void test_lambda()
			{
				std::vector<int> vec{ 1, 2, 3, 4, 5 };
				{
					int value = 5, total = 0;
					std::for_each(vec.begin(), vec.end(), [&total, &value, this](int x) {
						total += x * value * this->GetFour();
					});
					std::cout << total << "\n"; // 300 = 1*5*4 + 2*5*4 + 3*5*4 + 4*5*4 + 5*5*4
				}
				{
					int value = 5, total = 0;
					//���ó�Ա��������Ҫ����this�ſ���
					std::for_each(vec.begin(), vec.end(), [&total, &value, this](int x) {
						total += x * value;
						this->AddFour(total);
					});
					std::cout << total << "\n==========\n"; // 95 = 1*5+4 + 2*5+4 + 3*5+4 + 4*5+4 + 5*5+4
				}
			}
		};
		Sc sc;
		sc.test_lambda();
	}
}

//lambda����ʵ�������������͵ĺ�������(function object)�����͵�����ֻ�б��������á�
//������ lambda ������Ϊ�������õĻ������ͱ�����һ��ģ�����ͣ����߱��봴��һ�� std::function ����һ�����ƵĶ���ȥץȡ lambda ֵ�� 
//auto �ؼ����������洢 lambda ������  
// http://cpp1x.org/Lambda-Function-And-Expressions.html

double eval(std::function<double(double)> f, double x = 2.0){ return f(x); }

void test_lambda2()
{
	//��������Ӵ洢���������ڱ�����vectors���� arrays �У�Ȼ������ǵ����ֵ���������ʹ�ã�
	
	std::function<double(double)> f0 = [](double x){ return 1; };
	auto                          f1 = [](double x){ return x; };
	decltype(f0)                  fa[3] = { f0, f1, [](double x){ return x*x; } };
	std::vector<decltype(f0)>     fv = { f0, f1 };
	fv.push_back([](double x){return x*x; });
	for (int i = 0; i<fv.size(); i++)  
		std::cout << fv[i](2.0) << "\n";
	std::cout << "==========\n";
	for (int i = 0; i<3; i++)          
		std::cout << fa[i](2.0) << "\n";
	std::cout << "==========\n";
	for (auto &f : fv)             
		std::cout << f(2.0) << "\n";
	std::cout << "==========\n";
	for (auto &f : fa)             
		std::cout << f(2.0) << "\n";
	std::cout << "==========\n";

	std::cout << eval(f0) << "\n";
	std::cout << eval(f1) << "\n";
	std::cout << eval([](double x){return x*x; }) << "\n";
		
	//lambda ���[] Ϊ�յĻ���������ʽת����һ������ָ��Ͷ�Ӧ�ĺ���ָ����ͬ�����������ǺϷ��ģ�
	auto my_onheap_lambda_func = new auto([=](int x) { /*...*/ });
	auto a_lambda_func = [](int x) { /*...*/ };
	void(*func_ptr)(int) = a_lambda_func;
	func_ptr(4); //calls the lambda.
}
int main()
{
	test_lambda();
	test_lambda2();

	getchar();
	return 0;
}