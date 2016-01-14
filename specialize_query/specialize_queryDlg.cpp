
// specialize_queryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "specialize_query.h"
#include "specialize_queryDlg.h"
#include "afxdialogex.h"
#include "afxsock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cspecialize_queryDlg 对话框

Cspecialize_queryDlg::Cspecialize_queryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cspecialize_queryDlg::IDD, pParent)
{
	m_hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cspecialize_queryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_keyword, m_edit_keyword);
	DDX_Control(pDX, IDC_COMBO_organization, m_combobox_organization);
	DDX_Control(pDX, IDC_LIST_specialize, m_listctrl_specialize);
}

BEGIN_MESSAGE_MAP(Cspecialize_queryDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_organization, &Cspecialize_queryDlg::OnCbnSelchangeComboorganization)
	ON_EN_CHANGE(IDC_EDIT_keyword, &Cspecialize_queryDlg::OnEnChangeEditkeyword)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_specialize, &Cspecialize_queryDlg::OnNMRClickListspecialize)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_specialize, &Cspecialize_queryDlg::OnNMDblclkListspecialize)
	ON_COMMAND(ID_LISTCTRL_new, &Cspecialize_queryDlg::OnListctrlnew)
	ON_COMMAND(ID_LISTCTRL_edit, &Cspecialize_queryDlg::OnListctrledit)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// Cspecialize_queryDlg 消息处理程序

