// ***********************************************************************
// Filename         : ScopeGuard.h
// Author           : LIZHENG
// Created          : 2014-06-08
// Description      : ��Դ�Զ��ͷ�ʵ���࣬RAII
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-08
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SCOPEGUARD_FILE_H
#define ZL_SCOPEGUARD_FILE_H
#include <functional> 

namespace ZL
{

/// \brief     ScopeGuard : ��Դ�Զ��ͷ�ʵ����
/// \author    LIZHENG
class ScopeGuard
{
public:
	explicit ScopeGuard(std::function<void()> onExitScope)
		: onExitScope_(onExitScope), dismissed_(false)
	{
	}

	~ScopeGuard()
	{
		if (!dismissed_)
		{
			onExitScope_();
		}
	}

	/// ����֧��rollbackģʽ�����ײ�Ҫֱ��ʹ��,����Ϊ��֧�ֻع�ģʽ
	void dismiss()
	{
		dismissed_ = true;
	}

private:
	ScopeGuard(const ScopeGuard&);
	ScopeGuard& operator=(const ScopeGuard&);

private:
	bool dismissed_;	//����֧��rollbackģʽ
	std::function<void()> onExitScope_;
};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

} /* namespace ZL */

#endif /* ZL_SCOPEGUARD_FILE_H */