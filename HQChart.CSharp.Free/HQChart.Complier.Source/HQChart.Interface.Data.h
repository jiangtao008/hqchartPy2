/*
	Copyright (c) 2018 jones

	https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

	��Դ��Ŀ https://github.com/jones2000/hqchartPy2

	jones_2000@163.com

	�������ݽṹ (c++)
*/

#pragma once

namespace HQChart { namespace Complier {

#pragma pack(push,1)

struct HISTORY_ITEM
{
	int _nDate = 0;		//����  yyyymmdd
	int _nTime = 0;		//ʱ��  hhmmss
	double _dYClose = 0;	//ǰ���̼�	��ʱ-����
	double _dOpen = 0;		//��
	double _dHigh = 0;		//��
	double _dLow = 0;		//��
	double _dClose = 0;		//��
	double _dVol = 0;		//�ɽ���
	double _dAmount = 0;	//�ɽ����
	int	_nAdvance = 0;		//�������Ǽ���. �ֱ� B/S
	int _nDecline = 0;		//�����µ�����.

	//�ڻ�
	double _dPosition = 0;		//�ֲ�
	double _dSettle = 0;		//�����

	char	_exData[32] = { 0 };	//Ԥ������
};

//K����Ϣ
struct KDATA_INFO
{
	long _lPeriod;	//����
	long _lRight;	//��Ȩ

	//��ʼ����
	long _lStartDate;
	long _lStartTime;

	//��������
	long _lEndDate;
	long _lEndTime;

	long _lCount;	//K�߸���
};

struct SNAPSHOT_ITEM
{
	wchar_t _szSymbol[32];
	int _nDate;
	int _nTime;

	double _dYClose;	//ǰ���̼�
	double _dOpen;		//��
	double _dHigh;		//��
	double _dLow;		//��
	double _dClose;		//��
	double _dVol;		//�ɽ���
	double _dAmount;	//�ɽ����

	int	_nAdvance;		//�������Ǽ���. �ֱ� B/S
	int _nDecline;		//�����µ�����.

	//�嵵����
	double _dSellPrice[10];
	double _dSellVol[10];
	double _dBuyPrice[10];
	double _dBuyVol[10];
};

struct MINUTE_KLINE_ITEM
{
	int _nDate;
	int _nTime;

	double _dYClose;	//ǰ���̼�
	double _dOpen;		//��
	double _dHigh;		//��
	double _dLow;		//��
	double _dClose;		//��
	double _dVol;		//�ɽ���
	double _dAmount;	//�ɽ����
};

//�����������
struct SNAPSHOT_MINUTE_ITEM
{
	wchar_t _szSymbol[32];
	double _dYClose;
	int _nDate;
	int _nCount;

	HISTORY_ITEM _Minute[250];
};

#pragma pack(pop)


}
}