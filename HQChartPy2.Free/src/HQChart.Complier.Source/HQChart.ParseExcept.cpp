/*
	Copyright (c) 2018 jones

	https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

	��Դ��Ŀ https://github.com/jones2000/hqchartPy2

	jones_2000@163.com

	�﷨�����쳣�� (c++)
*/


#include "HQChart.Complier.h"
#include "HQChart.data.h"
#include <string>
#include <assert.h>


namespace HQChart { namespace Complier {

ParseExcept::ParseExcept(const std::wstring& strMessage)
	:m_strMessage(strMessage)
{

}

ParseExcept::~ParseExcept()
{

}

}
}