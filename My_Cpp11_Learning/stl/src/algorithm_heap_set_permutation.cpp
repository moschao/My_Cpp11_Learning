// ***********************************************************************
// Filename         : algorithm_heap_set_permutation.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : ������STL�еĶ��㷨�������㷨�������㷨��
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
#include <assert.h>
using namespace std;

//! set_union set_intersection set_difference set_symmetric_difference
//! make_heap push_heap pop_heap sort_heap
//! next_permutation prev_permutation

template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

//���ϲ����㷨
//includes                 : �ж�һ�������Ƿ�����һ�����ϵ��Ӽ�
//set_union                : ����һ���������У������������������еĲ��ظ�Ԫ��.
//set_intersection         : ����һ���������У�����Ԫ�������������ж�����.
//set_difference           : ����һ���������У������н�������һ�������д��ڵĶ��ڶ����в����ڵ�Ԫ��.
//set_symmetric_difference : ����һ���������У�������ȡ�������еĶԳƲ(����-����)
//! ��Щ�㷨����Ҫ�����������ϣ����������϶���Ҫ������������ͬ���������
void test_set_algorithm()
{
	vector<int> v1 = { 1, 2, 3, 4, 4, 5, 6, 6, 6, 9 };  //���ϲ���ʱ����Ҫ����������
	vector<int> v2 = { 0, 2, 3, 4, 5, 5, 6, 6 };  //���ϲ���ʱ����Ҫ����������
	vector<int> v = { 2, 3, 5, 6, 9 };
	if (std::includes(v1.begin(), v1.end(), v.begin(), v.end()))
		cout << "v is subse of v1\n";
	cout << "order 1 : ";
	print_all(v1.begin(), v1.end());
	cout << "order 2 : ";
	print_all(std::begin(v2), std::end(v2));

	v.clear();
	std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v));  //��
	cout << "union : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v), [](int e1, int e2){ return (e1 < e2); }); //��,Ĭ�ϼ���
	cout << "union : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v)); //��
	cout << "intersection : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::inserter(v, v.end())); //���
	cout << "difference : ";
	print_all(std::begin(v), std::end(v));

	v.clear();
	std::set_symmetric_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v)); //��ԳƲ�
	cout << "symmetric_difference : ";
	print_all(std::begin(v), std::end(v));
}

//�Ѳ����㷨
//make_heap : ��ָ����Χ�ڵ�Ԫ������һ���ѡ�Ĭ���ǽ������ѡ���int���ͣ������ڵ�������������greater<int>()�õ���С�ѡ�
//pop_heap  : �������������Ԫ�شӶ��е�����������������ѡ�����first��last-1������
//            Ȼ����������һ���ѡ���ʹ��������back�����ʱ�"����"��Ԫ�ػ���ʹ��pop_back����������ɾ��
//push_heap : ����first��last-1��һ����Ч�ѣ�Ҫ�����뵽�ѵ�Ԫ�ش����λ��last-1���������ɶѡ�
//            ��ָ��ú���ǰ�������Ȱ�Ԫ�ز���������
//sort_heap : ��ָ����Χ�ڵ�������������������������Ǹ�����ѡ����ذ汾ʹ���Զ���Ƚϲ���
void test_heap_algorithm()
{
	vector<int> vec;
	for (int i = 0; i < 10; ++i)
		vec.push_back(rand() % 100);
	print_all(vec.begin(), vec.end());

	std::make_heap(vec.begin(), vec.end()); //�����󶥶�
	print_all(vec.begin(), vec.end());

	//��������: ���������м��룬�ٵ���push_heap 
	vec.push_back(100);
	std::push_heap(vec.begin(), vec.end());
	print_all(vec.begin(), vec.end());

	//ɾ������: �ȵ���pop_heap������������ɾ��  
	std::pop_heap(vec.begin(), vec.end());
	vec.pop_back();
	print_all(vec.begin(), vec.end());

	//������  
	std::sort_heap(vec.begin(), vec.end());
	print_all(vec.begin(), vec.end());
}

//��������㷨
//next_permutation : ���ظ�����Χ�е�Ԫ����ɵ���һ�����ֵ��������
//prev_permutation : ���ظ�����Χ�е�Ԫ����ɵ���һ�����ֵ��������,�����������һ�������򷵻�false
//is_permutation   : �ж�һ�������Ƿ�����һ�����е�һ������
void test_permutation_algorithm()
{
	{
		vector<int> v = { 1, 2, 3, 4 }; //ȫ����ʱ��Ҫ��֤����next_permutation���ȡһ���δ��
		int sum = 1;
		//print_all(v.begin(), v.end());
		bool over = std::next_permutation(v.begin(), v.end());
		while (over)
		{
			sum++;
			//print_all(v.begin(), v.end());
			over = std::next_permutation(v.begin(), v.end());
		}
		cout << "total have " << sum << " permutation\n";
	}
	{
		vector<int> v = { 4, 3, 2, 1 }; //ȫ����ʱ��Ҫ��֤����prev_permutation��ǰȡһ����С��
		int sum = 1;
		bool over = std::prev_permutation(v.begin(), v.end());
		while (over)
		{
			sum++;
			//print_all(v.begin(), v.end());
			over = std::prev_permutation(v.begin(), v.end());
		}
		cout << "total have " << sum << " permutation\n";
	}
	{
		vector<int> v1 = { 1, 2, 3, 4 };
		vector<int> v2 = { 4, 3, 2, 1 };
		if (std::is_permutation(v1.begin(), v1.end(), v2.begin()))
			cout << "OK\n";
	}
	{   //����ϣ�7��Ԫ����ѡ3��
		int values[] = { 1, 2, 3, 4, 5, 6, 7 };
		int elements[] = { 1, 1, 1, 0, 0, 0, 0 };
		const size_t N = sizeof(elements) / sizeof(elements[0]);
		assert(N == sizeof(values) / sizeof(values[0]));
		std::vector<int> selectors(elements, elements + N);

		int count = 0;
		do
		{
			std::cout << ++count << ": ";
			for (size_t i = 0; i < selectors.size(); ++i)
			{
				if (selectors[i])
				{
					std::cout << values[i] << ", ";
				}
			}
			std::cout << std::endl;
		} while (prev_permutation(selectors.begin(), selectors.end()));
	}
}


int main()
{
	test_set_algorithm();
	std::cout << "===================\n";

	test_heap_algorithm();
	std::cout << "===================\n";

	test_permutation_algorithm();
	std::cout << "===================\n";

	getchar();
	return 0;
}