BOOL Cspecialize_queryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CString t_cs;
	char t_ch[BUFFERSIZE]={0};

	AfxSocketInit();
	WORD t_wVersionRequested;
	WSADATA t_wsaData;
	t_wVersionRequested=MAKEWORD(2,0);
	WSAStartup(t_wVersionRequested,&t_wsaData);
	char t_hostname[256];   
	gethostname(t_hostname,256);
	m_hostname=this->char2unicode(t_hostname,sizeof(t_hostname));	

	// listctrl
	//CRect t_rect;
	//m_listctrl_specialize.GetClientRect(&t_rect);   
	m_listctrl_specialize.SetExtendedStyle((m_listctrl_specialize.GetExtendedStyle())|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);    
	m_listctrl_specialize.InsertColumn(1,_T("name"),LVCFMT_LEFT,LIST1WIDTH); 
	m_listctrl_specialize.InsertColumn(2,_T("keyword"),LVCFMT_LEFT,LIST2WIDTH); 

	// combobox
	CString t_organizationcategory[ORGANIZATIONCATEGORY]=ORGANIZATIONCATEGORYARRAY;
	m_combobox_organization.InsertString(0,_T("all"));
	for(int t_i=0;t_i<ORGANIZATIONCATEGORY;t_i++)
	{		
		m_combobox_organization.InsertString(t_i+1,t_organizationcategory[t_i]);
	}
	m_combobox_organization.SetCurSel(0);

	// edit
	m_lastedit.Empty();

	// sqlite3 db
	m_db=NULL;
	t_cs=getappdir()+SQLITEDBNAME;
	//this->unicode2char(t_cs,t_ch);
	if(sqlite3_open(CW2A(t_cs,CP_UTF8),&m_db)!=SQLITE_OK)
	{
		MessageBox(_T("db open error!"));
	}
	setdbandlistctrl();

	//t_cs.Format(_T("create table log(hostname text,operate text,object text,value text)"),m_hostname);
	//sqlite3_exec(m_db,CW2A(t_cs,CP_UTF8),NULL,NULL,NULL);
	//insertlogtable(m_hostname,m_hostname,m_hostname,m_hostname);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void Cspecialize_queryDlg::setdbandlistctrl()
{
	CString t_cs;
	char t_ch[BUFFERSIZE]={0};
	
/*
	sqlite3_exec(m_db,"create table specializelist(id integer primary key,name text,category text,keyword text,comment text)",NULL,NULL,NULL);
	for(int t_i=0;t_i<1000;t_i++)
	{
		t_cs.Format(_T("insert into specializelist(id,name,category,keyword,comment) values(%d,'a%d','b%d','c%d','d%d')"),t_i,t_i,t_i,t_i,t_i);
		this->unicode2char(t_cs,t_ch);
		sqlite3_exec(m_db,t_ch,NULL,NULL,NULL);
	}
*/
	int t_nrow,t_ncolumn;
	char **t_dbresult=NULL;
	int t_i=0;
	sqlite3_get_table(m_db,"select * from specializelist",&t_dbresult,&t_nrow,&t_ncolumn,NULL);
	m_db_nrecoder=t_nrow;
	for(t_i=0;t_i<m_db_nrecoder;t_i++)
	{
		m_specializelist_recoder[t_i]=new specializelist_recoder;
		//m_specializelist_recoder[t_i]->id=_ttoi(CA2W(t_dbresult[(t_i+1)*t_ncolumn],CP_UTF8));
		m_specializelist_recoder[t_i]->name=CA2W(t_dbresult[(t_i+1)*t_ncolumn],CP_UTF8);
		m_specializelist_recoder[t_i]->category=CA2W(t_dbresult[(t_i+1)*t_ncolumn+1],CP_UTF8);
		m_specializelist_recoder[t_i]->keyword=CA2W(t_dbresult[(t_i+1)*t_ncolumn+2],CP_UTF8);
		m_specializelist_recoder[t_i]->comment=CA2W(t_dbresult[(t_i+1)*t_ncolumn+3],CP_UTF8);
		m_specializelist_recoder[t_i]->date=CA2W(t_dbresult[(t_i+1)*t_ncolumn+4],CP_UTF8);
	}

	sqlite3_free_table(t_dbresult);

	for(t_i=0;t_i<m_db_nrecoder;t_i++)
	{
		m_listctrl_specialize.InsertItem(t_i,m_specializelist_recoder[t_i]->name);  
		//m_listctrl_specialize.SetItemText(t_i,1,_T("SetItemText"));
		m_listctrl_specialize.SetItemText(t_i,1,m_specializelist_recoder[t_i]->keyword);
		m_listctrl_specialize.SetItemData(t_i,(DWORD_PTR)m_specializelist_recoder[t_i]);
	}
	
	UpdateData(FALSE);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cspecialize_queryDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon=GetSystemMetrics(SM_CXICON);
		int cyIcon=GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x=(rect.Width() - cxIcon + 1) / 2;
		int y=(rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cspecialize_queryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cspecialize_queryDlg::OnCbnSelchangeComboorganization()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString t_cs;
	NextDlgCtrl();

	m_combobox_organization.GetWindowText(t_cs);
	CString t_edit;
	m_edit_keyword.GetWindowText(t_edit);
	if(t_cs==_T("all")||(t_edit.GetLength()==0))
	{
		m_listctrl_specialize.DeleteAllItems();
		setdbandlistctrl();
		if(m_lastedit.GetLength()!=0)
		{
			m_edit_keyword.SetWindowText(_T(""));
		}	
		UpdateData(FALSE);

	}
	if(t_cs!=_T("all"))
	{
		int t_listctrlrows=m_listctrl_specialize.GetItemCount();
		int t_nItemIndex=0,t_i=0;
		for(;t_i<t_listctrlrows;)
		{
			if(t_cs!=((specializelist_recoder*)m_listctrl_specialize.GetItemData(t_nItemIndex))->category)
			{
				m_listctrl_specialize.DeleteItem(t_nItemIndex);
			}
			else
			{
				t_nItemIndex++;
			}
			t_i++;
		}
		m_listctrl_specialize.SetColumnWidth(0,LIST1WIDTH);
		m_listctrl_specialize.SetColumnWidth(1,LIST2WIDTH);
	}

	//	MessageBox(t_cs);
}


void Cspecialize_queryDlg::OnEnChangeEditkeyword()
{
	// TODO:  Èç¹û¸Ã¿Ø¼þÊÇ RICHEDIT ¿Ø¼þ£¬Ëü½«²»
	// ·¢ËÍ´ËÍ¨Öª£¬³ý·ÇÖØÐ´ CDialogEx::OnInitDialog()
	// º¯Êý²¢µ÷ÓÃ CRichEditCtrl().SetEventMask()£¬
	// Í¬Ê±½« ENM_CHANGE ±êÖ¾¡°»ò¡±ÔËËãµ½ÑÚÂëÖÐ¡£

	// TODO:  ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	CString t_edit;

	UpdateData(TRUE);
	m_edit_keyword.GetWindowText(t_edit);
	if(t_edit.Find(m_lastedit)<0)
	{
		m_listctrl_specialize.DeleteAllItems();
		setdbandlistctrl();
		m_combobox_organization.SetCurSel(0);		
	}
	m_lastedit=t_edit;
	int t_listctrlrows=m_listctrl_specialize.GetItemCount();
	CString t_subkeyword[SUBKEYWORD]={_T("")};
	t_edit.TrimLeft();
	t_edit.TrimRight();
	t_subkeyword[0]=t_edit;
	for(int t_j=0;((t_subkeyword[t_j].GetLength()!=0)&&(t_subkeyword[t_j].Find(_T(" "))!=-1)&&(t_j<(SUBKEYWORD-1)));t_j++)
	{
		t_subkeyword[t_j+1]=t_subkeyword[t_j].Right(t_subkeyword[t_j].GetLength()-1-t_subkeyword[t_j].Find(_T(" ")));
		t_subkeyword[t_j+1].TrimLeft();
		t_subkeyword[t_j]=t_subkeyword[t_j].Left(t_subkeyword[t_j].Find(_T(" ")));
	}
	int t_nItemIndex=0;
	for(int t_i=0;t_i<t_listctrlrows;)
	{
		CString t_cs;
		int t_keywordflag=0;
		t_cs=((specializelist_recoder*)m_listctrl_specialize.GetItemData(t_nItemIndex))->name+_T(" ")+((specializelist_recoder*)m_listctrl_specialize.GetItemData(t_nItemIndex))->keyword;
		for(int t_j=0;t_j<SUBKEYWORD;t_j++)
		{
			if(t_subkeyword[t_j].GetLength()==0)
			{
				t_keywordflag=1;
				break;
			}
			else
			{
				if(t_cs.MakeUpper().Find(t_subkeyword[t_j].MakeUpper())<0)
				{
					break;
				}
			}
		}
		if(t_keywordflag==0)
		{
			m_listctrl_specialize.DeleteItem(t_nItemIndex);
		}
		else
		{
			t_nItemIndex++;
		}
		t_i++;
	}
	m_listctrl_specialize.SetColumnWidth(0,LIST1WIDTH);
	m_listctrl_specialize.SetColumnWidth(1,LIST2WIDTH);
}


CString Cspecialize_queryDlg::listctrlgetitemtextfromactiveitem(NMHDR *v_pNMHDR,int v_subitem)
{
	NM_LISTVIEW* t_pNMListView = (NM_LISTVIEW*)v_pNMHDR; 
	CString t_strtemp; 
	t_strtemp.Empty();
	if(t_pNMListView->iItem!=-1) 
	{ 	
		// t_strtemp=m_listctrl_specialize.GetItemText(t_pNMListView->iItem,t_pNMListView->iSubItem);
		t_strtemp=m_listctrl_specialize.GetItemText(t_pNMListView->iItem,v_subitem);
		//AfxMessageBox(t_strtemp); 
	}
	return t_strtemp;
}


void Cspecialize_queryDlg::OnNMRClickListspecialize(NMHDR *v_pNMHDR, LRESULT *v_pResult)
{
	LPNMITEMACTIVATE pNMItemActivate=reinterpret_cast<LPNMITEMACTIVATE>(v_pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	CMenu t_menu; 
	if(t_menu.m_hMenu==NULL)
	{
		POINT t_pt={0}; 
		GetCursorPos(&t_pt);
		t_menu.LoadMenu(IDR_MENU_listctrl);
		t_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,t_pt.x,t_pt.y,this);
	}
	m_listctrlactiveitem=pNMItemActivate->iItem;
	m_listctrlactiveitemtext=listctrlgetitemtextfromactiveitem(v_pNMHDR);
	*v_pResult=0;
}

CString Cspecialize_queryDlg::getappdir()
{
	CString t_apppath;
	GetModuleFileName(NULL,t_apppath.GetBuffer(_MAX_PATH),_MAX_PATH);
	t_apppath.ReleaseBuffer();
	return getdirfrompath(t_apppath);
}

CString Cspecialize_queryDlg::getdirfrompath(CString v_cspath)
{
	return v_cspath.Left(v_cspath.ReverseFind(_T('\\'))+1);
}


void Cspecialize_queryDlg::OnNMDblclkListspecialize(NMHDR *v_pNMHDR, LRESULT *v_pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(v_pNMHDR);
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë

	specializelist_recoder* t_p=(specializelist_recoder*)m_listctrl_specialize.GetItemData(pNMItemActivate->iItem);
	if(pNMItemActivate->iSubItem==0)
	{
		CString t_cs;
		t_cs=getappdir()+t_p->category+_T("\\")+t_p->name;
		//AfxMessageBox(t_cs);
		ShellExecute(this->m_hWnd,_T("open"),t_cs,NULL,NULL,SW_SHOW );
		CString t_keyword;
		UpdateData(TRUE);
		m_edit_keyword.GetWindowTextW(t_keyword);
		insertlogtable(m_hostname,_T("open"),t_p->name,t_keyword);
	}
	else
	{
		//AfxMessageBox(listctrlgetitemtextfromactiveitem(v_pNMHDR,1));
		clistctrlactiveitemcomment t_listctrlactiveitemcomment;
		t_listctrlactiveitemcomment.m_pappdlg=this;
		t_listctrlactiveitemcomment.m_pitemdata=(void*)t_p;
		if(t_listctrlactiveitemcomment.DoModal()==IDOK)
		{
			CString t_cs;
			t_cs.Format(_T("update specializelist set comment='%s',date='%s' where name='%s'"),t_p->comment,getsystemdatetime(1),t_p->name);
			while(1)
			{
				if(sqlite3_exec(m_db,CW2A(t_cs,CP_UTF8),NULL,NULL,NULL)==SQLITE_OK)
				{
					insertlogtable(m_hostname,_T("comment"),t_p->name,t_p->comment);
					break;
				}
				Sleep(10);
			}
		}
	}
	*v_pResult = 0;
}


void Cspecialize_queryDlg::OnListctrlnew()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	// AfxMessageBox(m_listctrlactiveitemtext); 
	clistctrlnewitem t_listctrlnewitem;
	specializelist_recoder* t_p=new specializelist_recoder;
	int t_i=0;
	t_listctrlnewitem.m_pappdlg=this;
	t_listctrlnewitem.m_pitemdata=(void*)t_p;
	if(t_listctrlnewitem.DoModal()==IDOK)
	{
		CString t_css,t_csd;
		CStdioFile t_csfs,t_csfd;
		char t_buff[BUFFERSIZE]={0};
		t_css=t_p->name;
		t_p->name=t_p->name.Right(t_p->name.GetLength()-t_p->name.ReverseFind(_T('\\'))-1);
		for(t_i=0;t_i<m_db_nrecoder;t_i++)
		{
			if(m_specializelist_recoder[t_i]->name==t_p->name)
			{
				MessageBox(_T("error! file existed"));
				delete t_p;
				return;
			}
		}
		t_csd=this->getappdir()+t_p->category+_T("\\")+t_p->name;
		if(t_css==t_csd)
		{
			MessageBox(_T("error!"));
			delete t_p;
			return;
		}
		if((t_csfs.Open(t_css,CFile::modeRead|CFile::typeBinary|CFile::shareDenyNone))&&(t_csfd.Open(t_csd,CFile::modeWrite|CFile::modeCreate|CFile::typeBinary)))
		{
			char* t_ptr=t_buff;
			UINT t_iobytes=0;
			do 
			{				
				t_iobytes=t_csfs.Read(t_buff,BUFFERSIZE);
				if(t_iobytes>0)
				{
					t_csfd.Write(t_ptr,t_iobytes);
				}
			}while(t_iobytes>0);
			t_csfs.Close();
			t_csfd.Close();
			t_i=m_listctrl_specialize.GetItemCount();
			m_listctrl_specialize.InsertItem(t_i,t_p->name);  
			//m_listctrl_specialize.SetItemText(t_i,1,_T("SetItemText"));
			m_listctrl_specialize.SetItemText(t_i,1,t_p->keyword);
			m_listctrl_specialize.SetItemData(t_i,(DWORD_PTR)t_p);
			m_specializelist_recoder[m_db_nrecoder]=t_p;

			CString t_cs;
			t_cs.Format(_T("insert into specializelist(name,category,keyword,comment,date) values('%s','%s','%s','%s','%s')"),t_p->name,t_p->category,t_p->keyword,t_p->comment,getsystemdatetime(1));
			while(1)
			{
				if(sqlite3_exec(m_db,CW2A(t_cs,CP_UTF8),NULL,NULL,NULL)==SQLITE_OK)
				{
					insertlogtable(m_hostname,_T("new"),t_p->name,t_p->category);
					break;
				}
				Sleep(10);
			}
			m_db_nrecoder++;
		}
		else
		{
			MessageBox(_T("error! plz check file"));
		}
	}
	else
	{
		delete t_p;
	}
}


