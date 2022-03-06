// ***********************************************************************
// Filename         : algorithm_create_update_delete.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : STL�еı����㷨(���ɡ����졢�޸ġ��滻��ɾ����)
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
using namespace std;

//! �����㷨(Mutating algorithms)����һ���ܹ��޸�����Ԫ�����ݵ�ģ�庯�����ɽ����������ݵĸ��ƣ��任��
//! fill fill_n for_each generate generate_n transform
//! copy copy_backward copy_if copy_n
//! swap iter_swap swap_ranges
//! replace replace_if replace_copy replace_copy_if
//! remove  remove_if  remove_copy  remove_copy_if
//! reverse reverse_copy rotate rotate_copy
//! unique unique_copy
template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

//! ���ɺͱ����㷨
//fill       : ��һ����Χ��Ԫ�ظ�ֵΪ����ֵ
//fill_n     : ��ĳ��λ�ÿ�ʼ�� n ��Ԫ�ظ�ֵΪ����ֵ
//generate   : ��һ��������ִ�н�����浽ָ����Χ��Ԫ���У�����������ֵ��Χ�е�Ԫ��
//generate_n : ��һ��������ִ�н�����浽ָ��λ�ÿ�ʼ�� n ��Ԫ����
//transform  : ��ָ����Χ�е�ÿ��Ԫ�ص���ĳ�������Ըı�Ԫ�ص�ֵ.
//             ���ذ汾������������һ��Ԫ���ϣ�����һ��Ԫ���������������һ�����С���������ָ������
void test()
{
	{
		vector<int> vec(6);

		std::fill(vec.begin(), vec.end(), 2);
		print_all(vec.begin(), vec.end());

		//���ӵڶ���Ԫ�ؿ�ʼ��3��Ԫ���޸�Ϊ5
		std::fill_n(vec.begin() + 1, 3, 5);
		print_all(vec.begin(), vec.end());
	}
	{
		vector<int> vec(6);

		std::generate(vec.begin(), vec.end(), []{ return rand() % 10; });
		print_all(vec.begin(), vec.end());

		//��ǰ����Ԫ���޸�Ϊ1 2 3
		std::generate_n(vec.begin(), 3, []{static int i = 1; return i++; });
		print_all(vec.begin(), vec.end());
	}
	{
		vector<int> vec = { 1, 2, 3, 4, 5 };
		std::transform(vec.begin(), vec.end(), vec.begin(), [](int x){return x*x; });
		print_all(vec.begin(), vec.end());

		vec = { 1, 2, 3, 4, 5 };
		vector<int> vec2 = { 2, 3, 4, 5, 6, 9 };
		//��vec2�е�Ԫ����ζ�Ӧ��ӵ�vec��
		std::transform(vec.begin(), vec.end(), vec2.begin(), vec.begin(), [](int x, int y){ return x + y; });
		print_all(vec.begin(), vec.end());
	}
	{

	}
}

//        ɾ�����滻�㷨 15��
//copy    : ��һ����Χ�е�Ԫ�ؿ������µ�λ�ô� 
//copy_backward : ��һ����Χ�е�Ԫ�ذ����򿽱����µ�λ�ô�, ����������,������Ԫ�ؿ�ʼ���ƣ�ֱ����Ԫ�ظ��Ƴ�����
//                ���Ʋ����Ǵ�last-1��ʼ��ֱ��first����.����һ����������ָ���ѱ�����Ԫ���������ʼλ��
//copy_if :	��һ����Χ���������������Ԫ�ؿ������µ�λ�ô�
//copy_n  : ���� n ��Ԫ�ص��µ�λ�ô�
void test_copy()
{
	{   //copy copy_backward copy_if copy_n
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		vector<int> v2;
		v2.resize(v1.size());

		std::copy(v1.begin(), v1.end(), v2.begin());
		print_all(v2.begin(), v2.end());

		v2.resize(v1.size() * 2);
		std::copy(v1.begin(), v1.end(), v2.begin() + 2);
		std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, " "));  std::cout << "\n";

		std::copy(v1.begin() + 1, v1.end(), v1.begin()); //��Ԫ���������󸲸�ԭԪ��
		print_all(v1.begin(), v1.end());  // 2 3 4 5 6 6

		vector<int> v3(v1.size());
		auto it = std::copy_if(v1.begin(), v1.end(), v3.begin(), [](int e){ return e % 2 == 0; }); //ֻ����ż��
		print_all(v3.begin(), it); // 2 4 6 6

		v3.clear();
		std::copy_n(v1.begin() + 1, 3, std::back_inserter(v3));
		print_all(v3.begin(), v3.end());
	}
	{
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		auto iter = std::copy_backward(v1.begin(), v1.begin() + 2, v1.end()); //�Ӻ���ǰ���ƣ����Ƶ��ӽ�β��ʼ�ĺ�����Ԫ��
		print_all(v1.begin(), v1.end()); // 1 2 3 4 1 2
		cout << "copy elems : ";	print_all(iter, v1.end());
	}
	std::cout << "======================\n";
}

