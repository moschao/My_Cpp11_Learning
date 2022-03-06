// ***********************************************************************
// Filename         : range.hpp
// Author           : LIZHENG
// Created          : 2014-06-16
// Description      : C++11ʵ�ֵ�range
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-16
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_RENGE_FILE_H
#define ZL_RENGE_FILE_H
/***
c++11��range-based forѭ������֧���Զ������͵ı���������Ҫ���Զ���������������������
	1. ʵ��begin()��end()�����Ƿֱ��������ص�һ�������һ��Ԫ�صĵ�������
	2. �ṩ������ֹ�ķ�����
	3.�ṩ����range�ķ�����
C++11 ʵ�ֵ�range �� �ο��ԣ�http://www.cnblogs.com/qicosmos/p/3540435.html
������python��range���������ֲ�����֧����������֧�ָ�������ͬʱ����˫�������
***/

template<typename value_t>
class RangeImpl
{
	class Iterator;
public:
	RangeImpl(value_t begin, value_t end, value_t step = 1) :m_begin(begin), m_end(end), m_step(step)
	{
		if (step>0 && m_begin >= m_end)
			throw std::logic_error("end must greater than begin.");
		else if (step<0 && m_begin <= m_end)
			throw std::logic_error("end must less than begin.");

		m_step_count = (m_end - m_begin) / m_step;  //����Ҫ�������ٸ�Ԫ��
		if (m_begin + m_step_count * m_step != m_end)
		{
			m_step_count++;  //����ȡ��
		}
	}

	Iterator begin()
	{
		return Iterator(0, *this);
	}

	Iterator end()
	{
		return Iterator(m_step_count, *this);
	}

	value_t operator[](int s)
	{
		return m_begin + s * m_step;
	}

	int size()
	{
		return m_step_count;
	}

private:
	value_t m_begin;   //��ʼλ��
	value_t m_end;     //����λ��
	value_t m_step;    //����
	int m_step_count;  //ǰ������

	class Iterator
	{
	public:
		Iterator(int start, RangeImpl& range) : m_current_step(start), m_range(range)
		{
			m_current_value = m_range.m_begin + m_current_step*m_range.m_step;
		}

		value_t operator*() { return m_current_value; }

		const Iterator* operator++()
		{
			m_current_value += m_range.m_step;
			m_current_step++;
			return this;
		}

		bool operator==(const Iterator& other)
		{
			return m_current_step == other.m_current_step;
		}

		bool operator!=(const Iterator& other)
		{
			return m_current_step != other.m_current_step;
		}

		const Iterator* operator--()
		{
			m_current_value -= m_range.m_step;
			m_current_step--;
			return this;
		}

	private:
		value_t m_current_value;
		int m_current_step;
		RangeImpl& m_range;
	};
};

template<typename T>
RangeImpl<T> Range(T end)
{
	return RangeImpl<T>(T(), end, 1);
}

template<typename T>
RangeImpl<T> Range(T begin, T end)
{
	return RangeImpl<T>(begin, end, 1);
}

template<typename T, typename V>
auto Range(T begin, T end, V stepsize)->RangeImpl<decltype(begin + end + stepsize)>
{
	return RangeImpl<decltype(begin + end + stepsize)>(begin, end, stepsize);
}

#endif /* ZL_RENGE_FILE_H */