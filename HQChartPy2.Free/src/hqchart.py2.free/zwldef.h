#ifndef	__zealink_winlinux_define__
#define	__zealink_winlinux_define__
/////////////////////////////////////////////////////////////////////////////
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<stddef.h>
#include	<math.h>
#include	<stdarg.h>
#include	<ctype.h>
#include	<errno.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<sys/types.h>

#if (defined WIN32) || (defined WIN64)
	#include	<share.h>
	#include	<time.h>
	#include	<io.h>
	#include	<sys/utime.h>
	#include	<winsock2.h>
	#include	<windows.h>
	#include	<tchar.h>
#else
	#include	<wchar.h>
	#include	<unistd.h>
	#include	<pthread.h>
	#include	<dirent.h>
	#include	<fnmatch.h>
	#include	<zlib.h>
	#include	<netdb.h>
	#include	<signal.h>
	#include	<getopt.h>
	#include	<termios.h>
	#include	<sysexits.h>
	#include	<utime.h>
	#include	<syslog.h>

	#include	<netinet/in.h>
	#include	<arpa/inet.h>
	#include	<linux/fb.h>
	#include	<net/if.h>
	#include	<net/if_arp.h>

	#include	<sys/wait.h>
	#include	<sys/uio.h>
	#include	<sys/un.h>
	#include	<sys/socket.h>
	#include	<sys/ioctl.h>
	#include	<sys/mman.h>
	#include	<sys/io.h>
	#include	<sys/fcntl.h>
	#include	<sys/kd.h>
	#include	<sys/time.h>
	#include	<sys/param.h>
	#include	<sys/utsname.h>
	#include	<sys/resource.h>
	#include	<sys/termios.h>
#endif
#pragma pack(push,1)
/////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
	typedef	unsigned char		XBYTE;
	typedef	unsigned short		XWORD;
	typedef	short				XINT16;
	typedef	long				XINT32;
	typedef	unsigned long		XDWORD;
	typedef	__int64				XINT64;
	typedef	unsigned __int64	XBIGINT;
	typedef long double			XLDOUBLE;  // long double win32����8bytes�� linux����12bytes
	typedef unsigned long		XULONG;
#else
	typedef	unsigned char		XBYTE;
	typedef	unsigned short		XWORD;
	typedef	short				XINT16;
	typedef	int					XINT32;
	typedef	unsigned int		XDWORD;
	typedef	long long			XINT64;
	typedef	unsigned long long	XBIGINT;
	typedef double				XLDOUBLE;
	typedef unsigned long		XULONG;
#endif

#if (defined WIN32) || (defined WIN64)
	typedef	HANDLE	HTHREAD;
	typedef	HANDLE	HPIPE;

	typedef	int	socklen_t;
	#define	NOVTABLE __declspec(novtable)
	#ifdef TEST_SOLUTION
		#define PRIVATE   public
	#else
		#define PRIVATE   private
	#endif

	#ifdef TEST_SOLUTION
		#define PROTECTED   public
	#else
		#define PROTECTED   protected
	#endif
#else	//Global Define(like win)
	typedef	pthread_t	HTHREAD;
	typedef	int		HPIPE[2];
	typedef XDWORD			WPARAM;
	typedef XINT32			LPARAM;
	typedef const void		*LPCVOID;
	typedef const char		*LPCSTR;
	typedef char			*LPSTR;
	typedef const wchar_t	*LPCWSTR;
	typedef wchar_t			*LPWSTR;
	typedef	__U32_TYPE		__time32_t;
	typedef unsigned char	*LPBYTE;
	typedef XDWORD			COLORREF;
	typedef void			*LPVOID;
	typedef void			*HANDLE;
	typedef void			*HINSTANCE;
	typedef XINT32			BOOL;
	typedef XINT32			LRESULT;
	typedef int				SOCKET;
	typedef void*			HWND;
	typedef short			SHORT;
	typedef char			TCHAR;
	typedef const char* LPCTSTR;
	typedef char* LPTSTR;
	const XINT32 MAX_PATH=260;

	#define	FILE_BEGIN		0
	#define FILE_CURRENT	1
	#define FILE_END		2

	#define INVALID_SOCKET  (SOCKET)-1
	#define	WINAPI
	#define	NOVTABLE

	#define MAKEWORD(a,b)	((XWORD)(((XBYTE)(a))|((XWORD)((XBYTE)(b)))<<8))
	#define MAKELONG(a,b)	((XINT32)(((XWORD)(a))|((XDWORD)((XWORD)(b)))<<16))
	#define LOWORD(l)		((XWORD)(l))
	#define HIWORD(l)		((XWORD)(((XDWORD)(l)>>16)&0xFFFF))
	#define LOBYTE(w)		((XBYTE)(w))
	#define HIBYTE(w)		((XBYTE)(((XWORD)(w)>>8)&0xFF))
	#define RGB(r,g,b)		((COLORREF)(((XBYTE)(r)|((XWORD)((XBYTE)(g))<<8))|(((XDWORD)(XBYTE)(b))<<16)))

