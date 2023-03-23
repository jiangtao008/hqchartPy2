
#include "hqchart.csharp.h"
#include <thread>
#include <string>

#include "HQChart.CallbackData.h"
#include "HQChart.RunConfig.h"
#include "HQChart.Log.h"
#include "HQChart.Execute.h"


const int MAIN_VERSION = 1;
const int MIN_VERSION = 65;	//��5λ��С�汾��
std::wstring AUTHORIZE_INFO = L"HQChart for c# ������ by Jones";


HQCHART_DLL_API int MainVersion()
{
	return MAIN_VERSION;
}

HQCHART_DLL_API int MinVersion()
{
	return MIN_VERSION;
}


HQCHART_DLL_API bool Run(const wchar_t* pJonsConfig, HQCHART_CALLBACK_PTR callback)
{
#ifdef _DEBUG
	HQChart::Complier::Log::SetLogStatus(1);
#endif

	ScriptLibrary::GetInstance();

	auto& customFunc = HQChart::Complier::CustomFunction::GetInstance();
	customFunc.Add(L"HK2SHSZ", 0);
	customFunc.Add(L"MARGIN", 1);
	customFunc.Add(L"EXTDATA_USER", 2);

	auto& customVar = HQChart::Complier::CustomVariant::GetInstance();
	customVar.Add(L"GONORTH");
	customVar.Add(L"MARGIN");
	customVar.Add(L"GONORTHR");
	customVar.Add(L"MARGINR");

	customVar.Add(L"HYBLOCK");		//������ҵ���
	customVar.Add(L"DYBLOCK");		//����������
	customVar.Add(L"GNBLOCK");		//��������
	customVar.Add(L"FGBLOCK");		//���������
	customVar.Add(L"ZSBLOCK");		//����ָ�����
	customVar.Add(L"ZHBLOCK");		//������ϰ��
	customVar.Add(L"ZDBLOCK");		//�����Զ�����
	customVar.Add(L"HYZSCODE");
	customVar.Add(L"GNBLOCKNUM");	//����������ĸ���
	customVar.Add(L"FGBLOCKNUM");	//���������ĸ���
	customVar.Add(L"ZSBLOCKNUM");	//����ָ�����ĸ���
	customVar.Add(L"ZHBLOCKNUM");	//������ϰ��ĸ���
	customVar.Add(L"ZDBLOCKNUM");	//�����Զ�����ĸ���
	customVar.Add(L"HYSYL");		//ָ����ӯ�ʻ����������ҵ����ӯ��
	customVar.Add(L"HYSJL");		//ָ���о��ʻ����������ҵ���о���

	HQChart::Complier::RunConfig config;
	config.SetCallbackProc(callback);
	if (!config.LoadJsonConfig(pJonsConfig)) return false;

	bool bSuccess = config.RunScript(config);
	return bSuccess;
}

HQCHART_DLL_API bool HQ_CALL AddFunction(const wchar_t* pStrName, int nArgCount)
{
	auto& func = HQChart::Complier::CustomFunction::GetInstance();
	std::wstring strName(pStrName);
	if (strName.empty()) return false;
	if (nArgCount < 0) return false;

	func.Add(pStrName, nArgCount);
	return true;
}

HQCHART_DLL_API bool HQ_CALL AddVariant(const wchar_t* pStrName)
{
	auto& customVar = HQChart::Complier::CustomVariant::GetInstance();
	std::wstring strName(pStrName);
	if (strName.empty()) return false;

	customVar.Add(strName);

	return true;
}

HQCHART_DLL_API const wchar_t* HQ_CALL GetAuthorizeInfo()
{
	return AUTHORIZE_INFO.c_str();
}
