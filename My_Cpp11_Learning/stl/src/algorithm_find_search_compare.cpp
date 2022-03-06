// ***********************************************************************
// Filename         : algorithm_find_compare.cpp
// Author           : LIZHENG
// Created          : 2014-06-14
// Description      : ������STL�еķǱ����㷨(���ҡ��Ƚϡ������Сֵ��)
//
// Last Modified By : LIZHENG
// Last Modified On : 2013-07-22
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//! STL�ķǱ����㷨��Non-mutating algorithms����һ�鲻�ƻ��������ݵ�ģ�庯�����������������ݽ����������Ԫ�ز��ҡ�������������ͳ�ƺ�ƥ�䡣
//! find find_if find_if_not adjacent_find find_end find_first_of
//! search search_n binary_search lower_bound upper_bound equal_range
//! max min max_element min_element mismatch lexicographical_compare
//! includes equal count count_if all_of any_of none_of
template<typename T>
void print_all(T start, T end)
{
	std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
	cout << "\n";
}

//find          : ���ҵ���ĳֵ��Ԫ��
//find_if       : ��find��һ��ν���жϰ汾�������÷��ز���ֵ��ν���ж�pred��������������[first, last)�ϵ�ÿһ��Ԫ��
//find_if_not   : ���ص�һ��ֵ���������������Ԫ��
//adjacent_find : ���ڲ�����Ȼ������������ڽ�Ԫ�ضԡ�
//find_end      : ��һ�����������������һ������һ����ƥ���������.
//                �ڵ���������[first1, last1)�������������������[first2, last2)Ԫ��ƥ��������У�������Ԫ�صĵ�������last1
//find_first_of : ���ڲ���λ��ĳ����Χ֮�ڵ�Ԫ�ء��ڵ���������[first1, last1)�ϲ���Ԫ��*i��ʹ�õ���������[first2, last2)
//                ��ĳ��Ԫ��*j������*i ==*j�������Ԫν�ʺ���comp(*i, *j)==true��������Ԫ���ҵ��򷵻ص�����i�����򷵻�last1
void test_find()
{
	{	//find find_if find_if_not
		std::cout << "--------------------    find find_if find_if_not --------------------\n";
		vector<int> vvv = { 16, 2, 30, 3, 45, 75, 69, 70 };
		print_all(vvv.begin(), vvv.end());

		int val = 3;
		auto iter = std::find(vvv.begin(), vvv.end(), val);
		if (iter != vvv.end())
			cout << "find it, " << "elem " << val << " at location " << iter - vvv.begin() << "\n";
		else
			cout << "find fail, no elem " << val << "\n";

		//���ҵ�һ���ܹ�����val��Ԫ��λ��
		auto iter2 = std::find_if(vvv.begin(), vvv.end(), [&val](int x){ return x % val == 0; });
		if (iter2 != vvv.end())
			cout << "find it, at location " << iter2 - vvv.begin() << ", and value = " << *iter2 << "\n";
		else
			cout << "find fail\n";

		auto iter3 = std::find_if_not(vvv.begin(), vvv.end(), [&val](int x){ return x < 50; });
		if (iter2 != vvv.end())
			cout << "find it, at location " << iter2 - vvv.begin() << ", and value = "<< *iter3 << "\n";
		else
			cout << "find fail\n";
	}
	{	//adjacent_find
		std::cout << "--------------------    adjacent_find  --------------------\n";
		int IntArray[] = { 1, 2, 3, 4, 10, 8, 8, 6, 7, 9 };
		const int ARRAY_SIZE = sizeof(IntArray) / sizeof(IntArray[0]);
		print_all(IntArray, IntArray + ARRAY_SIZE);

		// ���ҵ�һ����������ȵ�Ԫ�� 
		int *pos1 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE);
		if (pos1 != IntArray + ARRAY_SIZE)  // elements found		
			cout << "Found adjacent pair of matching elements: (" << *pos1 << ", "
			<< *(pos1 + 1) << "), " << "at location " << pos1 - IntArray << endl;
		else
			cout << "No adjacent pair of matching elements were found" << endl;

		// ��ν����ʽ�Ĳ�����������odd_even���ڽ�Ԫ�ض�λ��
		//x bool odd_even(int x, int y)
		//x {
		//x 	return (x - y) % 2 == 0 ? 1 : 0;
		//x }
		//x int *pos2 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE, odd_even);
		int *pos2 = std::adjacent_find(IntArray, IntArray + ARRAY_SIZE, [](int x, int y){ return (x - y) % 2 == 0 ? 1 : 0; });
		if (pos2 != IntArray + ARRAY_SIZE)  // elements found		
		{
			cout << "Found adjacent pair of matching elements: (" << *pos2 << ", "
				<< *(pos2 + 1) << "), " << "at location " << pos2 - IntArray << endl;
		}
		else
			cout << "No adjacent pair of matching elements were found" << endl;
	}
	{	//find_end
		std::cout << "--------------------    find_end   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
		//sort(v.begin(), v.end()); 
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		vector<int>::iterator iter;

		vector<int> arr = { 1, 2, 2 };
		iter = std::find_end(v.begin(), v.end(), arr.begin(), arr.end());
		if (iter != v.end())
			cout << "find at position " << (iter - v.begin()) << endl;
		else
			cout << "find fail\n";

		vector<int> arr1 = { 1, 2, 2, 9 };
		iter = std::find_end(v.begin(), v.end(), arr1.begin(), arr1.end());
		if (iter != v.end())
			cout << "find at position " << (iter - v.begin()) << endl;
		else
			cout << "find fail\n";

		vector<int> arr2 = { 3, 8, 4 };
		//����һ��ԭ������ĳһ���������У�ʹ��ֵ��1��ǡ��Ϊ������arr2
		iter = std::find_end(v.begin(), v.end(), arr2.begin(), arr2.end(), [](int x, int y){ return x + 1 == y;	});
		if (iter != v.end())
			cout << "find at position " << std::distance(v.begin(), iter) << endl;
		else
			cout << "find fail\n";
	}
	{	//find_first_of
		std::cout << "--------------------    find_first_of   --------------------\n";
		const char* hello = "Hello, World!";
		const char* email = "lizhenghn@gmail.com";
		const char* pos = std::find_first_of(hello, hello + strlen(hello), email, email + strlen(email));
		if (pos!=NULL)
			cout << "�ַ���hello�е�һ���������ַ���email���ַ�Ϊ��" << *pos << endl;
	}
}