//critical section macro:
	typedef XINT32 HRESULT;
	typedef	pthread_mutex_t CRITICAL_SECTION;
	#define	InitializeCriticalSection(hMutex)	pthread_mutex_init(hMutex,NULL)
	#define	DeleteCriticalSection(hMutex)		pthread_mutex_destroy(hMutex)
	#define	EnterCriticalSection(hMutex)		pthread_mutex_lock(hMutex)
	#define	LeaveCriticalSection(hMutex)		pthread_mutex_unlock(hMutex)
	#define	InterlockedIncrement(pInt)			__sync_add_and_fetch(pInt,1)
	#define	InterlockedDecrement(pInt)			__sync_sub_and_fetch(pInt,1)
//map win func
	#define TlsAlloc() pthread_key_create()
	#define _vstprintf vsprintf
	#define _snprintf snprintf
	#define _sntprintf snprintf
	#define	lstrlenW(str) wcslen(str)
	#define	lstrlen(str) strlen(str)
	#define	lstrlenA(str) strlen(str)
	#define wsprintf	sprintf
	#define wsprintfW   swprintf
	#define wsprintfA	sprintf
	#define _istalnum   isalnum
	#define _istalpha	isalpha
	#define _istdigit	isdigit
	#define _atoi64 atoll
	#define _wtof(str)  wcstof(str, NULL)
	#define _wtoi64(str)    wcstoll (str, NULL, 10)
	#define _tfopen  fopen
	#define _wtol(str)  wcstol(str, NULL, 10)
	#define _wtoi(str)  wcstol(str, NULL, 10)
	#define sprintf_s sprintf
	#define	lstrcpy(str1,str2) strcpy(str1,str2)
	#define	lstrcpyA(str1,str2) strcpy(str1,str2)
	#define	lstrcpyn(str1,str2,size) strncpy(str1,str2,size)
	#define	lstrcpynW(str1,str2,size) wcscpy(str1,str2)
	#define	lstrcpynA(str1,str2,size) strncpy(str1,str2,size)
	#define strcpy_s(str1, size, str2) strncpy(str1, str2,size)
	//#define strcpy_s(str1, str2) strcpy(str1, str2)
	#define	lstrcat(str1,str2) strcat(str1,str2)
	#define	lstrcatA(str1,str2) strcat(str1,str2)
	#define	lstrcmp(str1,str2) strcmp(str1,str2)
	#define	lstrcmpA(str1,str2) strcmp(str1,str2)
	#define	lstrcmpi(str1,str2) strcasecmp(str1,str2)
	#define	lstrcmpiA(str1,str2) strcasecmp(str1,str2)
	#define	_stricmp(str1,str2) strcasecmp(str1,str2)
	#define	strnicmp(str1,str2,n) strncasecmp(str1,str2,n)
	#define	closesocket(h)  ::close(h)
	#define	Sleep(lSeconds)	usleep(lSeconds*1000L)
	#define		ARRAYSIZE(a)  (sizeof(a)/sizeof(a[0]))
	#define  _T(x)	x
	#define TEXT(x) 	x
	typedef struct _LARGE_INTEGER
	{
		struct
		{
			XDWORD	LowPart;
			XINT32	HighPart;
		};
		XINT64	QuadPart;
	}LARGE_INTEGER;

#ifndef FILETIME
	typedef struct _FILETIME
	{
		XDWORD	dwLowDateTime;
		XDWORD	dwHighDateTime;
	}FILETIME,*PFILETIME,*LPFILETIME;
#endif

	typedef struct _SYSTEMTIME
	{
		XWORD	wYear;
		XWORD	wMonth;
		XWORD	wDayOfWeek;
		XWORD	wDay;
		XWORD	wHour;
		XWORD	wMinute;
		XWORD	wSecond;
		XWORD	wMilliseconds;
	}SYSTEMTIME,*PSYSTEMTIME,*LPSYSTEMTIME;
	typedef struct tagDBTIMESTAMP
    {
		short	year;
		XWORD	month;
		XWORD	day;
		XWORD	hour;
		XWORD	minute;
		XWORD	second;
		XDWORD	fraction;
    }DBTIMESTAMP;
#endif

#ifndef	TRUE
	#define	TRUE	1
#endif

#ifndef	FALSE
	#define	FALSE	0
#endif


#ifndef	DELETE_PTR
	#define	DELETE_PTR(p) if(p){delete p;p=NULL;}
#endif

#ifndef	DELETE_WNDPTR
	#define	DELETE_WNDPTR(p) if(p){if(p->m_hWnd)p->DestroyWindow();delete p;p=NULL;}
#endif

#ifndef	DELETE_PTRA
	#define	DELETE_PTRA(p) if(p){delete[] p;p=NULL;}
#endif

#ifndef	COPY_STRING
	#define	COPY_STRING(p1,p2)\
	lstrcpyn(p1,p2,sizeof(p1))
#endif

#ifndef	COPY_STRINGEX
	#define	COPY_STRINGEX(p1,p2)\
	memset(p1,0,sizeof(p1));\
	lstrcpyn(p1,p2,sizeof(p1));
