#include <iostream>
#include <string>
#include <vector>
using namespace std;

//                 �䳤����ģ��
/***
C++11 ֮ǰ, ��������ģ����Ǻ���ģ�壬��ֻ�ܰ��䱻����ʱ��ָ�������ӣ�����һ��̶���Ŀ��ģ����� ��
C++11 �����µı�ʾ�������������������������ģ������������ڶ���ʱ�������ĸ����̶���

emplate<typename... Values> class tuple;  ģ���� tuple �Ķ����ܽ��ܲ��޸����� typename ��Ϊ����ģ���βΣ�
	class tuple<int, std::vector<int>, std::map<std::string, std::vector<int>>> someInstanceName;
ʵ�εĸ���Ҳ������ 0������ class tuple<> someInstanceName �����Ķ���Ҳ�ǿ��Եġ�
����ϣ������ʵ�θ���Ϊ 0 �ı䳤����ģ�壬����Բ������µĶ��壺
	template<typename First, typename... Rest> class tuple;

��template<typename... Params> void printf(const std::string &strFormat, Params... parameters);
���У�Params �� parameters �ֱ����ģ���뺯���ı䳤�������ϣ� ��֮Ϊ������ (parameter pack)������������Ҫ�������"..."����ʹ�ã������﷨�ϵ����塣

�䳤����ģ���У��䳤�������޷���ͬһ��������������ʹ�ã� ��˵��͵��ַ����Եݹ�ķ���ȡ�����ò���

������ģ���������ʹ��...��ʾ������ģ������⣬��������Ҳʹ��ͬ���ı�ʾ����������������
***/


//C++ʵ�ֵ�printf������
//printf_cpp�᲻�ϵصݹ������������������ args... �ڵ���ʱ�� �ᱻģ�����ƥ�����Ϊ T value�� Args... args��
//ֱ�� args... ��Ϊ�ղ����������򵥵� printf(const char *s) �γ�ƥ�䣬�˳��ݹ顣
void printf_cpp(const char *s)
{
	while (*s)
	{
		if (*s == '%' && *(++s) != '%')
			throw std::runtime_error("invalid format string: missing arguments");
		std::cout << *s++;
	}
}

template<typename T, typename... Args>
void printf_cpp(const char* s, T value, Args... args)
{
	while (*s)
	{
		if (*s == '%' && *(++s) != '%')
		{
			std::cout << value;
			printf_cpp(*s ? ++s : s, args...); // ���㵱 *s == 0 Ҳ��������ã��Լ���������Ͳ�����
			return;
		}
		std::cout << *s++;
	}
	throw std::logic_error("extra arguments provided to printf");
}

//����䳤����������
template<typename ...Args> 
struct count_paras
{
	static const int size = sizeof...(Args);
};

int main()
{
	printf_cpp("My name is %s, age is %d, live in %s\n", "lizheng", 26, "Beijing");

	std::cout << count_paras<int, double>::size << "\n"; // 2
	std::cout << count_paras<>::size << "\n"; // 0

	getchar();
	return 0;
}