void Cspecialize_queryDlg::OnListctrledit()
{
	// TODO: ÔÚ´ËÌí¼ÓÃüÁî´¦Àí³ÌÐò´úÂë
	// AfxMessageBox(m_listctrlactiveitemtext); 
	specializelist_recoder* t_p=(specializelist_recoder*)m_listctrl_specialize.GetItemData(m_listctrlactiveitem);
	clistctrlactiveitemmodify t_listctrlactiveitemmodify;
	t_listctrlactiveitemmodify.m_pappdlg=this;
	t_listctrlactiveitemmodify.m_pitemdata=(void*)t_p;
	if(t_listctrlactiveitemmodify.DoModal()==IDOK)
	{
		CString t_cs;
		t_cs.Format(_T("update specializelist set keyword='%s',date='%s' where name='%s'"),t_p->keyword,getsystemdatetime(1),t_p->name);
		m_listctrl_specialize.SetItemText(m_listctrlactiveitem,1,t_p->keyword);
		while(1)
		{
			if(sqlite3_exec(m_db,CW2A(t_cs,CP_UTF8),NULL,NULL,NULL)==SQLITE_OK)
			{
				insertlogtable(m_hostname,_T("keyword"),t_p->name,t_p->keyword);
				break;
			}
			Sleep(10);
		}
	}
}


