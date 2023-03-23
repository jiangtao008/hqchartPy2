/*
Copyright (c) 2018 jones

https://github.com/jones2000/hqchartPy2/blob/master/LICENSE

��Դ��Ŀ https://github.com/jones2000/hqchartPy2

jones_2000@163.com

���ڼ��� (c++)
*/

#pragma once

namespace HQChart { namespace Helper {


class CalendarHelper
{
public:

	static unsigned short GetDayCount(unsigned short wYear, unsigned short wMonth);				//�õ�ĳһ���µ�����
	static bool IsLeapYear(unsigned short wYear);								//�Ƿ�Ϊ����
	static unsigned short CaculateWeekDay(unsigned short wYear, unsigned short wMonth, unsigned short wDay);	//�õ�ĳһ�������ڼ�
	static bool IsDateValid(unsigned short wYear, unsigned short wMonth, unsigned short wDay); // �����Ƿ���Ч
	
	//ũ���㷨���
	static long GetLunarLastMonthDay(unsigned int kp_year);//���ũ�����һ��������
	static unsigned char GetLeapMonth(unsigned int lunar_year);	//ȷ���Ƿ����ũ�������� ����������
	static unsigned char GetLeapMonthDay(unsigned int lunar_year); //����������,�������µ�����,30?29  
	static unsigned int GetLunarYearTotal(unsigned int lunar_year); // ũ������������,354?355 384 383
	static unsigned int IsLeapYear(unsigned int year);				//�Ƿ�Ϊ����
	static unsigned char GetDay(unsigned int year ,unsigned char month); //�жϵ��굱������
	static unsigned int GetSolarTotal(unsigned int solar_year, unsigned char solar_month); //����1900.1.1 ��  �������µ�����   
	static unsigned char  ConvertSolarToLunar(unsigned int kp_year,unsigned char kp_month,unsigned char kp_day); /* ��������ʱ�� ��  ��  �� */ 
	static long GetLunarDate(unsigned int kp_year,unsigned char kp_month,unsigned char kp_day);

protected:

	//��ر���
	static unsigned int solar_year,lunar_year;  
	static unsigned char solar_month,lunar_month;  
	static unsigned int solar_day,lunar_day;
};

}}