#endif

#ifndef	WLSTAT_DEFINE
	#define	WLSTAT_DEFINE
	#ifdef	_WIN32
		typedef	struct _stati64 STAT_STRU;
		#define	STAT_PROC _stati64
		#define	FSTAT_PROC _fstati64
	#else
		typedef	struct stat64 STAT_STRU;
		#define	STAT_PROC stat64
		#define	FSTAT_PROC fstat64
	#endif
#endif

#if (defined WIN32) || (defined WIN64)
	#define	WSA_LAST_ERROR	WSAGetLastError()
	#define	LAST_ERROR	GetLastError()

	#ifndef	CLOSE_HANDLE
		#define	CLOSE_HANDLE(h) if(h){CloseHandle(h);h=NULL;}
	#endif

	#ifndef	CLOSE_FILE
		#define	CLOSE_FILE(h) if(h!=INVALID_HANDLE_VALUE){CloseHandle(h);h=INVALID_HANDLE_VALUE;}
	#endif

	#ifndef	CLOSE_SOCKET
		#define	CLOSE_SOCKET(h)	if(h!=INVALID_SOCKET){closesocket(h);h=INVALID_SOCKET;}
	#endif

	#ifndef	THREAD_CREATE
		#define	THREAD_CREATE(AfxProc,Class,Method)\
		DWORD WINAPI AfxProc(LPVOID lpParam)\
		{\
			CoInitialize(NULL);\
			try\
			{\
				((Class*)lpParam)->Method();\
			}\
			catch(...)\
			{\
			}\
			CoUninitialize();\
			return(0);\
		}
	#endif

	#ifndef	THREAD_SAFE_CLOSE
		#define	THREAD_SAFE_CLOSE(h,tm)\
		if(h)\
		{\
			if(WaitForSingleObject(h,tm)!=WAIT_OBJECT_0)\
			{\
				TerminateThread(h,0);\
			}\
			CloseHandle(h);\
			h = NULL;\
		}
	#endif

	#define	DECLARE_FILEOPEN(fp,filename,openmode)	FILE*fp=_fsopen(filename,openmode,SH_DENYNO)
#else	//Linux
	#define	WM_USER		0x0400

	#define	WSA_LAST_ERROR	errno
	#define	LAST_ERROR	errno

	#ifndef	CLOSE_FILE
		#define	CLOSE_FILE(h) if(h!=NULL){fclose(h);h=NULL;}
	#endif

	#ifndef	CLOSE_SOCKET
		#define	CLOSE_SOCKET(h)	if(h>0){closesocket(h);h=-1;}
	#endif

	#ifndef	THREAD_CREATE
		#define	THREAD_CREATE(AfxProc,Class,Method)\
		void*AfxProc(void*lpParam)\
		{\
			try\
			{\
				((Class*)lpParam)->Method();\
			}\
			catch(...)\
			{\
			}\
			return(NULL);\
		}
	#endif

	#ifndef	THREAD_SAFE_CLOSE
		#define	THREAD_SAFE_CLOSE(h,tm)\
		if(h)\
		{\
			pthread_join(h,NULL);\
			h = 0;\
		}
	#endif

	#define	DECLARE_FILEOPEN(fp,filename,openmode)	FILE*fp=fopen(filename,openmode)
#endif
/////////////////////////////////////////////////////////////////////////////
#ifndef	ZERO_STRING
	#define	ZERO_STRING(s) memset(s,0,sizeof(s))
#endif

#ifndef	ROUNDUP_SIZE
	#define ROUNDUP_SIZE(size,amount)	(((ULONG)(size)+((amount)-1))&~((amount)-1))
#endif

#ifndef	CHECK_STRING_ENDNULL
	#define	CHECK_STRING_ENDNULL(s) s[sizeof(s)-1] = 0;
#endif

#ifdef	_WIN32
	#ifdef	_UNICODE
		#define	__string_lwr__(s) _wcslwr(s)
		#define	__string_upr__(s) _wcsupr(s)
		#define	__bigint_to_string__(i,s,b) _i64tow(i,s,b)
		#define	__string_to_bigint__(s) _wtoi64(s)
		#define	__long_to_string__(i,s,b) _itow(i,s,b)
		#define	__string_to_long__(s) _wtol(s)
		#define	__string_to_double__(s) _wtof(s)
		#define	__string_search__(s,sub) wcsstr(s,sub)
		#define	__string_char__(s,c) wcschr(s,c)
		#define	__csprintf__ swprintf
	#else
		#define	__string_lwr__(s) _strlwr(s)
		#define	__string_upr__(s) _strupr(s)
		#define	__bigint_to_string__(i,s,b) _i64toa(i,s,b)
		#define	__string_to_bigint__(s) _atoi64(s)
		#define	__long_to_string__(i,s,b) _itoa(i,s,b)
		#define	__string_to_long__(s) atol(s)
		#define	__string_to_double__(s) atof(s)
		#define	__string_search__(s,sub) strstr(s,sub)
		#define	__string_char__(s,c) strchr(s,c)
		#define	__csprintf__ sprintf
	#endif
	#define	__stringA_to_bigint__(s) _atoi64(s)
	#define	__bigint_to_stringA__(i,s)	_i64toa(i,s,10)
	#define	ustrcmpiA(str1,str2) _stricmp(str1,str2)
	#define	__long_to_stringA__(i,s)	_itoa(i,s,10)
	#define	ustrcmp(str1,str2) _tcscmp(str1,str2)
	#define	ustrcmpi(str1,str2) _tcsicmp(str1,str2)
	#define	ustrlen(str) lstrlen(str)
	#define	ustrnicmp(str1,str2,n) _strnicmp(str1,str2,n)
