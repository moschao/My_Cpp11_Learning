#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
using namespace std;
//http://cpp1x.org/Thread.html  http://zh.cppreference.com/w/cpp/thread

//          std::thread
/***
std::thread�ĳ�Ա������
join   :���������߳�(������ס�߳�)��ֱ�����߳����н�����
swap   : �������̵߳���ز���(underlying handles)������
detach : �����̶߳���������������С�Detach ���̲߳��ٿ�����(�㲻�õ�������)��

std::this_thread�ṩ�ĺ���
get_id    : ���ص�ǰ�̵߳� ID��
yield     : ���ߵ��ȳ������������߳�(���㴦��æ�ȴ���ʱ��ǳ�����)��
sleep_for : ������ǰ�߳�ֱ��ָ����ʱ��(sleep_duration)��
sleep_util: ������ǰ�߳�ֱ��ָ����ʱ��(sleep_time)��
***/
void func1()
{
	std::cout << "func1()\n";
}

// ��������ޅ�����func1ͬ�����ᵼ�������������޷���Ϊthread���̺߳���
// cannot convert argument 1 from 'overloaded-function' to 'std::thread &&'
//void func1(int& a) 
//{
//	std::cout << "func(int& a)\n";
//}

//���Ը��̺߳������������Ĳ���
void func2(int i, double d, const std::string& s)
{
	std::cout << i << ", " << d << ", " << s << "\n";
	std::cout << "func2()\n";
}

//�����÷�ʽ���ݣ�ע���̺߳���Ĭ�϶�����ֵ��ʽ���ݵģ�����ʹ�� std::ref ����std::cref ����ת��
void func3(int& a)
{
	a ++;
	std::cout << "func3()\n";
}

int func4(const int& a)
{
	std::cout << "func4()\n";
	return a + 100;
}

class SomeClass
{
public:
	int PrintString(const std::string& str) { std::cout << str << "\n";  return 1; }
};

void test_thread()
{
	std::cout << "test_thread id: " << std::this_thread::get_id() << "\n";
	{
		std::thread t(func1); //��ס�����ﲻ�������أ�Ҳ������������ͬ������func1����ʹ����ǩ����һ��
		std::cout << t.get_id() << "\t" << std::this_thread::get_id() << "\n";
		t.join();
		std::cout << t.get_id() << "\t" << std::this_thread::get_id() << "\n";
		//t.detach();
		std::cout << "-----------------------\n";
	}
	{   //���ݶ������
		std::thread t(func2, 1, 12.50, "sample");
		t.join();
		std::cout << "-----------------------\n";
	}
	{	//�����÷�ʽ����ʱ�����ݵĲ�������ʹ�� std::ref ����std::cref ����ת��		
		int a = 42;
		std::thread t(func3, std::ref(a));
		t.join();
		std::cout << a << std::endl;
		std::cout << "-----------------------\n";
	}
	{	//��const���÷�ʽ����		
		int a = 42;
		std::thread t(func4, std::cref(a));
		t.join();
		std::cout << a << std::endl;
		std::cout << "-----------------------\n";
	}
	{	//�����Ա����Ϊ�߳�ִ�к���
		
		SomeClass sc;
		std::string str("Hello,World!");
		std::thread t(&SomeClass::PrintString, &sc, std::cref(str));
		t.join();		
		std::cout << "-----------------------\n";
	}
}


//          std::mutex
/***
C++11 �� <mutex> ͷ�ļ����ṩ������ mutex ����ͬ������:
mutex           : �ṩ�˺��ĺ��� lock(), unlock() �� �������� trylock_() ����(�ж� mutex �Ƿ����)��
recursive_mutex : ������ͬ�̶߳�λ��mutex��
timed_mutex     : ��mutex�����ƣ����������Լ����������ķ���trylock__for()��rylock__until(),����������ָ����ʱ��λ���ʱ����ȡmutex��
recursive_timed_mutex : timed_mutex �� recursive_mutex ���ۺ���
***/
std::mutex glock_;
void func()
{
	std::lock_guard<std::mutex> locker(glock_);
	//glock_.lock();
	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
	//glock_.unlock();
}