void Cspecialize_queryDlg::OnCancel()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà

	//MessageBox(_T("OnCancel"));
	sqlite3_close(m_db);
	for(int t_i=0;t_i<m_db_nrecoder;t_i++)
	{
		delete m_specializelist_recoder[t_i];
	}

	CDialogEx::OnCancel();
}


int Cspecialize_queryDlg::unicode2char(CString v_cs,char* v_str)
{
	int t_len=0;
	t_len=v_cs.GetLength();
	WideCharToMultiByte(CP_OEMCP,0,(LPCTSTR)v_cs,-1,v_str,t_len,0,false); 
	v_str[t_len]=NULL;
	return t_len;
}


CString Cspecialize_queryDlg::char2unicode(char* v_str,int v_strlen)
{
	CString t_cs;
	t_cs.Empty();
	t_cs=CString(v_str,v_strlen);
	return t_cs;
}


CString  Cspecialize_queryDlg::getsystemdatetime(int v_type)
{
	CString t_cstime;
	SYSTEMTIME	t_sysTime; 
	GetLocalTime(&t_sysTime);
	t_cstime.Empty();
	if(v_type==0)
	{
		t_cstime.Format( _T("%04ld-%02ld-%02ld %02ld:%02ld:%02ld.%03ld"),t_sysTime.wYear,t_sysTime.wMonth,t_sysTime.wDay,t_sysTime.wHour,t_sysTime.wMinute,t_sysTime.wSecond,t_sysTime.wMilliseconds);
	}
	else
	{
		t_cstime.Format( _T("%04ld%02ld%02ld%02ld%02ld%02ld%03ld"),t_sysTime.wYear,t_sysTime.wMonth,t_sysTime.wDay,t_sysTime.wHour,t_sysTime.wMinute,t_sysTime.wSecond,t_sysTime.wMilliseconds);
	}
	return t_cstime;
}


int Cspecialize_queryDlg::insertlogtable(CString v_hostname,CString v_operate,CString v_object,CString v_value)
{
	CString t_cs;
	t_cs.Format(_T("insert into log(hostname,operate,object,value,date) values('%s','%s','%s','%s','%s')"),v_hostname,v_operate,v_object,v_value,getsystemdatetime(1));
	while(1)
	{
		if(sqlite3_exec(m_db,CW2A(t_cs,CP_UTF8),NULL,NULL,NULL)==SQLITE_OK)
		{
			break;
		}
		Sleep(10);
	}
	return 0;
}