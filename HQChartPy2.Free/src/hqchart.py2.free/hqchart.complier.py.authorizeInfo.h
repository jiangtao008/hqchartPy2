/*
Copyright (c) 2018 jones

https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

��Դ��Ŀ https://github.com/jones2000/hqchartPy2

jones_2000@163.com
*/

#pragma once
#include <vector>
#include <string>


namespace HQChart {namespace Complier { namespace Py {

//�û���Ȩ��Ϣ
class AuthorizeInfo
{
public:
	AuthorizeInfo();
	~AuthorizeInfo();

	static AuthorizeInfo& GetInstance();

	void Load(const std::string& strFile);
	const std::wstring& GetInfo() const;
	const std::wstring& GetError() const;

	std::wstring ToString() const;

	bool IsVaild() const;

protected:
	bool					m_bVaild = true;
	int						m_nExpired = 0;
	std::wstring			m_strInfo = L"HQChartPy2�����汾";
	mutable std::wstring	m_strError;
};



}
}
}