//searc         : ����������Χ����һ������������һ�����еĵ�һ�γ��ֵ�λ�á�
//search_n      : �����������Ƿ���һϵ��Ԫ��ֵ��Ϊĳ������ֵ(��������ν���ж��������������С�
//                ��������������Ҫ����������ֻ�ǰ�˳��ʼ��������
//binary_search : ���ֲ��ң�Ҫ��������б�������. �����Ƿ���[first, last)�д���iterator i, 
//                ���� !(*i<value) && !(value<*i) or comp(*i, value) == false && comp(value, *i) == false
void test_search()
{
	std::cout << "--------------------    search   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6, 4 };
	//x sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������
	print_all(v.begin(), v.end());

	{   //search
		auto func = [](std::vector<int> &vec){ copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, ",")); return ""; };

		vector<int> v1 = { 2, 7, 3 };
		vector<int>::iterator iter1 = std::search(v.begin(), v.end(), v1.begin(), v1.end());
		if (iter1 != v.end())
			cout << "v have sub sequences is v1(", func(v1), cout << ")\n";
		else
			cout << "v have not sub sequences is v1(", func(v1), cout << ")\n";

		vector<int> v2 = { 2, 7, 3, 5 };
		vector<int>::iterator iter2 = std::search(v.begin(), v.end(), v2.begin(), v2.end());
		if (iter2 != v.end())
			cout << "v have sub sequences is v2\n";
		else
			cout << "v have not sub sequences is v2\n";
	}
	{   //search_n
		int count = 3, val = 4;
		if (std::search_n(v.begin(), v.end(), count, val) != v.end())
			cout << "find " << count << " continuous sequencs is " << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs is " << val << "\n";

		count = 2, val = 7;
		if (std::search_n(v.begin(), v.end(), count, val) != v.end())
			cout << "find " << count << " continuous sequencs is" << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs is" << val << "\n";

		count = 3, val = 8;
		if (std::search_n(v.begin(), v.end(), count, val, [](int elem, int val){ return elem * 2 == val; }) != v.end())
			cout << "find " << count << " continuous sequencs which its double is " << val << "\n";
		else
			cout << "find " << count << " continuous sequencs which its double is " << val << "\n";

		count = 4, val = 8;
		if (std::search_n(v.begin(), v.end(), count, val, [](int elem, int val){ return elem * 2 == val; }) != v.end())
			cout << "find " << count << " continuous sequencs which its plus one is " << val << "\n";
		else
			cout << "find not " << count << " continuous sequencs which its plus one is " << val << "\n";
	}
	{	// binary_search
		std::cout << "--------------------    binary_search   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };
		sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������		
		print_all(v.begin(), v.end());
		
		int val = 3;
		if (std::binary_search(v.begin(), v.end(), val))
			cout << "find elem " << val << " success\n";
		else
			cout << "find elem " << val << " fail\n";

		//val = 9;
		//���� ������������ܹ���2������Ԫ��
		if (std::binary_search(v.begin(), v.end(), val, [](int elem, int val)->bool{ return abs(val - elem) % 2 == 0; }))
			cout << "find success\n";
		else
			cout << "find fail\n";
		std::cout << "\n";
	}
}

