// ***********************************************************************
// Filename         : CheckClassMethod.hpp
// Author           : LIZHENG
// Created          : 2014-08-04
// Description      : ģ�弼��(SFINAE)ʵ�ֵļ�����Ա��������
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-08-04
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_CHECKCLASSMETHOD_HPP
#define ZL_CHECKCLASSMETHOD_HPP

/********
SFINAE : Substitution failure is not an error, ƥ��ʧ�ܲ�����һ������. SFINAE ��һ��ר�����ñ�����ƥ��ʧ�ܵ�trick.
********/

// ���ڼ������ClassType�Ƿ��г�Ա����const char* ToString()const;
template<typename ClassType>
struct HasToStringFunction
{
	typedef struct { char a[2]; } Yes;
	typedef struct { char a[1]; } No;

	template<typename FooType, const char* (FooType::*)()const>
	struct FuncMatcher;

	template<typename FooType>
	static Yes Tester(FuncMatcher<FooType, &FooType::ToString>*);

	template<typename FooType>
	static No Tester(...);

	enum
	{
		Value = sizeof(Tester<ClassType>(NULL)) == sizeof(Yes)
	};
};


#endif  /* ZL_CHECKCLASSMETHOD_HPP */