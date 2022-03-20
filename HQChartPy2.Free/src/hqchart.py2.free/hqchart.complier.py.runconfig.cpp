/*
Copyright (c) 2018 jones

https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

��Դ��Ŀ https://github.com/jones2000/hqchartPy2

jones_2000@163.com

pyָ�����ӿ� (c++)
*/

#include "hqchart.complier.py.runconfig.h"

//json ��ȡ
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "filereadstream.h"
using namespace rapidjson;

#include "HQChart.Log.h"
#include "HQChart.OutVarToJson.h"
#include "hqchart.complier.py.callbackdata.h"
#include "hqchart.complier.py.authorizeInfo.h"
#include "hqchart.complier.py.callbackfunction.h"

namespace HQChart { namespace Complier { namespace Py {

RunConfig::RunConfig()
{

}


RunConfig::~RunConfig()
{

}

bool RunConfig::LoadConfig(PyObject* pConfig, PyObject* pCallback, std::wstring& strError)
{
	if (!LoadJsonConfig(pConfig, strError))
		return false;


	if (!LoadCallbackConfg(pCallback, strError))
		return false;

	return true;
}

bool RunConfig::LoadJsonConfig(PyObject* pConfig, std::wstring& strError)
{
	if (!pConfig || !PyUnicode_Check(pConfig))
	{
		strError = L"runconfig is null.";
		return false;
	}

	const char* pStrConfig = PyUnicode_AsUTF8AndSize(pConfig, NULL);

	std::wstring strValue;
	const ScriptIndex::ARRAY_ARGUMENT* pDefaultArgs = NULL;
	rapidjson::Document root;
	root.Parse(pStrConfig);
	if (root.IsNull()) return false;

	if (JSON_CHECK_STRING(root, "Name"))	//ϵͳָ��
	{
		strValue = UTF8ToWString(root["Name"].GetString());
		const ScriptIndex* pIndex = ScriptLibrary::GetInstance().Get(strValue);
		if (!pIndex)
		{
			TRACE_WARNING(L"[ReadRunConfig] 'Name=%ls' can't find in system index.", strValue.c_str());
			strError = L"Can't find system index. Name=";
			strError += strValue;
			return false;
		}

		m_strCode = pIndex->GetCode();
		pDefaultArgs = &pIndex->GetArgument();
	}
	else if (JSON_CHECK_STRING(root, "Script"))	//�ű�
	{
		m_strCode = UTF8ToWString(root["Script"].GetString());
	}
	else
	{
		TRACE_WARNING(L"[ReadRunConfig] config 'Script' error.");
		strError = L"Script or Name field is null.";
		return false;
	}
	

	//����
	if (root.HasMember("Args") && root["Args"].IsArray())
	{
		const Value& jsArgs = root["Args"];

		long lCount = (long)jsArgs.Size();

		double dValue = 0;
		for (long i = 0; i < lCount; ++i)
		{
			const auto& item = jsArgs[i];
			if (!JSON_CHECK_STRING(item, "Name") || !JSON_CHECK_DOUBLE(item, "Value")) continue;

			strValue = UTF8ToWString(item["Name"].GetString());
			dValue = item["Value"].GetDouble();

			HQChart::Complier::ARGUMENT_ITEM argItem;
			argItem._dValue = dValue;
			argItem._strName = strValue;

			m_aryArgs.push_back(argItem);
		}
	}
	else if (pDefaultArgs)	//û�в��� ��ʹ��Ĭ�ϲ���
	{
		m_aryArgs = *pDefaultArgs;
	}

	//����
	if (JSON_CHECK_INT(root, "Period")) m_lPeriod = root["Period"].GetInt();

	//��Ȩ
	if (JSON_CHECK_INT(root, "Right")) m_lRight = root["Right"].GetInt();

	//����
	if (!root.HasMember("Symbol"))
	{
		TRACE_WARNING(L"[ReadRunConfig] config 'Symbol' error.");
		strError = L"Symbol field error.";
		return false;
	}

	const Value& jsSymbol = root["Symbol"];
	if (jsSymbol.IsString())
	{
		std::wstring strSymbol;
		strSymbol = UTF8ToWString(root["Symbol"].GetString());
		m_arySymbol.push_back(strSymbol);
	}
	else if (jsSymbol.IsArray())
	{
		long lCount = (long)jsSymbol.Size();
		std::wstring strSymbol;
		for (long i = 0; i < lCount; ++i)
		{
			const auto& item = jsSymbol[i];
			if (!item.IsString()) continue;
			strSymbol = UTF8ToWString(item.GetString());
			m_arySymbol.push_back(strSymbol);
		}

	}

	if (m_arySymbol.empty())
	{
		TRACE_WARNING(L" Symbol field error. ");
		return false;
	}

	if (JSON_CHECK_INT(root, "OutCount"))
		m_lOutCount = root["OutCount"].GetInt();

	if (JSON_CHECK_STRING(root, "JobID"))
		m_strGuid = root["JobID"].GetString();

	return true;
}

bool RunConfig::LoadCallbackConfg(PyObject* pCallbackFunc, std::wstring& strError)
{
	//�ص�
	if (!pCallbackFunc || !PyDict_Check(pCallbackFunc))
	{
		strError = L"callback function config is null.";
		return false;
	}

	m_pGetKData = PyDict_GetItemString(pCallbackFunc, "GetKLineData");
	if (!m_pGetKData || !PyCallable_Check(m_pGetKData))
	{
		strError = L"callback function GetKLineData error.";
		return false;
	}

	m_pGetKData2 = PyDict_GetItemString(pCallbackFunc, "GetKLineData2");
	if (!m_pGetKData2 || !PyCallable_Check(m_pGetKData2))
	{
		strError = L"callback function GetKLineData2 error.";
		return false;
	}

	m_pGetDataByName = PyDict_GetItemString(pCallbackFunc, "GetDataByName");
	if (!m_pGetDataByName || !PyCallable_Check(m_pGetDataByName))
	{
		strError = L"callback function GetDataByName error.";
		return false;
	}

	m_pGetDataByNumber = PyDict_GetItemString(pCallbackFunc, "GetDataByNumber");
	if (!m_pGetDataByNumber || !PyCallable_Check(m_pGetDataByNumber))
	{
		strError = L"callback function GetDataByNumber error.";
		return false;
	}

	m_pGetDataByNumbers = PyDict_GetItemString(pCallbackFunc, "GetDataByNumbers");
	if (!m_pGetDataByNumbers || !PyCallable_Check(m_pGetDataByNumbers))
	{
		strError = L"callback function m_pGetDataByNumbers error.";
		return false;
	}

	m_pGetDataByString = PyDict_GetItemString(pCallbackFunc, "GetDataByString");
	if (!m_pGetDataByString || !PyCallable_Check(m_pGetDataByString))
	{
		strError = L"callback function GetDataByString error.";
		return false;
	}

	m_pGetIndexScript= PyDict_GetItemString(pCallbackFunc, "GetIndexScript");
	if (!m_pGetIndexScript || !PyCallable_Check(m_pGetIndexScript))
	{
		strError = L"callback function GetIndexScript error.";
		return false;
	}

	//��ѡ�ص�
	m_pSuccess = PyDict_GetItemString(pCallbackFunc, "Success");
	if (!m_pSuccess || !PyCallable_Check(m_pSuccess)) m_pSuccess = NULL;

	m_pFailed = PyDict_GetItemString(pCallbackFunc, "Failed");
	if (!m_pFailed || !PyCallable_Check(m_pFailed)) m_pFailed = NULL;

	return true;
}

bool RunConfig::VerifyAuthorizeInfo()
{
	const auto& authorize = AuthorizeInfo::GetInstance();
	if (authorize.IsVaild()) return true;

	if (m_pFailed)
	{
		PyCallbackFunction pyFunction(m_pFailed);
		PyObject* arglist = Py_BuildValue("uuus", L"", L"", authorize.ToString().c_str(), m_strGuid.c_str());
		pyFunction.Call(arglist);
	}

	return false;
}


bool RunConfig::RunScript()
{
	if (!VerifyAuthorizeInfo()) return false;

	try
	{
		Pool pool;
		Program* pProgram = HQChart::Complier::Parse(pool, m_strCode);	//�ű�����
		TRACE_DEBUG(L"[RunConfig::RunScript] start (count=%d)......", m_arySymbol.size());

		HistoryDataCallback* pHistoryDataCallback = new HistoryDataCallback(L"", m_lPeriod, m_lRight);
		std::shared_ptr<HistoryDataCallback> ptrHistoryDataCallback = std::shared_ptr<HistoryDataCallback>(pHistoryDataCallback);
		pHistoryDataCallback->SetRunConfig(this);
		HQChart::Complier::IHistoryData* pHistoryData = pHistoryDataCallback;

		HQChart::Complier::Execute exec;
		exec.SetProgram(pProgram);
		if (!m_aryArgs.empty()) exec.SetArguments(m_aryArgs);

		long lFinished = 0;
		std::string strJson;
		for (const auto& strSymbol : m_arySymbol)
		{
			try
			{
				pHistoryDataCallback->Reset();
				pHistoryDataCallback->SetSymbol(strSymbol, m_lPeriod, m_lRight);

				//����������Ϣ
				pHistoryDataCallback->SetRunConfig(this);
				pHistoryDataCallback->LoadKData();	//����K������

				//ִ��
				//writelog("Run scrpit");
				exec.SetHistoryData(pHistoryDataCallback);
				exec.Run();	//ִ�нű�

				if (m_pSuccess)
				{
					OutVarToJsonHelper::ToJson(exec.GetOutVarInfo(), pHistoryDataCallback, strJson, m_lOutCount, m_lOutStartIndex, m_lOutEndIndex, &m_aryArgs);
					PyCallbackFunction pyFunction(m_pSuccess);
					PyObject* arglist = Py_BuildValue("uss", strSymbol.c_str(), strJson.c_str(), m_strGuid.c_str());
					pyFunction.Call(arglist);
				}

				++lFinished;
				TRACE_DEBUG(L"[RunConfig::RunScript] progress %d/%d", lFinished, m_arySymbol.size());
			}
			catch (const ExecuteExcept& e)	//ִ��ʧ��
			{
				std::wstring strError;
				std::wstringstream strStream;
				strStream << L"ִ��ʧ��:" << e.GetDescription().c_str();
				strError = strStream.str();
				if (m_pFailed)
				{
					PyCallbackFunction pyFunction(m_pFailed);
					PyObject* arglist = Py_BuildValue("uuus", m_strCode.c_str(), strSymbol.c_str(), strError.c_str(), m_strGuid.c_str());
					pyFunction.Call(arglist);
				}

				return false;
			}
		}
		
		return true;
	}
	catch (const ParseExcept& e)	//����ʧ��
	{
		std::wstring strError;
		std::wstringstream strStream;
		strStream << L"����ʧ��:" << e.GetDescription().c_str();
		strError = strStream.str();
		if (m_pFailed)
		{
			PyCallbackFunction pyFunction(m_pFailed);
			PyObject* arglist = Py_BuildValue("uuus", m_strCode.c_str(), L"", strError.c_str(), m_strGuid.c_str());
			pyFunction.Call(arglist);
		}
		return false;
	}
}

}
}
}