// ***********************************************************************
// Filename         : algorithm_sort.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : STL�е������㷨������ͨ���㷨
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-14
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <functional>
#include <cstdlib>
using namespace std;

//! sort stable_sort partial_sort partial_sort_copy partition stable_partition nth_element merge inplace_merge
//     �����ͨ���㷨 14��
//merge             : �ϲ������������У���ŵ���һ�����С����ذ汾ʹ���Զ���ıȽ�
//inplace_merge     : �ϲ������������У�������и������˷�Χ�����ذ汾ʹ������Ĳ�����������
//nth_element       : ����Χ�ڵ�������������ʹ����С�ڵ�n��Ԫ�ص�Ԫ�ض���������ǰ�棬���������Ķ������ں���
//partial_sort      : ���������������򣬱�����Ԫ�ظ������ÿ��Ա��ŵ���Χ��
//partial_sort_copy : ��partial_sort���ƣ�������������������и��Ƶ���һ������
//partition         : ��ָ����Χ��Ԫ����������ʹ������ĺ������ѽ��Ϊtrue��Ԫ�ط��ڽ��Ϊfalse��Ԫ��֮ǰ
//stable_partition  : ��partition���ƣ�������֤���������е����˳��
//random_shuffle    : ��ָ����Χ�ڵ�Ԫ����������������ذ汾����һ���������������
//shuffle           : ��ָ��������������������ָ����Χ�е�Ԫ�ص�λ��
//reverse           : ��ָ����Χ��Ԫ�����·�������
//reverse_copy      : ��reverse���ƣ����������д����һ������
//rotate            : ��ָ����Χ��Ԫ���Ƶ�����ĩβ����middleָ���Ԫ�س�Ϊ������һ��Ԫ��
//rotate_copy       : ��rotate���ƣ����������д����һ������
//sort              : ��������������ָ����Χ�ڵ�Ԫ�ء����ذ汾ʹ���Զ���ıȽϲ���
//stable_sort       : ��sort���ƣ������������Ԫ��֮���˳���ϵ(�����ȶ�����) 
//is_sorted         : C11�汾���ж������Ƿ�Ϊ�������
//is_sorted_until   : �������д�start iterator��ʼΪ����������еĽ�����
template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

