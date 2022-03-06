#include <iostream>
#include <functional>
#include <string>
#include <assert.h>
using namespace std;

// ��Ϻ�������N��һԪ�������һ�ָ����ӵĺ�����ÿ�������ķ���
// ֵ��Ϊ����������һ��������ֱ���������һ������������
// ���������ԣ�
//     ����һԪ��������Ϊ����ֵҪ���¸���������Σ�����ֵֻ��һ�����;
//     һԪ��������κͷ���ֵ����ͬһ�����ͣ���Ϊ����ֵҪ���¸����������;
//     ���Ҫ���ж�����������Խ�һ���ṹ����Ϊ��Σ�
//     ��������˳���ǰ�������;   
// see http://www.cnblogs.com/qicosmos/p/3292490.html
template <typename OuterFn, typename InnerFn>
class Composed
{
public:
	explicit Composed(OuterFn &outerFn, InnerFn &innerFn)
		: m_outerFn(outerFn), m_innerFn(innerFn)
	{}

	Composed(Composed& other)
		: m_innerFn(std::move(other.m_innerFn)),
		  m_outerFn(std::move(other.m_outerFn))
	{}

	Composed(Composed&& other)
		: m_innerFn(std::move(other.m_innerFn)),
		 m_outerFn(std::move(other.m_outerFn))
	{}

public:
	template <typename Arg> //ֻ��һ������
	auto operator()(Arg && arg) -> decltype(m_outerFn(m_innerFn(arg)))
	{
		return m_outerFn(m_innerFn(arg));
	}

private:
	InnerFn m_innerFn;
	OuterFn m_outerFn;
};

template < typename Function1, typename Function2 >
Composed<Function1, Function2>	Compose(Function1 &f1, Function2 &f2)
{
	return Composed<Function1, Function2>(f1, f2);
}
template < typename Function1, typename Function2, typename... Functions >
auto Compose(Function1 &f1, Function2 &f2, Functions &... f3)->decltype(Compose(Compose(f1, f2), f3...))
{
	return Compose(Compose(f1, f2), f3...);
}

int gt(int x){ return x; }
int ht(int y){ return y; }

void TestCompose()
{
	auto f1 = [](int a){ return a + 1; };
	auto g1 = [](int b){ return b + 2; };
	auto h1 = [](int c){ return c + 3; };
	auto I1 = [](int d){ return d + 4; };
	auto J1 = [](int e){ return e + 5; };

	auto ret = Compose(f1, g1, h1)(3);
	assert(ret == f1(g1(h1(3))));
	cout << ret << "\n";

	ret = Compose(f1, g1, h1, I1)(3);
	assert(ret == f1(g1(h1(I1(3)))));
	cout << ret << "\n";

	ret = Compose(f1, g1, h1, I1, J1)(3);
	assert(ret == f1(g1(h1(I1(J1(3))))));
	cout << ret << "\n";

	ret = Compose(f1, g1, h1, I1, J1, J1, J1)(3);
	cout << ret << "\n";

	ret = Compose([](int d)
					{
						return d + 4;
					},
				  [](int d)
					{
						return d + 5;
					})(3);
	cout << ret << "\n";

	ret = Compose(std::bind(gt, std::placeholders::_1), 
					std::bind(ht, std::placeholders::_1))(3);
	cout << ret << "\n";
}


// ��ʽ����, ������ϵ��õ�������
template<typename T>
class Task;

template<typename R, typename...Args>
class Task<R(Args...)>
{
public:
	Task(std::function<R(Args...)>&& f) : m_fn(std::move(f))
	{}

	Task(std::function<R(Args...)>& f) : m_fn(f)
	{}

	template<typename... Args>
	R run(Args&&... args)
	{ 
		return m_fn(std::forward<Args>(args)...); 
	} 

	template<typename F> 
	auto then(F& f) -> Task<typename std::result_of<F(R)>::type(Args...)> 
	{
		return Task<typename std::result_of<F(R)>::type(Args...)>([this, &f](Args&&... args){
			return f(m_fn(std::forward<Args>(args)...)); });
	}

private:
	std::function<R(Args...)> m_fn;
};

void TestTask()
{
	Task<int(int)> task = [](int i){ return i; };
	auto result = task.then([](int i){return i + 1; }).then([](int i){return i + 2; }).then([](int i){return i + 3; }).run(1);
	cout << result << "\n";  //result 7
}

int main()
{
	TestCompose();
	cout << "*************************\n";
	TestTask();

	system("pause");
}