//lower_bound : ����ָ��Χ�е�һ��ֵ���ڻ���ڸ���ֵ��Ԫ�صĵ�����
//upper_bound : ����ָ��Χ�е�һ��ֵ���ڸ���ֵ��Ԫ�صĵ�����
//�ٶ���ֵͬ��Ԫ�ؿ����ж��,lower_bound ���ص�һ������������Ԫ��λ��;upper_bound �������һ������������Ԫ��λ��
void test_lower_upper_bound()
{
	{	//lower_bound
		std::cout << "--------------------    lower_bound   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
		sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������
		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		/*  lower_bound */
		int val = 3;
		cout << "lower_bound function, split value = " << val << endl;
		vector<int>::iterator iter = std::lower_bound(v.begin(), v.end(), val);
		cout << "less than " << val << " : ";
		copy(v.begin(), iter, ostream_iterator<int>(cout, " "));		cout << endl;
		cout << "equal or greater than " << val << " : ";
		copy(iter, v.end(), ostream_iterator<int>(cout, " "));			cout << endl;
		std::cout << "\n";
	}
	{	//upper_bound
		std::cout << "--------------------    upper_bound   --------------------\n";
		vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 5, 6, 6 };

		sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������

		copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

		int val = 3;
		cout << "upper_bound function, split value = " << val << endl;
		vector<int>::iterator iter = std::upper_bound(v.begin(), v.end(), val);
		cout << "equal or less than " << val << " : ";
		copy(v.begin(), iter, ostream_iterator<int>(cout, " "));		cout << endl;
		cout << "greater than " << val << " : ";
		copy(iter, v.end(), ostream_iterator<int>(cout, " "));			cout << endl;
		std::cout << "\n";
	}
}

//equal_range : ˳����ҵ��ڸ���ֵ��Ԫ����ɵ��ӷ�Χ��Ҫ��������б�������
//              ��������subrange[i,j)��ʹ������һ��iterator in [i,j)����!(*k<value) && !(value<*k) or comp(*k,value)==false && comp(value,*k)==false.
//              �ٶ���ֵͬ��Ԫ�ؿ����ж��,equal_range �������е���ָ��ֵ��ͷ/βԪ�ص�λ�ã���ʵ����lower_bound��upper_bound
void test_equal_range()
{
	std::cout << "--------------------    equal_range   --------------------\n";

	vector<int> v = { 0, 1, 2, 2, 7, 3, 3, 4, 4, 4, 0, 6, 6 };
	sort(v.begin(), v.end());   //ע�⣬����Ҫ��֤�������
	copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 	cout << endl;

	int val = 3;
	cout << "euqual_range function, split value = " << val << endl;
	pair<vector<int>::iterator, vector<int>::iterator> vecpair = std::equal_range(v.begin(), v.end(), val);
	cout << "get euqal value " << val << "= ";
	copy(vecpair.first, vecpair.second, ostream_iterator<int>(cout, " "));	cout << endl;

	val = 9;
	cout << "euqual_range function, split value = " << val << endl;
	vecpair = std::equal_range(v.begin(), v.end(), val);
	cout << "get euqal value " << val << "= ";
	copy(vecpair.first, vecpair.second, ostream_iterator<int>(cout, " "));	cout << endl;
	std::cout << "\n";
}