void test_sort()
{
	{	// sort  stable_sort
		std::cout << "--------------   sort stable_sort   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, rand); //����10�������

		std::sort(v1.begin(), v1.end()); //Ĭ������
		print_all(v1.begin(), v1.end());

		vector<int> v2;
		std::generate_n(std::back_inserter(v2), 10, rand); //����10�������

		std::sort(v2.begin(), v2.end(), std::greater<int>()); //����
		//std::sort(v1.rbegin(), v1.rend());   // OK
		print_all(v2.begin(), v2.end());

		vector<int> v3 = { 3, 2, 1, 1, 2, 5, 7 };
		std::stable_sort(v3.begin(), v3.end()); //�ȶ�������ֵͬ�Ա���ԭ����
		print_all(v3.begin(), v3.end());
	}
	{	// is_sorted  is_sorted_until 
		vector<int> v1 = { 3, 1, 20, 4, 5, 9, 8 };
		if (std::is_sorted(v1.begin(), v1.end()))  //v1 is not sorted
			cout << "v1 is sorted\n";
		else
			cout << "v1 is not sorted\n";

		if (std::is_sorted(v1.begin() + 1, v1.end() - 1))  //subset of v1 is sorted
			cout << "subset of v1 is sorted\n";
		else
			cout << "subset of v1 is not sorted\n";

		vector<int>::iterator it_end = std::is_sorted_until(v1.begin(), v1.end());
		print_all(v1.begin(), it_end);   // 3 

		vector<int>::iterator it_start = v1.begin() + 1;
		it_end = std::is_sorted_until(it_start, v1.end());
		print_all(it_start, it_end);    // 1 20

		it_start = v1.begin() + 2;
		it_end = std::is_sorted_until(it_start, v1.end(), std::greater<int>());
		print_all(it_start, it_end);    // 1 20
	}
	{	// partial_sort
		std::cout << "--------------   partial_sort   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //����10�������
		print_all(v1.begin(), v1.end());

		std::partial_sort(v1.begin(), v1.begin() + 3, v1.end()); //ֻ������С����������������������Ҳ������
		print_all(v1.begin(), v1.end());

		std::partial_sort(v1.begin(), v1.begin() + 3, v1.end(), std::greater<int>()); //ֻ��������������������������
		print_all(v1.begin(), v1.end());

		std::partial_sort(v1.begin(), v1.begin() + v1.size(), v1.end()); //�൱��ֱ��������
		print_all(v1.begin(), v1.end());
	}
	{	// partial_sort_copy
		std::cout << "--------------   partial_sort_copy   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //����10�������
		print_all(v1.begin(), v1.end());

		vector<int> v2(v1.size());
		std::partial_sort_copy(v1.begin(), v1.end(), v2.begin(), v2.end());
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		vector<int> v3(v1.size());
		std::partial_sort_copy(v1.begin() + 3, v1.end(), v3.begin(), v3.end());
		print_all(v1.begin(), v1.end());
		print_all(v3.begin(), v3.end());
	}
	{	// partition
		std::cout << "--------------   partition   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //����10�������
		print_all(v1.begin(), v1.end());

		vector<int> v2(v1.size());
		std::partition(v1.begin(), v1.end(), [](int e){ return e > 50; }); //������50��������ǰ�棬����������
		print_all(v1.begin(), v1.end());

		int oddeven[] = { 1, 2, 3, 4, 5, 6 };
		std::partition(oddeven, oddeven + 6, [](int x){ return x % 2 != 0; }); //���򣬽���������ż��֮ǰ
		print_all(oddeven, oddeven + 6);
	}
	{	// stable_partition
		std::cout << "--------------   stable_partition   --------------\n";
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //����10�������
		print_all(v1.begin(), v1.end());

		vector<int> v2(v1.size());
		std::stable_partition(v1.begin(), v1.end(), [](int e){ return e > 50; }); //������50��������ǰ�棬���򱣳ֲ���
		print_all(v1.begin(), v1.end());

		int oddeven[] = { 1, 2, 3, 4, 5, 6 };
		std::stable_partition(oddeven, oddeven + 6, [](int x){ return x % 2 != 0; }); //���򣬽���������ż��֮ǰ
		print_all(oddeven, oddeven + 6);
	}
	{	// merge inplace_merge
		vector<int> v1 = { 1, 3, 4, 9 };
		int arr[] = { 2, 6, 7 };

		vector<int> v2(v1.size() + sizeof(arr) / sizeof(0[arr]));

		std::merge(v1.begin(), v1.end(), arr, arr + sizeof(arr) / sizeof(0[arr]), v2.begin()); //��������
		print_all(v2.begin(), v2.end());

		vector<int> v3 = { 1, 3, 6, 9, 2, 5, 8 };  //[0, 4)��[4, 7)�ֱ����򣬽����������кϲ����������еķ�Χ[0, 7)
		auto it = adjacent_find(v3.begin(), v3.end(), std::greater<int>());
		std::inplace_merge(v3.begin(), v3.begin() + 4, v3.end());
		print_all(v3.begin(), v3.end());
	}
	{	// nth_element random_shuffle shuffle
		vector<int> v1;
		std::generate_n(std::back_inserter(v1), 10, []{return rand() % 100; }); //����10�������
		print_all(v1.begin(), v1.end());

		std::nth_element(v1.begin(), v1.begin() + 1, v1.end()); //����С��Ԫ�ط�������ǰ��
		print_all(v1.begin(), v1.end());

		std::sort(v1.begin(), v1.end());
		std::random_shuffle(v1.begin(), v1.end());
		print_all(v1.begin(), v1.end());

		std::sort(v1.begin(), v1.end());
		//std::shuffle(v1.begin(), v1.end(), rand);
		print_all(v1.begin(), v1.end());
	}
	std::cout << "======================\n";
}

int main()
{
	test_sort();
}