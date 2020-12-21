#pragma once
/*
* 日志记录实现头文件
* Version: 1.03
* Date 2015-07-02
* Description: 
* 2015-07-02 修改了与记录窗口的绑定方式
*			 增加了定时刷新的功能
* 2015-07-03 增加了dettachwnd
* 将互斥量改为临界区
* 2015-08-31 定时刷新升级更新;
*/
#include <afxmt.h>
//#include <MMSystem.h>
//#pragma comment(lib,"Winmm.lib")

class Logger
{
public:
	BOOL showLineCount;
	BOOL ShowTime;
	BOOL bPauseUpdate;
	BOOL bNoScroll;
	int LineCount;
	CString LogFilePathName;
	int bNameSetDone;		//已经设置完路径和名称
	CEdit * m_pLogWnd;
	CEdit m_LogWnd;
	int IsLogWndAttached;
	int AttachedType;		//方式，0，松；1，紧
	CString LogFilePath;
	CString LogFileName;
	CString slog;
	CString LogFilePreFix;
private:
	HANDLE hLogMutex;
	int logchanged;
	int LogTextLength;
	CString schangedlog;
	CFile CLogFile;
	int LogFileOpened;	//日志文件是否已经打开
	UINT TimerID;
//	CString LogFileName;
	CRITICAL_SECTION myCriticalSection;
	CCriticalSection myCriticalSection2;

public:	
	Logger()
	{
//		myCriticalSection.
		LogFilePath=_T(".\\Log");
		showLineCount=1;
		ShowTime=1;
		LineCount=0;
		LogTextLength=0;
		bPauseUpdate=FALSE;
		bNoScroll=FALSE;
//		hLogMutex=CreateMutex(NULL,FALSE,NULL);
		schangedlog.Empty();
		logchanged=0;
		LogFileOpened=0;
		IsLogWndAttached=0;
		bNameSetDone=0;
//		SetTimer(GetActiveWindow(),(UINT_PTR)this,100,MyTimerProc1);

		TimerID=0;
		//myCriticalSection.
	//	InitializeCriticalSection(&myCriticalSection);
/*
		TIMECAPS tc;
		if(timeGetDevCaps(&tc,sizeof(TIMECAPS))==TIMERR_NOERROR) 
		{
			timeBeginPeriod(100);
			TimerID=timeSetEvent(100,100,TimerProc,(DWORD_PTR)this,TIME_PERIODIC);//TIME_ONESHOT
		}
*/
	}
	Logger(CString FilePath)
	{

		Logger();
		LogFilePath=FilePath;
		SHCreateDirectoryEx(NULL,LogFilePath,NULL);	
		bNameSetDone=1;

	}