//swap: ����Ԫ��
//iter_swap: ͨ������������Ԫ�صĽ���
//swap_ranges: ����Ԫ�ؽ���
void test_swap()
{
	{
		vector<int> v1 = { 1, 2, 3, 4 };
		vector<int> v2 = { 5, 6, 7, 8, 9 };

		std::swap(v1, v2);
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		v2.swap(v1);
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		vector<int>().swap(v2);  //�ͷ���v2���ڴ�ռ��
		print_all(v2.begin(), v2.end());
	}
	{
		vector<int> v1 = { 1, 2, 3, 4, 5 };
		std::swap(v1[0], v1[1]);
		std::iter_swap(&v1[3], &v1[4]);
		print_all(v1.begin(), v1.end());
	}
	{
		vector<int> v1 = { 1, 2, 3, 4 };
		vector<int> v2 = { 5, 6, 7, 8, 9 };
		std::swap_ranges(v1.begin() + 1, v1.end(), v2.begin()); //��v1�ӵڶ���Ԫ�غ������������v2�ӿ�ʼԪ�ؽ��н���
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());
	}
	std::cout << "======================\n";
}

//replace: ��ָ��Ԫ��ֵ�滻Ϊ��ֵ
//replace_if: �������ν���������滻
//replace_copy: ������1��Ԫ�ؿ���������2�������滻ĳԪ��ֵΪ��ֵ����������
//replace_copy_if: ������1��Ԫ�ؿ���������2�������滻����ν��������ĳԪ��ֵΪ��ֵ����������
void test_replace()
{
	{	//replace
		vector<int> v1 = { 3, 2, 3, 3, 4, 5, 3 };
		std::replace(v1.begin() + 1, v1.end(), 3, 9); ///��v1�ӵڶ���Ԫ�غ������ֵΪ3��Ԫ���滻Ϊ9
		print_all(v1.begin(), v1.end());
	}
	{	//replace_if
		vector<int> v1 = { 1, 2, 3, 3, 4, 5, 3 };
		std::replace_if(v1.begin() + 1, v1.end(), [](int e){ return e >= 3; }, 9); //�����д��ڵ���3��Ԫ���滻Ϊ9
		print_all(v1.begin(), v1.end());
	}
	{	//replace_copy
		const vector<int> v1 = { 1, 2, 3, 3, 4, 5, 3 };
		vector<int> v2(v1.size());
		std::replace_copy(v1.begin(), v1.end(), v2.begin(), 3, 8); //��v1������Ԫ�ظ��Ƶ�v2�У����ǵ���3��Ԫ��ֱ���滻Ϊ8�����ı�v1
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());
	}
	{	//replace_copy_if
		vector<int> v1 = { 1, 2, 3, 3, 4, 5, 3 };
		vector<int> v2(v1.size());
		std::replace_copy_if(v1.begin(), v1.end(), v2.begin(), [](int e){ return e >= 3; }, 8); //��v1������Ԫ�ظ��Ƶ�v2�У������ֵ����ν���������滻Ϊ8�����ı�v1
		print_all(v1.begin(), v1.end());
		print_all(v2.begin(), v2.end());

		std::replace_copy_if(v1.begin(), v1.end(), v1.begin(), [](int e){ return e >= 3; }, 8); //ԭ���û�
		print_all(v1.begin(), v1.end());
	}
	std::cout << "======================\n";
}

