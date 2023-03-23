/*
Copyright (c) 2018 jones

https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

��Դ��Ŀ https://github.com/jones2000/hqchartPy2

jones_2000@163.com

���ú����� (c++)
*/

#include "HQChart.data.h"
#include "HQChart.Execute.h"


///////////////////////////////////////////////////////////////////////////////
//
// ��������
//
//////////////////////////////////////////////////////////////////////////////

namespace HQChart { namespace Complier {


Variant* VariantOperator::GT(const Variant& left, const Variant& right)
{
	Variant* pResult =  Create();
	if (left.m_nType == Variant::ARRAY_DOUBLE_TYPE && right.m_nType == Variant::ARRAY_DOUBLE_TYPE)
	{
		pResult->m_nType = Variant::ARRAY_DOUBLE_TYPE;
		GT(pResult->m_aryValue, left.m_aryValue, right.m_aryValue);
	}
	else if (left.m_nType == Variant::DOUBLE_TYPE && right.m_nType == Variant::ARRAY_DOUBLE_TYPE)
	{
		pResult->m_nType = Variant::ARRAY_DOUBLE_TYPE;
		if (left.m_aryValue.size() == 1 && left.m_aryValue[0].IsVaild())
		GT(pResult->m_aryValue, left.m_aryValue[0]._dValue, right.m_aryValue);
	}
	else if (left.m_nType == Variant::ARRAY_DOUBLE_TYPE && right.m_nType == Variant::DOUBLE_TYPE)
	{
		if (right.IsVaildDoulbe())
		{
			GT(pResult->m_aryValue, left.m_aryValue, right.GetDoubleValue());
			pResult->m_nType = Variant::ARRAY_DOUBLE_TYPE;
		}
	}
	else if (left.m_nType == Variant::DOUBLE_TYPE && right.m_nType == Variant::DOUBLE_TYPE)
	{
		if (left.IsVaildDoulbe() && right.IsVaildDoulbe())
		{
			double dValue = DoubleGT(left.GetDoubleValue() , right.GetDoubleValue()) ? 1 : 0;
			pResult->SetDoubleValue(dValue);
		}
	}
	return pResult;
}

void VariantOperator::GT(ARRAY_DOUBLE& dest, const ARRAY_DOUBLE& left, const ARRAY_DOUBLE& right)
{
	size_t nLeftCount = left.size(), nRightCount = right.size();
	size_t nCount = std::max(nLeftCount, nRightCount);
	for (size_t i = 0; i < nCount; ++i)
	{
		VARIANT_ITEM item;
		if (i<nLeftCount || i<nRightCount)
		{
			const auto& leftItem = left[i];
			const auto& rightItem = right[i];
			if (leftItem._sType == VARIANT_ITEM::VAILD_ID && rightItem._sType == VARIANT_ITEM::VAILD_ID)
			{
				item.SetValue(DoubleGT(leftItem._dValue , rightItem._dValue) ? 1 : 0);

			}
		}
		dest.push_back(item);
	}
}

void VariantOperator::GT(ARRAY_DOUBLE& dest, double dLeft, const ARRAY_DOUBLE& right)
{
	for (auto rightItem : right)
	{
		VARIANT_ITEM item;
		if (rightItem._sType == VARIANT_ITEM::VAILD_ID)
		{
			item.SetValue(DoubleGT(dLeft , rightItem._dValue) ? 1 : 0);
		}
		dest.push_back(item);
	}
}

void VariantOperator::GT(ARRAY_DOUBLE& dest, const ARRAY_DOUBLE& left, double dRight)
{
	dest.reserve(left.size());
	for (auto leftItem : left)
	{
		VARIANT_ITEM item;
		if (leftItem._sType == VARIANT_ITEM::VAILD_ID)
		{
			item.SetValue(DoubleGT(leftItem._dValue , dRight) ? 1 : 0);
		}
		dest.push_back(item);
	}
}

/*
��������ִ�в�ͬ�����, ����ֹ(�������е����һ����ֵ���ж�).
�÷�:
IFC(X, A, B)��X��Ϊ0��ִ��A, ����ִ��B.IFC��IF���������� : ����X��ֵ��ѡ����ִ��A��B���ʽ.
���� :
	IFC(CLOSE > OPEN, HIGH, TESTSKIP(1)); L; ��ʾ���������򷵻����ֵ, ��ִ����һ��"L;", �����˳���ʽ����
*/
bool VariantOperator::IFC(const Variant& data)
{
	if (data.GetType() == Variant::DOUBLE_TYPE)
	{
		if (!data.IsVaildDoulbe()) return false;

		return data.GetDoubleValue() > 0;
	}
	else if (data.GetType() == Variant::ARRAY_DOUBLE_TYPE)
	{
		if (data.m_aryValue.empty()) return false;
		auto iter= data.m_aryValue.cbegin();
		if (iter->IsVaild()) return iter->_dValue > 0;
		return false;
	}

	return false;
}

/*
TESTSKIP(A):����A��ֱ�ӷ���.
�÷�:
TESTSKIP(A)
��ʾ�����������A��ù�ʽֱ�ӷ���,���ټ���������ı��ʽ ע��:AΪ����������,ֻȡ���һ������
*/
bool VariantOperator::TESTSKIP(const Variant& data)
{
	if (data.GetType() == Variant::DOUBLE_TYPE)
	{
		if (!data.IsVaildDoulbe()) return false;

		return data.GetDoubleValue() > 0;
	}
	else if (data.GetType() == Variant::ARRAY_DOUBLE_TYPE)
	{
		if (data.m_aryValue.empty()) return false;
		auto iter = data.m_aryValue.cbegin();
		if (iter->IsVaild()) return iter->_dValue > 0;
		return false;
	}

	return false;
}


}
}