	~Logger()
	{
		if (TimerID!=0)
		{
//			timeKillEvent(TimerID);
//			timeEndPeriod(100);
		}
		if (IsLogWndAttached)
		{
			m_LogWnd.Detach();
		}
//		CloseHandle(hLogMutex);
		if (LogFileOpened)
		{
			CLogFile.Close();
		}
//		DeleteCriticalSection(&myCriticalSection);
	}
public:
	static	void CALLBACK MyTimerProc1(HWND hWnd,UINT nMsg,UINT nTimerid,DWORD dwTime)
	{
//		Logger * my = (Logger *)nTimerid;
//		my->UpdateLogDisplay();
	};

private:
	static void PASCAL TimerProc(UINT wTimerID, UINT msg,DWORD dwUser,
		DWORD dwl,DWORD dw2) 
	{
//		Logger * my;
//		my=(Logger *)dwUser;
//		my->UpdateLogDisplay();
		//timeBeginPeriod()
	}
public:
	int SetLogPathName(CString Path,CString FileName)
	{
		LogFilePath=Path;
		LogFilePreFix=FileName;
		bNameSetDone=1;
		if (LogFileOpened)
		{
			CLogFile.Close();
			LogFileOpened=0;
		}
		int j;
		j=SHCreateDirectoryEx(NULL,LogFilePath,NULL);
		return j;
	}
	int AttachWnd(HWND  hWnd)
	{
//		if (pWnd->IsKindOf(RUNTIME_CLASS(CEdit)))
//			pWnd->GetRuntimeClass()

		if (IsLogWndAttached) {return FALSE;}
		CWnd * pCWnd=CWnd::FromHandlePermanent(hWnd);
		if (pCWnd!=NULL)
		{
			m_pLogWnd=(CEdit *)pCWnd;
	//		m_pLogWnd=CWnd::FromHandle(pWnd->m_hWnd);
			AttachedType=0;
		}
		else
		{
			ASSERT(CWnd::FromHandlePermanent(hWnd) == NULL);
			// must not already be in permanent map

			if (hWnd == NULL)
				return FALSE;

			m_LogWnd.Attach(hWnd);
			m_pLogWnd=&m_LogWnd;
			AttachedType=1;
		}

//			pWnd->m_hWnd;
//			CEdit mywnd;
//			mywnd.Attach(pWnd->m_hWnd);

		m_pLogWnd->ModifyStyle(NULL,ES_MULTILINE|ES_AUTOVSCROLL|ES_SELECTIONBAR|ES_WANTRETURN);
		m_pLogWnd->Invalidate();
//			m_LogWnd.ModifyStyle(NULL,ES_PASSWORD);
		m_pLogWnd->SetLimitText(10485760);
//			m_LogWnd.MoveWindow(20,30,500,600,TRUE);
		IsLogWndAttached=1;
		TimerID=SetTimer(GetActiveWindow(),(UINT_PTR)this,100,(TIMERPROC)MyTimerProc1);
		//TIMERPROC 
		return true;
	}
	int Dettach()
	{
		if (IsLogWndAttached)
		{
			IsLogWndAttached=0;	
			if (AttachedType==1)
			{
				m_LogWnd.Detach();
			}
			m_pLogWnd=NULL;
		}
		KillTimer(GetActiveWindow(),TimerID);
		return true;
	}
	void LogTxt(CString s)
	{
		CString s2;

		LineCount++;
		if (showLineCount)
		{
			s2.Format(_T("%d:%s"),LineCount,s);
		}
		else
		{
			s2=s;
		}
		LogTextLength+=s2.GetLength();
//		WaitForSingleObject(hLogMutex,INFINITE);
//		EnterCriticalSection(&myCriticalSection)
		
		myCriticalSection2.Lock(INFINITE);
//		slog+=s2;
		if (logchanged==1)
		{
			schangedlog+=s2;
		}
		else
		{
			schangedlog=s2;
		}
		//m_log.ReplaceSel(s);
		logchanged=1;
		//	m_log.SetWindowTextW(slog);
		LogToFile(s);
	//	LeaveCriticalSection(&myCriticalSection);
		myCriticalSection2.Unlock();
//		ReleaseMutex(hLogMutex);

	//	UpdataLogDisplay();
	}
	void LogToFile(CString msg)
	{
		CString s1;
		CStringA sa1;
		//	CTime time1;
		//	time1.GetTime();
		CStringA DateStr,TimeStr,DateTimeStr;
		CStringA msgA;
		CString DateStrT;
		CString logfilename;
		int j;//,k,l;
#ifdef UNICODE
		j=WideCharToMultiByte(CP_ACP,0,msg,msg.GetLength(),msgA.GetBuffer(2048),2000,NULL,NULL);
		msgA.ReleaseBuffer(j);
#else
		msgA=msg;
#endif
		CTime time1=CTime::GetTickCount();
		CString timesecstr;
		timesecstr.Format(_T("%d"),time1);
		DateStr.Format("%04d-%02d-%02d ",time1.GetYear(),time1.GetMonth(),time1.GetDay());
		DateStrT.Format(_T("%04d-%02d-%02d "),time1.GetYear(),time1.GetMonth(),time1.GetDay());
		TimeStr.Format("%02d:%02d:%02d",time1.GetHour(),time1.GetMinute(),time1.GetSecond());
		DateTimeStr=DateStr+TimeStr;
		logfilename.Format(_T("%slog_%s.log"),LogFilePreFix,DateStrT);
		LogFilePathName=LogFilePath+_T("\\")+logfilename;

		SHCreateDirectoryEx(NULL,LogFilePath,NULL);	
		if (LogFileOpened)
		{
			CString oldfilename=CLogFile.GetFileName();
			if (oldfilename!=logfilename)
			{
				CLogFile.Close();
				LogFileOpened=0;
			}
		}
		if (!LogFileOpened) 
		{
			if (CLogFile.Open(LogFilePathName,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite|CFile::shareDenyWrite))
			{
				CLogFile.SeekToEnd();
				LogFileOpened=1;
				sa1.Format("\r\n----< %s >---- <Logfileopened> ========== \r\n",DateTimeStr);
				CLogFile.Write(sa1.GetString(),sa1.GetLength());
			}
		}
		if (LogFileOpened)
		{
			if (ShowTime)
			{
				sa1.Format("%s : %s",DateTimeStr,msgA);
			}
			else
			{
				sa1=msgA;
			}
			//		s1.C
			//		s1.CharToOemA();
			CLogFile.Write(sa1,sa1.GetLength());
		}
	}
	int UpdateLogDisplay(void)
	{
		int i,j,k;
		if (bPauseUpdate) return 0;
		if (IsLogWndAttached&&m_pLogWnd&&IsWindow(m_pLogWnd->m_hWnd))
		{
			//if (m_pLogWnd->GetWindowTextLength()>2000000)
			if (LogTextLength>2000000)
			{
				m_pLogWnd->SetSel(0,1000000,true);
			//	m_pLogWnd->ReplaceSel(_T(""));
				m_pLogWnd->Clear();
				LogTextLength=LogTextLength-1000000;
			}

		}
//		EnterCriticalSection(&myCriticalSection);
		if (!myCriticalSection2.Lock(INFINITE)) {return -1;}
		if (logchanged!=0)
		{
			if (IsLogWndAttached&&m_pLogWnd&&IsWindow(m_pLogWnd->m_hWnd))
			{
				int line1,line2;
				line1=m_pLogWnd->GetFirstVisibleLine();
				i=m_pLogWnd->GetLineCount();
				j=m_pLogWnd->LineIndex(i-1);

				m_pLogWnd->SetSel(j,j,true);
				k=m_pLogWnd->LineIndex(-1)+m_pLogWnd->LineLength(-1);
				m_pLogWnd->SetSel(k,k,true);

				m_pLogWnd->ReplaceSel(schangedlog);
				line2=m_pLogWnd->GetFirstVisibleLine();
				if (bNoScroll)
				{
					m_pLogWnd->LineScroll(line1-line2);
				}
			}
			schangedlog.Empty();
		}
		logchanged=0;
//		LeaveCriticalSection(&myCriticalSection);
		myCriticalSection2.Unlock();
		return 0;
	}
};