//equal       : ������������ڱ�־��Χ��Ԫ�ض���ȣ�����true
//includes    : �жϵ�һ��ָ����Χ�ڵ�����Ԫ���Ƿ񶼱��ڶ�����Χ������ʹ�õײ�Ԫ�ص�<���������ɹ�����true
//max         : ��������Ԫ���нϴ�һ��
//min         : ��������Ԫ���н�Сһ��
//max_element : ����һ��ForwardIterator��ָ������������Ԫ��
//min_element : ����һ��ForwardIterator��ָ����������С��Ԫ��
//minmax      : ��������Ԫ����ֵ�����С��Ԫ��
//minmax_element : ���ظ�����Χ��ֵ�����С��Ԫ��
//mismatch    : �Ƚ��������У�����һ��iterator����־��һ����ƥ��Ԫ��λ�á������ƥ�䣬����ÿ��������last
//lexicographical_compare : ���ֵ���Ƚ���������
void test_relation()
{
	vector<int> v1 = { 1, 2, 3, 4, 4, 5, 6, 6, 6, 9 };  //���ϲ���ʱ����Ҫ����������
	vector<int> v2 = { 8, 2, 3, 4, 5, 5, 6, 6 };  //���ϲ���ʱ����Ҫ����������
	vector<int> v = { 2, 3, 5, 6, 9 };
	if (std::includes(v1.begin(), v1.end(), v.begin(), v.end()))
		cout << "v is subse of v1\n";
	if (std::lexicographical_compare(v1.begin(), v1.end(), v.begin(), v.end()))
		cout << "v is subse of v1\n";

	int arr[] = { 2, 3, 5, 6, 9 };
	if (std::equal(v.begin(), v.end(), arr))
		cout << "arr == v\n";

	auto it1 = std::max(v1, v2); //Ĭ������Ԫ�رȽϣ�ֱ���ҵ���С�����
	print_all(it1.begin(), it1.end());
	auto it2 = std::min(v1, v2); //Ĭ������Ԫ�رȽϣ�ֱ���ҵ���С�����
	print_all(it2.begin(), it2.end());

	auto it3 = std::max_element(v1.begin(), v1.end());
	cout << *it3 << "\n";
	auto it4 = std::min_element(v1.begin(), v1.end());
	cout << *it4 << "\n";

	auto it5 = std::minmax({ 3, 5, 8, 0, 1 });
	cout << it5.first << "\t" << it5.second << "\n";
	auto it6 = std::minmax_element(v1.begin() + 1, v1.end());
	cout << *it6.first << "\t" << *it6.second << "\n";

	vector<int> v3 = { 1, 2, 3, 4 };
	vector<int> v4 = { 1, 2, 3, 4, 5 };
	pair<vector<int>::iterator, vector<int>::iterator> pp1 = std::mismatch(v3.begin(), v3.end(), v4.begin());
	if (pp1.first == v3.end() && pp1.second != v4.end())
		cout << "v3 match v4";
	else
		cout << "different elem : " << *pp1.first << "\t" << *pp1.second << "\n";
}

//count       : ���ڼ��������е�ĳ������ֵ�ĳ��ִ���
//count_if    : ����ֵ�������������Ԫ�صĸ���
//all_of      : ����ڸ�����Χ���Ƿ�����Ԫ�ض��������������
//any_of      : ����ڸ�����Χ���Ƿ����Ԫ���������������
//none_of     : ����ڸ�����Χ���Ƿ񲻴���Ԫ���������������
void test_count()
{
	{	// count count_if
		vector<int> vvv = { 16, 70, 30, 3, 45, 75, 69, 70 };
		print_all(vvv.begin(), vvv.end());

		int val = 70;
		int cou = std::count(vvv.begin(), vvv.end(), 70);
		cout << "total have " << cou << " elems(" << val << ")\n";

		int cou2 = std::count_if(vvv.begin(), vvv.end(), [&val](int x){ return x >= 70; });
		cout << "total have " << cou2 << " elems which is equal or greater than(" << val << ")\n";
	}
	{	// all_of any_of none_of
		vector<int> vvv = { 16, 70, 30, 3, 45, 75, 69, 70 };
		if (std::all_of(vvv.begin(), vvv.end(), [](int e){ return e > 0; }))
			cout << "all of elems greater than 0\n";
		else 
			cout << "not all of elems greater than 0\n";

		if (std::any_of(vvv.begin(), vvv.end(), [](int e){ return e < 10; }))
			cout << "some of elems less than 10\n";
		else
			cout << "all of elems greater than 10\n";

		if (std::none_of(vvv.begin(), vvv.end(), [](int e){ return e > 90; }))
			cout << "none of elems greater than 90\n";
		else
			cout << "some of elems greater than 90\n";
	}
}

int main()
{
	test_find();
	std::cout << "===================\n";

	test_search();
	std::cout << "===================\n";

	test_lower_upper_bound();
	std::cout << "===================\n";

	test_equal_range();
	std::cout << "===================\n";

	test_relation();
	std::cout << "===================\n";

	test_count();
	std::cout << "===================\n";

	getchar();
	return 0;
}