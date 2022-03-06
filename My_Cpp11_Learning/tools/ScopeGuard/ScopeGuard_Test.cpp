#include <iostream>
#include "ScopeGuard.h"

#define Safe_Delete(p) { delete p; p = nullptr; }
class SC
{
public:
	SC(int n = 0) : num(n)
	{
		std::cout << this << " SC Construction\n";
	}
	~SC()
	{
		std::cout << this << " SC Deconstruction\n";
	}
	bool Fail()
	{
		num += 100;
		std::cout << this <<" SC Fail, num = " << num << "\n";
		return true;
	}
	bool Success()
	{
		num += 1000;
		std::cout << this << " SC Success, num = " << num << "\n";
		return true;
	}
	void RollBack()
	{
		num = 0;
		std::cout << this << " SC RollBack, num = " << num << "\n";
	}
	void Print()
	{
		std::cout << this << " SC num : " << num << "\n";
	}
private:
	int num;
};

void test_scope_guard()
{
	{
		int *pi = new int;
		ZL::ScopeGuard onExit([&] { delete pi; pi = nullptr; });
	}
	{
		SC *sc = new SC;
		ZL::ON_SCOPE_EXIT([&sc]{ delete sc; sc = nullptr; }); // Ok
		//ON_SCOPE_EXIT([&sc]{ Safe_Delete(sc) }); // Ok		
	}
	std::cout << "===================\n";
	{
		SC *sc = new SC;
		//ON_SCOPE_EXIT([&sc]{ Safe_Delete(sc) });
		ZL::ScopeGuard rollbackIfFail([&]{ sc->RollBack(); });
		do
		{
			//do something.....
			if (sc->Fail())
			{
				break;
			}
			rollbackIfFail.dismiss(); //����ifʧ�ܣ��߲��������˻ᵼ��ScopeGuardִ��sc��RollBack����
		} while (0);
	}
	std::cout << "===================\n";
	{
		SC *sc = new SC(1);
		ZL::ON_SCOPE_EXIT([&sc]{ Safe_Delete(sc) });
		ZL::ScopeGuard rollbackIfFail([&]{ sc->RollBack(); });
		do
		{
			//do something.....
			if (!sc->Success())
			{
				break;
			}
			rollbackIfFail.dismiss(); //ִ�е��������ȡ��rollback���ƣ�ִ�гɹ�
		} while (0);
	}
	std::cout << "===================\n";
}

int main()
{
	test_scope_guard();

	std::cout << "OK\n";
	getchar();
	return 0;
}
