#include <iostream>
#include <memory>
#include <chrono>
#include <functional>
using namespace std;
//#include <boost/chrono/chrono.hpp>
//#include <boost/chrono/system_clocks.hpp>
// AOP : Aspect Oriented Programming, ��Ϊ������������.
// ͨ��Ԥ���뷽ʽ�������ڶ�̬����ʵ�ֳ����ܵ�ͳһά����һ�ּ�����
// AOP��OOP������������������е�һ���ȵ㣬Ҳ��Spring����е�һ����Ҫ���ݣ��Ǻ���ʽ��̵�һ���������͡�
// ����AOP���Զ�ҵ���߼��ĸ������ֽ��и��룬�Ӷ�ʹ��ҵ���߼�������֮�����϶Ƚ��ͣ���߳���Ŀ������ԣ�ͬʱ����˿�����Ч�ʡ�
// see http://www.cnblogs.com/qicosmos/p/3154174.html
// ����ģʽ�����ڲ��ı�ԭ�д����߼�������£� ֻ�ڽӿڵ��ô���֯���棬���ɶԱ����ӿڽ���һϵ��ע�ᡢ��¼����������Ϊ����

template <typename WrappedType, typename DerivedAspect>
class BaseAspect
{
protected:
	WrappedType* m_wrappedPtr; //��֯��Ķ���

	//��ȡ�������������
	DerivedAspect* GetDerived()
	{
		return static_cast<DerivedAspect*>(this);
	}

	//��֯������ɾ�����������Զ����������е�After����
	struct AfterWrapper
	{
		DerivedAspect* m_derived;
		AfterWrapper(DerivedAspect* derived) : m_derived(derived) {};
		void operator()(WrappedType* p)
		{
			m_derived->After(p);
		}
	};
public:
	explicit BaseAspect(WrappedType* p) : m_wrappedPtr(p) {};


	void Before(WrappedType* p) {
		// Default does nothing
	};

	void After(WrappedType* p) {
		// Default does nothing
	}

	//����ָ�����������֯�����棨Before��After��
	std::shared_ptr<WrappedType> operator->()
	{
		GetDerived()->Before(m_wrappedPtr);
		return std::shared_ptr<WrappedType>(m_wrappedPtr, AfterWrapper(GetDerived()));
	}
};

//֯������Ĺ�������, ���ذ�����֯����������
template <template <typename> class Aspect, typename WrappedType>
Aspect<WrappedType> MakeAspect(WrappedType* p)
{
	return Aspect<WrappedType>(p);
}

template<typename WrappedType>
class TimeElapsedAspect : public BaseAspect< WrappedType, TimeElapsedAspect<WrappedType> >
{
	typedef  BaseAspect<WrappedType, TimeElapsedAspect<WrappedType> > BaseAspect;
	typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double> > time_point;

	time_point m_tmBegin;
public:
	TimeElapsedAspect(WrappedType* p) : BaseAspect(p) {}


	void Before(WrappedType* p)
	{
		m_tmBegin = std::chrono::system_clock::now();
	}

	void After(WrappedType* p)
	{
		time_point end = std::chrono::system_clock::now();

		std::cout << "Time: " << (end - m_tmBegin).count() << std::endl;
	}
};

template <typename WrappedType>
class LoggingAspect : public BaseAspect<WrappedType, LoggingAspect<WrappedType> >
{
	typedef  BaseAspect<WrappedType, LoggingAspect<WrappedType> > BaseAspect;
public:
	LoggingAspect(WrappedType* p) : BaseAspect(p) {}

	void Before(WrappedType* p)
	{
		std::cout << "entering" << std::endl;
	}

	void After(WrappedType* p)
	{
		std::cout << "exiting" << std::endl;
	}

};

class IX
{
public:
	IX(){}
	virtual ~IX(){}

	virtual void g() = 0;
private:

};

class X : public IX
{
public:
	void g()
	{
		std::cout << "it is a test" << std::endl;
	}

};

void TestAop()
{
	std::shared_ptr<IX> p(new X());
	MakeAspect<TimeElapsedAspect>(p.get())->g();
	MakeAspect<LoggingAspect>(p.get())->g();
}

// ------------------------------------------------------------ //
struct Aspect
{
	template<typename Func>
	Aspect(const Func& f) : m_func(f)
	{

	}

	template<typename T>
	void Invoke(T&& value)
	{
		value.Before();
		m_func();
		value.After();
	}

	template<typename Head, typename... Tail>
	void Invoke(Head&& head, Tail&&... tail)
	{
		head.Before();
		Invoke(std::forward<Tail>(tail)...);
		head.After();
	}
private:
	Aspect(const Aspect&) = delete;
	Aspect& operator=(const Aspect&) = delete;

private:
	std::function<void()> m_func;
};

template <typename T> 
using identity_t = T;

template<typename... AP>
void Invoke(const std::function<void()>& f)
{

	Aspect msp(f);
	//msp.Invoke(AP()...);    // gcc is ok
	msp.Invoke(identity_t<AP>()...);   // vs203 is ok
}

struct AA
{
	void Before()
	{
		cout << "Before from AA" << endl;
	}

	void After()
	{
		cout << "After from AA" << endl;
	}
};

struct BB
{
	void Before()
	{
		cout << "Before from BB" << endl;
	}

	void After()
	{
		cout << "After from BB" << endl;
	}
};

struct CC
{
	void Before()
	{
		cout << "Before from CC" << endl;
	}

	void After()
	{
		cout << "After from CC" << endl;
	}
};

struct TT
{
	void g()
	{
		cout << "real g function" << endl;
	}

	void h(int a)
	{
		cout << "real h function: " << a << endl;
	}
};

struct DD
{
	void Before()
	{

	}

	void After()
	{

	}
};

void GT()
{
	cout << "real GT function" << endl;
}

void HT(int a)
{
	cout << "real HT function: " << a << endl;
}

void TestAOP()
{
	TT tt;
	std::function<void()> ff = std::bind(&TT::g, &tt);
	//�������������AA BB
	Invoke<AA, BB>([&ff](){ ff(); }); //֯���Ա����
	cout << "-------------\n";

	Invoke<AA, BB>([&tt](){ tt.g(); }); //֯�����
	cout << "-------------\n";

	int aa = 3;
	Invoke<AA, BB>(&GT); //֯�뷽��
	cout << "-------------\n";

	Invoke<AA, BB>([aa](){HT(aa); });//֯����εķ���
	cout << "-------------\n";

	//֯��������ĳ�Ա�����Ͷ���
	std::function<void(int)> ff1 = std::bind(&TT::h, &tt, std::placeholders::_1);
	Invoke<AA, BB, CC, DD>([&ff1, aa](){ff1(aa); }); //������ĸ�����
	cout << "-------------\n";

	Invoke<AA, BB>([&tt, aa](){tt.h(aa); });
	cout << "-------------\n";
}

int main()
{
	TestAop();
	cout << "------------------------------------\n";

	TestAOP();

	system("pause");
}