#else
	#define	__string_lwr__(s)  _strlwr(s)
	#define	__string_upr__(s)  _strupr(s)
	#define	__bigint_to_string__(i,s,b)    CONVERT_BIGINT(s,i)
	#define	__string_to_bigint__(s)  atoll(s)
	#define	__long_to_string__(i,s,b)  sprintf(s, "%d", i) 
	#define	__string_to_long__(s) atol(s)
	#define	__string_to_double__(s) atof(s)
	#define	__string_search__(s,sub) strstr(s,sub)
	#define	__string_char__(s,c) strchr(s,c)
	#define	__csprintf__ sprintf
	#define	__stringA_to_bigint__(s) atoll(s)
	#define	__bigint_to_stringA__(i,s)	CONVERT_BIGINT(s,i)
	#define	ustrcmpiA(str1,str2) strcasecmp(str1,str2)
	#define	__long_to_stringA__(i,s)	sprintf(s, "%d", i) 
	#define	ustrcmp(str1,str2) strcmp(str1,str2)
	#define	ustrcmpi(str1,str2) strcasecmp(str1,str2)
	#define	ustrlen(str) strlen(str)
	#define	ustrnicmp(str1,str2,n) strnicmp(str1,str2,n)
#endif

//ͨ�ú궨��
#ifndef	__SAFE_DELETE_GDIOBJ__	//ɾ��GDI���
#define	__SAFE_DELETE_GDIOBJ__(hObj)\
	if(hObj)\
	{	DeleteObject(hObj);\
		hObj = NULL;\
	}
#endif

#ifndef	__DELETE_OBJECTS__	//ɾ��GDI�������
#define __DELETE_OBJECTS__(objs)\
	for(int i=0;i<ARRAYSIZE(objs);++i)\
	{\
		__SAFE_DELETE_GDIOBJ__(objs[i])\
	}
#endif

#ifndef	COLORREF2RGB
	#define COLORREF2RGB(Color) (Color&0XFF00)|((Color>>16)&0XFF)|((Color<<16)&0XFF0000)
#endif

#ifndef	__CHECK_STRING__
	#define	__CHECK_STRING__(s) s[sizeof(s)/sizeof(s[0])-1] = 0
#endif

#ifndef	__define_protocol_header__
#define	__define_protocol_header__
typedef struct tagProtocolHead
{
	__time32_t	time_check;		//ʱ��У��
	XDWORD	req_ans_command;	//req/ans command id
	XDWORD	source_size;		//source size(no compress)
	XDWORD	package_size;		//package size,if no compress,this must be 0
	XDWORD	self_param;			//HWND(x86)or other
}protocol_head,*pprotocol_head;

#endif

//֧�ֵ����ݿ�����
enum
{
	DBMS_MSSQL=0,	//sql server 2000/2005/2008
	DBMS_MYSQL,		//mysql 4.x/5.x
	DBMS_ORACLE,	//oracle 8i/9i/10g/11g
	DBMS_DB2,		//ibm db2 8.x/9.x
	DBMS_MONGODB,
};

enum
{
	__umsoem_zealink__=0,		//��˾ͨ�ð汾
	__umsoem_common__,			//��Go�ʹ�
	__umsoem_chinaamc__,		//���Ļ����ư汾
	__umsoem_reserved0__,		//��ȱ
	__umsoem_reserved1__,		//��ȱ
	__umsoem_reserved2__,		//��ȱ
	__umsoem_huaxia_ty__,		//����Ͷ��
	__umsoem_uni__,				//����-��Ͷ��
	__umsoem_topboce__,			//�����Ƹ���
	__umsoem_cninfo_notuse_,	//��֤��Ϣ(����)
	__umsoem_gogoal__,			//��������ת��
	__umsoem_investdata__,		//Ͷ������¼��ƽ̨
	__umsoem_uni2__,			//����-�Ź�ѧ��
	__umsoem_uni3__,			//����-��Ѷ�ն�
	__umsoem_reset__,           // ��˼
	__umsoem_uni4__,			//�ൺ��Ͷ��	
	__umsoem_uni5__,			//��Ͷ��-����A���о�Ժ


