/*
	Copyright (c) 2018 jones

	https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

	��Դ��Ŀ https://github.com/jones2000/hqchartPy2

	jones_2000@163.com

	���﷨�Զ��庯��,���� (c++)
*/


#include "HQChart.KLineData.h"
#include "HQChart.Log.h"
#include <list>
#include <sstream>


namespace HQChart { namespace Complier {

CustomFunction::CustomFunction()
{
	CUSTOM_FUNCTION_ITEM FUNCTION_LIST[] =
	{
		//����רҵ�������� 
		//FINVALUE(ID),IDΪ���ݱ��
		{L"FINVALUE",1},

		//����ָ��������յ�ĳ���͵Ĳ�������
		//FINONE(ID,Y,MMDD),IDΪ���ݱ��,Y��MMDD��ʾ�������.
		{L"FINONE",3},	

		//���ù�Ʊ����������
		//GPJYVALUE(ID,N,TYPE),IDΪ���ݱ��,N��ʾ�ڼ�������,TYPE:Ϊ1��ʾ��ƽ������,û�����ݵ����ڷ�����һ���ڵ�ֵ; Ϊ0��ʾ����ƽ������
		{L"GPJYVALUE", 3},

		//����ĳ��ĳ�����͵Ĺ�Ʊ����������
		//GPJYONE(ID,N,Y,MMDD),IDΪ���ݱ��,N��ʾ�ڼ�������,Y��MMDD��ʾ�������.
		//���YΪ0,MMDDΪ0,��ʾ��������,MMDDΪ1,2,3...,��ʾ������2,3,4...������
		{L"GPJYONE", 4},

		//�����г��ܵĽ���������
		//SCJYVALUE(ID,N,TYPE),IDΪ���ݱ��,N��ʾ�ڼ�������,TYPE:Ϊ1��ʾ��ƽ������,û�����ݵ����ڷ�����һ���ڵ�ֵ; Ϊ0��ʾ����ƽ������
		{L"SCJYVALUE",3},

		//����ĳ��ĳ�����͵��г��ܵĽ���������.���ָ��֧�������ݺ���,����Ҫ[רҵ��������]����.
		//SCJYONE(ID,N,Y,MMDD),IDΪ���ݱ��,N��ʾ�ڼ�������,Y��MMDD��ʾ�������.
		//���YΪ0,MMDDΪ0,��ʾ��������,MMDDΪ1,2,3...,��ʾ������2,3,4...������
		{L"SCJYONE",4},

		//���ù�Ʊ��ĳ������.
		//GPONEDAT(ID),IDΪ���ݱ��
		{L"GPONEDAT",1},
	};

	for (const auto& item : FUNCTION_LIST)
	{
		m_aryCustomFunc[item._strName] = item;
	}
}

CustomFunction::~CustomFunction()
{

}

CustomFunction& CustomFunction::GetInstance()
{
	static CustomFunction instance;
	return instance;
}

bool CustomFunction::Get(const std::wstring& strName, CUSTOM_FUNCTION_ITEM& item)
{
	auto find = m_aryCustomFunc.find(strName);
	if (find == m_aryCustomFunc.end()) return false;

	item = find->second;

	return true;
}

void CustomFunction::Add(const std::wstring& strName, long lArgCount)
{
	CUSTOM_FUNCTION_ITEM item;
	item._strName = strName;
	item._nArgCount = lArgCount;

	m_aryCustomFunc[strName] = item;
}



//////////////////////////////////////////////////////////////////////////////////////
CustomVariant::CustomVariant()
{

}


CustomVariant::~CustomVariant()
{

}


CustomVariant& CustomVariant::GetInstance()
{
	static CustomVariant instance;
	return instance;
}

void CustomVariant::Add(const std::wstring& strName)
{
	auto find = m_setVariant.find(strName);
	if (find == m_setVariant.end())
		m_setVariant.insert(strName);
}

bool CustomVariant::IsExist(const std::wstring& strName) const
{
	if (m_setVariant.empty()) return false;

	auto find = m_setVariant.find(strName);
	
	if (find == m_setVariant.end()) return false;

	return true;
}

}
}