//remove: ��һ����Χ��ֵ�ȼ��ڸ���ֵ��Ԫ��ɾ��.��������ɾ�������е�Ԫ��(ֻ�Ǻ���)��
//        ����һ���µ�end()����Ϊԭ���������Ƴ�ָ��ֵ����Ԫ��ǰ�ƺ��ĩβ����һ��λ�á�����ԭ��������end()������ı䡣
//remove_if: ��������ɾ������ν��������Ԫ��
//remove_copy : ����һ����Χ��Ԫ�أ�������ֵ�ȼ��ڸ���ֵ��Ԫ��ɾ��
//remove_copy_if : ����һ����Χ��Ԫ�أ�������ֵ�������������Ԫ��ɾ��
void test_remove()
{
	{	//remove
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		auto it = std::remove(v1.begin(), v1.end(), 3); //"ɾ��"�����е����е�3�������������������һ��Ԫ�ص���һ��λ��  
		print_all(v1.begin(), v1.end());	//1 2 4 4 2 1 2 1 (remove������3���������λ�õ�2��Ԫ����Ȼ����ԭֵ)
		print_all(it, v1.end());

		vector<int> v2 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		it = v2.erase(std::remove(v2.begin(), v2.end(), 3), v2.end()); //���Ҫɾ�������Ļ�����remove�ĺ����erase
		print_all(v2.begin(), v2.end());	//1 2 4 4 2 1
	}
	{	//remove_if
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		auto it = std::remove_if(v1.begin(), v1.end(), [](int e){ return e > 3; }); //"ɾ��"���д���3��Ԫ��
		print_all(v1.begin(), it); //��ʾ�������ϵ�Ԫ��
		print_all(it, v1.end());   //��ʾ����Ԫ��
	}
	{	//remove_copy
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		vector<int> v2(v1.size());
		// �� intList �г�ֵΪ34�����Ԫ�أ������temp1�У����ı� intList��  
		auto it = std::remove_copy(v1.begin(), v1.end(), v2.begin(), 3);
		print_all(v2.begin(), it); //��ʾ�������ϵ�Ԫ��
	}
	{	//remove_copy_if
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1 };
		vector<int> v2(v1.size());
		auto it = std::remove_copy_if(v1.begin(), v1.end(), v2.begin(), [](int e){ return e > 3; });
		print_all(v2.begin(), it);
	}
	std::cout << "======================\n";
}

//unique ��������������"ɾ��"�������ڵ��ظ�Ԫ��,��������ɾ�������е�Ԫ��(ֻ�Ǻ���)��
//unique_copy: ��ָ�������п������ظ�Ԫ�ص��������ԭ���в���
void test_unique()
{
	{	//unique
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 2, 1 };

		std::sort(v1.begin(), v1.end());	//ע�⣺uniqueֻ��ǰ��Ƚ���ȣ����������Ҫ����
		auto it = std::unique(v1.begin(), v1.end());
		print_all(v1.begin(), v1.end());	//��������
		print_all(v1.begin(), it);			//����������

		it = std::unique(v1.begin(), v1.end(), [](int e1, int e2){ return e1 == e2; }); //Ĭ�ϼ�����ȱȽ�
		print_all(v1.begin(), v1.end());	//��������
		print_all(v1.begin(), it);			//����������
	}
	{	//unique_copy
		vector<int> v1 = { 1, 2, 3, 4, 4, 3, 2, 1, 0 };
		vector<int> v2(v1.size());
		std::sort(v1.begin(), v1.end());	//ע�⣺unique_copyֻ��ǰ��Ƚ���ȣ����������Ҫ����

		auto it = std::unique_copy(v1.begin(), v1.end(), v2.begin());
		print_all(v2.begin(), it); //��ʾ�������ϵ�Ԫ��
	}
	std::cout << "======================\n";
}

//     �����ͨ���㷨 14��
//merge             : �ϲ������������У���ŵ���һ�����С����ذ汾ʹ���Զ���ıȽ�
//inplace_merge     : �ϲ������������У�������и������˷�Χ�����ذ汾ʹ������Ĳ�����������
//nth_element       : ����Χ�ڵ�������������ʹ����С�ڵ�n��Ԫ�ص�Ԫ�ض���������ǰ�棬���������Ķ������ں���
//partial_sort      : ���������������򣬱�����Ԫ�ظ������ÿ��Ա��ŵ���Χ��
//partial_sort_copy : ��partial_sort���ƣ�������������������и��Ƶ���һ������
//partition         : ��ָ����Χ��Ԫ����������ʹ������ĺ������ѽ��Ϊt r ue��Ԫ�ط��ڽ��Ϊfal se��Ԫ��֮ǰ
//stable_partition  : ��partition���ƣ���������֤���������е����˳��
//random_shuffle    : ��ָ����Χ�ڵ�Ԫ����������������ذ汾����һ���������������
//reverse           : ��ָ����Χ��Ԫ�����·�������
//reverse_copy      : ��reverse���ƣ����������д����һ������
//rotate            : ��ָ����Χ��Ԫ���Ƶ�����ĩβ����middleָ���Ԫ�س�Ϊ������һ��Ԫ��
//rotate_copy       : ��rotate���ƣ����������д����һ������
//sort              : ��������������ָ����Χ�ڵ�Ԫ�ء����ذ汾ʹ���Զ���ıȽϲ���
//stable_sort       : ��sort���ƣ������������Ԫ��֮���˳���ϵ(�����ȶ�����) 