void test_mutex()
{
	srand((unsigned int)time(0));

	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);

	t1.join();
	t2.join();
	t3.join();
}

//           safe container
template <typename T>
class container
{
public:
	void add(T element)
	{
		std::lock_guard<std::recursive_mutex> locker(lock_);
		elements_.push_back(element);
	}

	void addrange(int num, ...)
	{
		va_list arguments;

		va_start(arguments, num);
		for (int i = 0; i < num; i++)
		{
			std::lock_guard<std::recursive_mutex> locker(lock_);
			add(va_arg(arguments, T));
		}
		va_end(arguments);
	}

	void dump()
	{
		std::lock_guard<std::recursive_mutex> locker(lock_);
		std::copy(elements_.begin(), elements_.end(), std::ostream_iterator<T>(std::cout, "\t"));
		std::cout << "\n";
	}
private:
	std::recursive_mutex lock_; //���ﲻ��ʹ��mutex����Ϊaddrange�����addʱ��λ�ȡ�����������������ȻҲ�������취����ȡ������
	std::vector<T> elements_;
};

void test_safe_vector()
{
	container<int> cc;
	cc.add(1);
	cc.addrange(5, 3, 4, 5, 6, 9);
	cc.dump();
}

//         dead lock
class SomeType
{
public:
	std::mutex mutex_;
};

void ChangeTwoObj(SomeType& lhs, SomeType& rhs)
{
	//lhs.mutex_.lock();  //��������������������
	//rhs.mutex_.lock();
	std::lock(lhs.mutex_, rhs.mutex_); // Ok, ��������

	//do something .....

	lhs.mutex_.unlock();
	rhs.mutex_.unlock();
	std::cout << "ChangeTwoObj Over\n";
}

void test_deadlock()
{
	SomeType s1, s2;

	std::thread t1(ChangeTwoObj, std::ref(s1), std::ref(s2));
	std::thread t2(ChangeTwoObj, std::ref(s2), std::ref(s1));
	t1.join();
	t2.join();
}


//         condition variable
/***
ע�⣺
std::condition_variableֻ������std::unique_lock<std::mutex>��
condition_variable_any�����������κ��û����������������BasicLockableҪ��
condition_variable_any�ṩ������std::condition_variable�Ĺ��ܣ�����һ��������������һЩ�̵߳�ͬ��ԭ�
***/
void test_condition_variable()
{
	std::queue<int> produced_nums;
	std::mutex m;
	std::condition_variable cond_var;
	bool done = false;
	bool notified = false;

	std::thread producer([&]() {
		for (int i = 0; i < 5; ++i) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::unique_lock<std::mutex> lock(m);
			std::cout << "producing " << i << '\n';
			produced_nums.push(i);
			notified = true;
			cond_var.notify_one();
		}

		done = true;
		cond_var.notify_one();
	});

	std::thread consumer([&]() {
		std::unique_lock<std::mutex> lock(m);
		while (!done) {
			while (!notified) {  // loop to avoid spurious wakeups
				cond_var.wait(lock);
			}
			while (!produced_nums.empty()) {
				std::cout << "consuming " << produced_nums.front() << '\n';
				produced_nums.pop();
			}
			notified = false;
		}
	});

	producer.join();
	consumer.join();
}

//         std::call_once
std::once_flag once_init;
int one = 0, two = 0;
void only_call_once()
{
	one++;
	std::cout << "only_call_once\n";
}
void add_num()
{
	std::call_once(once_init, &only_call_once); //��������ʵ�ֵ�������
	two++;
	std::cout << "add_num\n";
}
void test_call_once()
{
	const int thread_num = 5;
	std::thread threads[thread_num];
	for (int i = 0; i < thread_num; ++i)
	{
		threads[i] = std::thread(add_num);
	}
	for (auto& th : threads)
	{
		th.join();
	}

	std::cout << one << "\t" << two << "\n";  // 1 5
}