	//��˾���ذ汾 101 - 110
	__umsoem_common_local_1_=101,			
	__umsoem_common_local_2_,	//���ϵͳ
	__umsoem_common_local_3_,	//���ſͻ���
	__umsoem_common_local_4_,	//UTS���ڴ�����
	__umsoem_university__,		//��Уʵѵƽ̨
	__umsoem_common_local_6_,
	__umsoem_common_local_7_,
	__umsoem_common_local_8_,
	__umsoem_common_local_9_,
	__umsoem_common_local_10_,

	__umsoem_common_btoc_=201,
};

//���ݿ����ӽṹ
#ifndef	__udb_conninfo__
#define	__udb_conninfo__
typedef struct tagUDBConnInfo
{
	XBYTE	dbtype;	
	//���ݿ����:
	//0:sql server
	//1:mysql
	//2:oracle
	//3:db2
	//4:mongodb

	XDWORD	policy;
	//����:
	//0x01 : ODBC����
	//0x02 : windows�����֤
	//0x04 : OCI����
	//0x08 : ORACLE���ݿ�MS����
	//0x10 : ���ݿ�ֻ��

	//0x0100 : excel

	char	dburl[64];		//��ַ
	char	dbuser[32];		//�û���
	char	dbowner[32];	//������
	char	dbpasswd[32];	//����
	char	utsmask[32];	//ʱ�����

	char	spaceTable[32];	//���ݱ�ռ�
	char	spaceIndex[32];	//������ռ�
	char	spaceText[32];	//���ı���ռ�

	char	dbname[32];		//���ݿ�����
	char	dbScript[32];	//������Ϣ
}udbconn_info,*pudbconn_info;
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
	__umymessage_netcommand__=WM_USER+0x9F01,	//������Ϣ
	__umessage_wndtrace__,				//����ƶ�������Ϣ
	__umessage_scrollbar__,				//��������Ϣ;����:wparam=1;����:wparam=0

	__umymessage_parentdraw__,			//������Ϣ�������ڻ���
	__umymessage_parent_mousemove__,	//��������ƹ���Ϣ��������
	__umymessage_parent_lbtndown__,		//����������������Ϣ��������
	__umymessage_parent_rbtndown__,		//��������Ҽ�������Ϣ��������
	__umymessage_parent_lbtnup__,		//�����������ͷ���Ϣ��������
	__umymessage_parent_rbtnup__,		//��������Ҽ��ͷ���Ϣ��������
	__umymessage_parent_lbtndblclk__,	//������˫��
	__umymessage_parent_mousewheel__,	//��껬���¼�
	__umymessage_parent_keydown__,		//���̰���
	__umymessage_parent_keyup__,		//���̷ſ�
	__umymessage_parent_return__,		//���»س���
	__umymessage_newhq_keydown__,		//��hq���̰���
	__umymessage_parent_lbtndblclk1__,	//������˫��(�����кź��к�)

	__umymessage_mins_pageup__,			//��ʷ��������ͼ�����¼�
	__umymessage_mins_pagedown__,		//��ʷ��������ͼ�����¼�
	__umymessage_mins_hwnd__,

	__umymessage_getstock_position__,  //��Ʊ�ֲ���Ϣ��巢����Ϣ
	__umymessage_getfund_position__, //����
	__umymessage_getfutures_position__,//�ڻ��ֲ���Ϣ��巢����Ϣ
	__umymessage_getbond_position__,   //ծȯ�ֲ���Ϣ��巢����Ϣ
	__umymessage_getexchange_position__, //���

	__umymessage_setstock__,
	__umymessage_setblock__,
	__umymessage_setindex__,
	__umymessage_setcode__,
	__umymessage_overlay__,				//��������
	__umymessage_uxsnormal__,
	__umymessage_setblock2__,
	__umymessage_setkeyindex__,

	__umymessage_add_minchart__,		//���������������ͼ
	__umymessage_del_minchart__,		//���������������ͼ
	__umymessage_ret_minchart__,		//������������ͼ

	__umymessage_self_block__,			//�Զ������

	__umymessage_his_minute__,			//��ʷk�� ���� ��ݼ�����command
	__umymessage_his_day__,				//
	__umymessage_his_week__,			//
	__umymessage_his_month__,			//
	__umymessage_his_season__,			//
	__umymessage_his_year__,			//��ʷk�� ���� ��ݼ�����command

	__umymessage_zb_inof__,				//ָ����Ϣ
	__umymessage_zb_param__,			//ָ�����

	__umymessage_parent_size_zoom_in__,	//�Ŵ�
	__umymessage_parent_size_zoom_out__,//��С
	__umymessage_parent_close__,        //���͹ر���Ϣ��������
	__umymessage_preparentdraw__,		//������Ϣ�������ڻ���(�Ӵ��ڻ���֮ǰ����)
	__umymessage_afterdraw__,			//���ڻ�ͼ���
	__umymessage_char_curve_selected__,	//ѡ������Ϣ (chart)
	__umymessage_showwindows__,			//��ʾ���ش����¼�

	__umymessage_resetblock__,			//���ð��
	__umymessage_addnewblock__,			//�½����
	__umymessage_deleteblock__,			//ɾ�����
	__umymessage_settype__,				//��������
	__umymessage_reload__,				//���¼���

	__umymessage_remove_module__,		//ɾ��һ������ wParam=m_lIdentify

	__umymessage_change_module__,	//����л����������� wParam=m_lIdentify lParam=�µ�����

	__umymessage_news_content__,

	__umymessage_maxmin_panle__,	//�����С����� wParam=(1.��� 0.��ԭ) lParam= UMyModule9*
	__umymessage_size_panel___,		//������С
	__umymessage_changemax_panle__,	//�ı�������  lParam= UMyModule9* �������л�������ͺ�ʹ��������
	__umymessage_nextmax_panle__,	//�л�����һ��ģ�����
	__umymessage_prevmax_panle__,	//�л�����һ��ģ�����

	__umymessage_closepanel__,		//�رչ�����	

	__umymessage_open_workspace__,
	__umymessage_show_bottomtoolbar__,	//��ʾ|���صײ������� wParam= 0 ���� 1 ��ʾ 2 ȡ��
	__umymessage_show_righttoolbar__,	//��ʾ|�����ұ߹����� wParam= 0 ���� 1 ��ʾ 2 ȡ��
	__umymessage_show_lefttoolbar__,		//��ʾ|������߹����� wParam= 0 ���� 1 ��ʾ 2 ȡ��

	__umymessage_set_groupkeyindex__, //���ù������еĹ������KeyIndex����

	__umymessage_enum_all_umsmodule__, //ö�������е�����ģ�� ����iUMSPublic

	__umymessage_run__,		//֪ͨ������ִ��

	UMS_SHOWWINDOW,			//������ʾ/������Ϣ

	__umymessage_setport__,		//������ϴ�����Ϣ
	__umymessage_setportmul__,	//���Ͷ���ϴ�����Ϣ

	__umymessage_rptsetplan__,	//����-���÷���
	__umymessage_rptsaveplan__,	//����-���淽��

	__umymessage_exitdialog__,	//�̰߳�ȫ�˳��Ի�����Ϣ

	__umymessage_parent_checkboxselall__, //���checkboxȫѡ��Ϣ

	__umymessage_callback_setcode__=0x1522,	//��������Ϣ, ����Ϣ��������

	__umymessage_setstocklist__,	//����Ʊ����
	__umessage_panel_init__,		//����ʼ�����
	__umymessage_homepage__,		//�л�����ҳ
	__umymessage_setcode2__,        //���鱨��ģ��˫����Ϣ
	__umymessage_parentpaste__,		//�򸸴��ڷ���ճ����Ϣ

	__umymessage_global_param__,	//ȫ�ֲ����䶯
	__umymessage_active_panel__,	//�������
	__umymessage_active_stktrade__,	//�������鱨�۹�����

	__umymessage_active_panel_max__=__umymessage_active_panel__+200,

};
/////////////////////////////////////////////////////////////////////////////////////////////////
#define	NUM_PRICE_LEVEL_L2	10	// Level2��λ����(10��)
#define	NUM_PRICE_LEVEL_L1	5	// Level1��λ����(5��)
typedef	struct	tagStockAttrib	//֤ȯ����
{
	XBIGINT	Market:8;	//�г�
	XBIGINT	Type:8;		//������:���
	XBIGINT	decNum:3;	//��ʾ��С��λ��
	XBIGINT	unitBase:3;	//������λλ��
	//������(�����Եĺ��嶼��ȷ���ģ��Ժ�����,�����ܸ���)
	XBIGINT	A:1;	//GP:A��		JJ:���ʽ����	ZQ:��ծ			HG:��Ѻʽ    �ڻ�:����				����:NYSE		HK:MAIN
	XBIGINT	B:1;	//GP:B��		JJ:����ʽ����	ZQ:��ծ			HG:���ʽ	 �ڻ�:�Ϻ�				����:AMEX		HK:GEM
	XBIGINT	C:1;	//GP:�¹��깺	JJ:LOF			ZQ:תծ			HG:��ծ		 �ڻ�:֣��				����:NASDAQ		HK:NASD
	XBIGINT	D:1;	//GP:����		JJ:ETF			ZQ:����Ʊ��		HG:��ծ		 �ڻ�:�Ƿ�Ϊ����						HK:ETS

	XBIGINT	E:1;	//GP:			JJ:FOF			ZQ:����ծ															
					//HK:ShortSellFlag(Indicator for short-sell authorization) 1:Short-sell allowed 0:Short-sell not allowed
	XBIGINT	F:1;	//GP:			JJ:������ϲ�Ʒ
					//HK:EFNFlag  (EFN Indicator for Bonds) 1:EFN 0:Non-EFN
	XBIGINT	G:1;	//GP:			JJ:
					/*
						HK:CallPutFlag (Indicator of whether the warrant or structured product is a call or put option for Warrants, Basket Warrants and Structured Product specific data)
						For Derivative Warrants/Basket Warrants:	1:Call 0:Put
						For ELI & CBBC:								1:Bull 0:Bear/Rang
					*/
	XBIGINT	H:1;	//GP:			JJ:

	XBIGINT	I:1;	//GP:			JJ:
	XBIGINT	J:1;	//GP:			JJ:

	XBIGINT	unitContract:16;	//�ڻ���Լ��λ	//HK:Board lot size for the security
//��������
	XBIGINT	TS:2;			//1:����;2:����
	XBIGINT TRADETIME:5;	//������ʱ������
	XBIGINT CURRENCY:4;		//���ҵ�λ	
							//0: Chinese Renminbi
							//1: Hong Kong dollars
							//2: US dollars
							//3: Euro
							//4: Japanese Yen
							//5: United Kingdom Sterling
							//6: Canadian Dollars
							//7: Singapore Dollars
	XBIGINT	selfStock:1;	//��ʶ�Ƿ��Ѿ�������ѡ��
	XBIGINT	Reserved:4;
}stock_attrib,*pstock_attrib;

