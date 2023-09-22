/*
Copyright (c) 2018 jones

https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

��Դ��Ŀ https://github.com/jones2000/hqchartPy2

jones_2000@163.com

���ݻ��� (c++)
*/

#pragma once
#include <map>
#include <memory>
#include <Python.h>
#include "HQChart.KLineData.h"

using namespace HQChart::Complier;

namespace HQChart { namespace PyCache {

class KLineCacheItem
{
public:

	typedef HistoryDataCache::ARRAY_KDATA ARRAY_KDATA;
	typedef std::shared_ptr< KLineCacheItem> REF_PTR;

	KLineCacheItem();
	~KLineCacheItem();

	long GetPeriod() const { return m_lPeriod; }
	long GetRight() const { return m_lRight; }
	const std::wstring& GetSymbol() const { return m_strSymbol; }
	const std::wstring& GetName() const { return m_strName; }
	const ARRAY_KDATA& GetData() const { return m_aryData; }

	void SetPeriod(long lValue) { m_lPeriod= lValue; }
	void SetRight(long lValue) { m_lRight = lValue; }
	void SetSymbol(const std::wstring& strSymbol) { m_strSymbol = strSymbol; }
	void SetName(const std::wstring& strName) { m_strName = strName; }
	bool SetPyData(PyObject* pData);
	bool UpdatePyData(PyObject* pData);
	

private:
	void UpdateData(const HISTORY_ITEM& item);

	ARRAY_KDATA m_aryData;
	std::wstring m_strSymbol;
	std::wstring m_strName;
	long m_lPeriod = 0;	//����
	long m_lRight = 0;	//��Ȩ
	time_t m_tmUpdate = 0;	//������ʱ��
};

class KLineCache
{
public:
	typedef std::map<std::wstring, KLineCacheItem::REF_PTR> MAP_DATA;

	KLineCache();
	~KLineCache();

	static KLineCache& GetInstance();

	KLineCacheItem::REF_PTR GetData(const std::wstring& strSymbol, long lPeriod, long lRight) const;

	bool AddData(PyObject* pData);
	bool UpdateData(PyObject* pData);	//���ݸ���

private:
	MAP_DATA m_mapData;
};


} }