//         Futures: promise��future
/***  http://www.cnblogs.com/haippy/p/3280643.html
promise������Ա���ĳһ����T��ֵ����ֵ�ɱ�future�����ȡ������������һ���߳��У������promiseҲ�ṩ��һ���߳�ͬ�����ֶΡ�
��promise������ʱ���Ժ�һ������״̬��ͨ����std::future�����������������������Ĺ���״̬(std::future)�ϱ���һ������Ϊ T ��ֵ��
����ͨ�� get_future ����ȡ��� promise ����������� future ���󣬵��øú���֮��������������ͬ�Ĺ���״̬(shared state):
	promise �������첽 Provider����������ĳһʱ�����ù���״̬��ֵ��
	future ��������첽���ع���״̬��ֵ�������ڱ�Ҫ����������������߲��ȴ�����״̬��־��Ϊ ready��Ȼ����ܻ�ȡ����״̬��ֵ��
***/
void print_int(std::future<int>& fut) {
	int x = fut.get(); // ��ȡ����״̬��ֵ.
	std::cout << "value: " << x << '\n'; // value: 10.
}

void test_future_promise()
{
	std::promise<int> prom;					  // ����һ�� std::promise<int> ����.
	std::future<int> fut = prom.get_future(); // �� future ����.
	std::thread t(print_int, std::ref(fut));  // �� future ��������һ���߳�t.
	prom.set_value(10);						  // ���ù���״̬��ֵ, �˴����߳�t����ͬ��.

	t.join();
}
/***
std::packaged_task ��װһ���ɵ��õĶ��󣬲��������첽��ȡ�ÿɵ��ö�������Ľ�����Ӱ�װ�ɵ��ö���������������std::packaged_task �� std::function ���ƣ�
ֻ���� std::packaged_task �����װ�Ŀɵ��ö����ִ�н�����ݸ�һ�� std::future ���󣨸ö���ͨ��������һ���߳��л�ȡ std::packaged_task �����ִ�н������

std::packaged_task �����ڲ����������������Ԫ�أ�
	һ������װ������(stored task)������(task)��һ���ɵ��õĶ����纯��ָ�롢��Ա����ָ����ߺ�������
	��������״̬(shared state)�����ڱ�������ķ���ֵ������ͨ�� std::future �������ﵽ�첽���ʹ���״̬��Ч����
����ͨ�� std::packged_task::get_future ����ȡ�빲��״̬������� std::future �����ڵ��øú���֮��������������ͬ�Ĺ���״̬������������£�
	std::packaged_task �������첽 Provider������ĳһʱ��ͨ�����ñ���װ�����������ù���״̬��ֵ��
	std::future ������һ���첽���ض���ͨ�������Ի�ù���״̬��ֵ����Ȼ�ڱ�Ҫ��ʱ����Ҫ�ȴ�����״̬��־��Ϊ ready.
	std::packaged_task �Ĺ���״̬����������һֱ���������һ����֮������Ķ����ͷŻ�������Ϊֹ��
***/
// count down taking a second for each value:
int countdown(int from, int to)
{
	for (int i = from; i != to; --i) 
	{
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Finished!\n";
	return from - to;
}

void test_future_packaged_task()
{
	{
		std::packaged_task<int(int, int)> task(countdown);  // ���� packaged_task
		std::future<int> ret = task.get_future();			// ����� packaged_task ����״̬������� future ����.

		std::thread th(std::move(task), 10, 0);				//����һ�����߳���ɼ�������.

		int value = ret.get();								// �ȴ�������ɲ���ȡ���.
		std::cout << "The countdown lasted for " << value << " seconds.\n";
		th.join();
	}
	{
		std::packaged_task<int(int)> tsk([](int x) { return x * 3; }); // package task
		std::future<int> fut = tsk.get_future();		// ��ȡ future ����.
		std::thread(std::move(tsk), 100).detach();		// �������̲߳�����packaged_task.
		int value = fut.get();							// �ȴ��������, ����ȡ���.
		std::cout << "The triple of 100 is " << value << ".\n";
	}
}

/***
std::future ����������ȡ�첽����Ľ������˿��԰�������һ�ּ򵥵��̼߳�ͬ�����ֶΡ�
һ����Ч�� std::future ����ͨ������������ Provider ����������ĳ������״̬�������Provider �����Ǻ��������࣬���Ƿֱ��ǣ�
	std::async ������
	std::promise::get_future��get_future Ϊ promise ��ĳ�Ա������
	std::packaged_task::get_future����ʱ get_futureΪ packaged_task �ĳ�Ա������
***/
int do_get_value() { return 10; }
bool do_check_prime(int x) 
{
	for (int i = 2; i < x; ++i)
		if (x % i == 0)
			return false;
	return true;
}
double ThreadTask(int n) 
{
	std::cout << std::this_thread::get_id() << " start computing..." << std::endl;
	double ret = 0;
	for (int i = 0; i <= n; i++) 
		ret += std::sin(i);
	std::cout << std::this_thread::get_id()	<< " finished computing..." << std::endl;
	return ret;
}
void do_print_ten(char c, int ms)
{
	for (int i = 0; i < 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		std::cout << c;
	}
}
void test_future()
{
	{
		std::future<int> fut = std::async(do_get_value);
		std::shared_future<int> shared_fut = fut.share();

		// ����� future ������Ա���η���.
		std::cout << "value: " << shared_fut.get() << '\n';
		std::cout << "its double: " << shared_fut.get() * 2 << '\n';
	}
	{
		// call function asynchronously:
		std::future < bool > fut = std::async(do_check_prime, 194232491);
		std::cout << "Checking...\n";
		fut.wait();		//��������ǰ�̣߳�ֱ������״̬�ı�־��Ϊ ready
		std::cout << "194232491 ";
		if (fut.get())  // guaranteed to be ready (and not block) after wait returns
			std::cout << "is prime.\n";
		else
			std::cout << "is not prime.\n";
	}
	{
		// call function asynchronously:
		std::future < bool > fut = std::async(do_check_prime, 194232491);

		std::cout << "Checking...\n";
		std::chrono::milliseconds span(10); // ���ó�ʱ���.

		// �����ʱ�������"."�������ȴ�
		while (fut.wait_for(span) == std::future_status::timeout) //������ֱ���ȴ���span��ʱ���wait_until()����
			std::cout << '.';

		std::cout << "\n194232491 ";
		if (fut.get()) // guaranteed to be ready (and not block) after wait returns
			std::cout << "is prime.\n";
		else
			std::cout << "is not prime.\n";
	}
	{
		std::future<double> f(std::async(std::launch::async, ThreadTask, 100000000)); //async�൱��һ���̵߳���
#if 0
		while (f.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(1))!= std::future_status::ready) 
		{
			std::cout << "task is running...\n";
		}
#else
		while (f.wait_for(std::chrono::seconds(1))!= std::future_status::ready) 
		{
			std::cout << "task is running...\n";
		}
#endif
		std::cout << f.get() << std::endl;
	}
	{
		std::cout << "with launch::async:\n";
		std::future < void >foo =
			std::async(std::launch::async, do_print_ten, '*', 100);
		std::future < void >bar =
			std::async(std::launch::async, do_print_ten, '@', 200);
		// async "get" (wait for foo and bar to be ready):
		foo.get();
		bar.get();
		std::cout << "\n\n";

		std::cout << "with launch::deferred:\n";
		foo = std::async(std::launch::deferred, do_print_ten, '*', 100);
		bar = std::async(std::launch::deferred, do_print_ten, '@', 200);
		// deferred "get" (perform the actual calls):
		foo.get();
		bar.get();
		std::cout << '\n';
	}
}

int main()
{
	//test_thread();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_mutex();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_safe_vector();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_deadlock();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_condition_variable();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_call_once();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_future_promise();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_future_packaged_task();
	std::cout << "- - - - - - - - - - - - -\n";

	test_future();
	std::cout << "- - - - - - - - - - - - -\n";

	getchar();
	return 0;
}