typedef struct tagStockIndex	//���
{
	stock_attrib	attrib;		//����

	char	ansiSymbol[10];

	TCHAR	szSymbol[10];
	TCHAR	szName[21];

	XINT32	secAccess;
	XINT32	verData;
	XINT32	stkIndex;

	XINT32	preClosepx;
	XINT32	lastPrice;
	XINT32	highPx;

	XINT64	mktCapital;		//������ͨ�ɱ�
	TCHAR	safeSymbol[12];

	XDWORD	crcCheck;
}STOCK_INDEX,*PSTOCK_INDEX;

typedef struct tagMARKETDATA3	//�ͻ����ڴ�������(�ް汾��)
{
	XINT32	dataTimeStamp;					// ���ݲ�����ʱ�䣬��163025��ʾ16:30:25

	XINT32	preClosePx;						// ���ռ�
	XINT32	openPx;							// ��
	XINT32	highPx;							// ���
	XINT32	lowPx;							// ���

	XINT32	lastPrice;						// ����

	XINT64	bidSize[NUM_PRICE_LEVEL_L2];	// ������
	XINT32	bidPx[NUM_PRICE_LEVEL_L2];		// �����
	XINT64	offerSize[NUM_PRICE_LEVEL_L2];	// ������
	XINT32	offerPx[NUM_PRICE_LEVEL_L2];	// ������

	XINT32	numTrades;						// �ɽ�����
	XINT64	totalVolumeTrade;				// �ɽ�����
	XINT64	totalValueTrade;				// �ɽ��ܽ��
	XBIGINT	volInside;						// ��������
	XBIGINT	volOutside;						// ��������
	XBIGINT	flowInside;						// �ֽ�����
	XBIGINT	flowOutside;					// �ֽ�����

	union
	{
		XBIGINT	vol_5;	//5�վ���
		struct
		{
			XWORD HALT_NUM;			//ͣ�Ƽ���
			XWORD UP_NUM;			//���Ǽ���
			XWORD DOWN_NUM;			//�µ�����
			XWORD UN_CHANGE_NUM;	//ƽ�̼���
		}index;	//ָ��
	};

	XINT64	totalBidQty;					// ί������
	XINT32	weightedAvgBidPx;				// ��Ȩƽ��ί��۸�
	XINT32	altWeightedAvgBidPx;			// ������Ȩƽ��ί��۸�
	XINT64	totalOfferQty;					// ί������
	XINT32	weightedAvgOfferPx;				// ��Ȩƽ��ί���۸�
	XINT32	altWeightedAvgOfferPx;			// ������Ȩƽ��ί���۸�

	XINT32	IOPV;							// IOPV��ֵ��ֵ
	XINT32	yieldToMaturity;				// ����������
	XINT64	totalWarrantExecQty;			// Ȩִ֤�е�������

	union
	{
		XINT64	warLowerPx;					// Ȩ֤��ͣ�۸� 			
		struct 
		{
			XINT32	lUpRate;				//1��������
			XINT32	lValue;					//δ��
		};
	};

	XINT64	warUpperPx;						// Ȩ֤��ͣ�۸�

	XINT32	pxWeek1;
	XINT32	pxWeek4;
	XINT32	pxWeek13;
	XINT32	pxWeek26;
	XINT32	pxWeek52;
	XINT32	pxWeekY;

	XINT32	mineMask;
	double	dSignal;		//�ź�ֵ

	XDWORD	verData;		//���ݸ��°汾��
}market_data3,*pmarket_data3;