//! reverse reverse_copy rotate rotate_copy
void test_reverse_rotate()
{
	{	// reverse reverse_copy
		std::cout << "--------------   reverse reverse_copy   --------------\n";
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		vector<int> v2;

		std::reverse(v1.begin(), v1.end());
		print_all(v1.begin(), v1.end());

		std::reverse_copy(v1.begin(), v1.end(), std::back_inserter(v2));
		print_all(v2.begin(), v2.end());
	}
	{	// rotate rotate_copy
		std::cout << "--------------   rotate rotate_copy   --------------\n";
		vector<int> v1 = { 1, 2, 3, 4, 5, 6 };
		vector<int> v2;

		std::rotate(v1.begin(), v1.begin() + 2, v1.end());
		print_all(v1.begin(), v1.end());

		std::rotate_copy(v1.begin(), v1.begin() + 2, v1.end(), std::back_inserter(v2));
		print_all(v2.begin(), v2.end());
	}
	std::cout << "======================\n";
}

//! ������ֵ�㷨 
//accumulate: iterator�Ա�ʶ�����ж�Ԫ��֮�ͣ��ӵ�һ����valָ���ĳ�ʼֵ�ϡ����ذ汾�������ӷ������Ǵ������Ķ�Ԫ��������Ӧ�õ�Ԫ����
//partial_sum: ����һ�������У�����ÿ��Ԫ��ֵ����ָ����Χ�ڸ�λ��ǰ����Ԫ��֮�͡����ذ汾ʹ���Զ����������ӷ�
//inner_product: �������������ڻ�(��ӦԪ����ˣ������)�����ڻ��ӵ�һ������ĳ�ʼֵ�ϡ����ذ汾ʹ���û�����Ĳ���
//adjacent_difference: ����һ�������У���������ÿ����ֵ����ǰԪ������һ��Ԫ�صĲ���ذ汾��ָ����Ԫ������������Ԫ�صĲ�
void test_numeric_algorithm()
{
	{	// accumulate
		std::cout << "--------------------    accumulate   --------------------\n";
		vector<int> vec = { 1, 2, 3, 4, 5 };
		int total = 0;
		total = std::accumulate(vec.begin(), vec.end(), 0);
		cout << "total = " << total << "\n";

		total = 1;
		total = std::accumulate(vec.begin(), vec.end(), total, [](int x, int total){ return total *= x; });
		cout << "total = " << total << "\n";
	}
	{	// partial_sum
		std::cout << "--------------------    partial_sum   --------------------\n";
		vector<int> vec = { 1, 2, 3, 4, 5 };
		vector<int> vec2(vec.size());
		std::partial_sum(vec.begin(), vec.end(), vec2.begin()); //���ֺͣ�vec2[i] = vec[0]+...+vec[i]
		print_all(vec2.begin(), vec2.end());

		std::partial_sum(vec.begin(), vec.end(), vec2.begin(), std::multiplies<int>()); //���ֳ�
		print_all(vec2.begin(), vec2.end());
	}
	{	// inner_product
		std::cout << "--------------------    inner_product   --------------------\n";
		vector<int> vec1 = { 1, 2, 3, 4 };
		vector<int> vec2 = { 1, 1, 1, 1 };

		int total = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
		cout << "total = " << total << "\n";
		print_all(vec2.begin(), vec2.end());

		total = std::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0, plus<int>(), minus<int>());
		cout << "total = " << total << "\n";
		print_all(vec2.begin(), vec2.end());
	}
	{	// adjacent_difference
		std::cout << "--------------------    adjacent_difference   --------------------\n";
		vector<int> vec1 = { 1, 2, 3, 4 };
		vector<int> vec2 = { 1, 1, 1, 1 };

		std::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin());
		print_all(vec2.begin(), vec2.end());

		std::adjacent_difference(vec1.begin(), vec1.end(), vec2.begin(), multiplies<int>());
		print_all(vec2.begin(), vec2.end());
	}
}


int main()
{
	std::cout << "===================\n";

	test_copy();
	std::cout << "===================\n";

	//test_numeric_algorithm();
	std::cout << "===================\n";

	//test_heap_algorithm();
	std::cout << "===================\n";

	getchar();
	return 0;
}