typedef struct tagUXSTimeSeed
{
	XDWORD		year:6;		//[year%60]
	XDWORD		month:4;
	XDWORD		day:5;
	XDWORD		hour:5;
	XDWORD		minute:6;
	XDWORD		second:6;
	XDWORD		seed;
}uxs_timeseed,*puxs_timeseed;

typedef struct tagUXSTreeData
{
	XBYTE	isGroup;			//�Ƿ����
	XINT32	iconIndex;			//ͼ��ID
	XINT64	parentCode;			//��ID
	XINT64	thisCode;			//����ID
	union
	{
		XWORD	wName[32];		//��ʾ����:�ϰ汾����
		char	szName[64];		//��ʾ����:�ϰ汾����
		char	szOwner[64];	//������
	};
	union
	{
		XWORD	wInfo[64];		//��ע��Ϣ
		char	szInfo[128];	//��ע��Ϣ
		char	szTitle[128];	//������Ϣ
	};
	XINT32	extLength;			//��չ���ݳ���
	XINT32	extLength2;			//��չ����2����
	XINT32	extLength3;			//��չ����3����
	XINT32	extLength4;			//��չ����4����
	XINT32	extLength5;			//��չ����3����
	XINT32	extLength6;			//��չ����4����
	XINT64  jobid;
	char	reserved[32];		//������Ϣ
	char	dataBuffer[1];		//����������
}uxs_treedata,*puxs_treedata;

typedef struct tagUXSTaskKeyValue
{
	char	keyName[31];
	XBYTE	sizeData;
	char	varData[64];
}uxstask_keyvalue,*puxstask_keyvalue;
#define __maxuxs_keyvalue__ 8

typedef struct tagUXSTaskMessage
{
	XINT64	taskIndex;		//����ID
	char	taskOwner[32];	//��������������
	char	taskName[64];	//��������

	XBYTE	runStatus;		//��ǰ����״̬
	XINT32	lastDate;		//�����������
	XINT32	lastTime;		//�������ʱ��

	XINT32	runCount;		//�������д���
	XINT32	addCount;		//������¼����
	XINT32	updateCount;	//�޸ļ�¼����
	XINT32	errCount;		//ɾ����¼����
	XBYTE	nKeyValue;		//������������

	XBYTE	runNow;			//�������б�־
	XBYTE	runStop;		//����ֹͣ��־

	uxstask_keyvalue	keyValue[__maxuxs_keyvalue__];

	char	taskMessage[128];	//������Ϣ

	XINT32	rdsVersion;		//���ݼ��汾��
	XINT32	rdsSize;		//���ݼ�����
	union
	{
		XINT64	ptrBuffer;		//���ݼ�����,���ǵ�X64��ָ�����,ռ�õ���8���ռ�
		LPSTR	rdsBuffer;
	};
	XBYTE	maskDelete;			//ɾ�����
	XINT32	posProgress;		//��ǰ����
	XINT32	dateStart;			//����ʼ����
	XINT32	dateEnd;			//�����������

////// go-goal
	XINT32	addnum;		//������¼(����)
	XINT32	updatenum;	//�޸ļ�¼(����)
	XINT32	errnum;		//ɾ����¼(����)
//////
	char	Reserved[87];		//������Ϣ
}uxstask_message,*puxstask_message;
enum
{
	__uxstask_idle__=0,	//����
	__uxstask_wait__,	//�ȴ�����
	__uxstask_run__,	//����
	__uxstask_error__,	//�д�����
};
/////////////////////////////////////////////////////////////////////////////////////////////////
const XDWORD	UERROR_NO=0;
const XDWORD	UERROR_UNKNOW=9999;
/////////////////////////////////////////////////////////////////////////////
//system error:
const XDWORD UERROR_MALLOC=101;		//malloc/new data error
const XDWORD UERROR_NETWORK=102;		//net work error
const XDWORD UERROR_NOTSUPPORT=103;	//not support
const XDWORD UERROR_SERIAL=104;		//error serial id
const XDWORD UERROR_SRVNOTRUN=105;	//service not run
const XDWORD UERROR_BUSY=106;		//system busy
const XDWORD UERROR_NODATA=107;		//����һ�£���������
/////////////////////////////////////////////////////////////////////////////
//public error:
const XDWORD UERROR_ACCOUNTEXIST=201;	//�ʺ��Ѵ���
const XDWORD UERROR_ACCOUNTNOTEXIST=202;	//�ʺŲ�����
const XDWORD UERROR_PASSWD=203;			//passwd error
const XDWORD UERROR_NETWORKCARD=204;		//network card denied
const XDWORD UERROR_DISABLED=205;		//disabled error
const XDWORD UERROR_EXPIRED=206;			//expired error
const XDWORD UERROR_IPADDRESS=207;		//ipaddress error
const XDWORD UERROR_OVERMAX=208;			//over max
const XDWORD UERROR_DENIED=209;			//denied

const XDWORD UERROR_FILEOPEN=301;		//open file error
const XDWORD UERROR_FILESEEK=302;		//seek file error
const XDWORD UERROR_FILEREAD=303;		//read file error
const XDWORD UERROR_FILEWRITE=304;		//write file error
const XDWORD UERROR_QUOTA=305;			//dir quota

const XDWORD UERROR_DBCONNSRV=401;		//connect to database server
const XDWORD UERROR_DBREAD=402;			//read recordset error
const XDWORD UERROR_DBWRITE=403;			//write recordset error
const XDWORD UERROR_TABLENOTEXIST=404;	//������
const XDWORD UERROR_UTSMASK=405;			//ʱ����������
const XDWORD UERROR_CREATETABLE=406;		//������ʧ��
///////////////////////////////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
#endif
