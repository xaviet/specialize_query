// listctrlnewitem.cpp : 实现文件
//

#include "stdafx.h"
#include "specialize_query.h"
#include "listctrlnewitem.h"
#include "afxdialogex.h"
#include "config.h"

// clistctrlnewitem 对话框

IMPLEMENT_DYNAMIC(clistctrlnewitem, CDialogEx)

clistctrlnewitem::clistctrlnewitem(CWnd* pParent /*=NULL*/)
	: CDialogEx(clistctrlnewitem::IDD, pParent)
{

}

clistctrlnewitem::~clistctrlnewitem()
{
}

void clistctrlnewitem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_new_path, m_new_location);
	DDX_Control(pDX, IDC_COMBO_new_category, m_new_category);
	DDX_Control(pDX, IDC_EDIT_new_keyword, m_new_keyword);
}


BEGIN_MESSAGE_MAP(clistctrlnewitem, CDialogEx)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// clistctrlnewitem 消息处理程序


BOOL clistctrlnewitem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	CString t_organizationcategory[ORGANIZATIONCATEGORY]=ORGANIZATIONCATEGORYARRAY;
	for(int t_i=0;t_i<ORGANIZATIONCATEGORY;t_i++)
	{
		m_new_category.InsertString(t_i,t_organizationcategory[t_i]);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void clistctrlnewitem::OnOK()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	UpdateData(TRUE);
	m_new_location.GetWindowText(((specializelist_recoder*)m_pitemdata)->name);
	m_new_category.GetWindowText(((specializelist_recoder*)m_pitemdata)->category);
	m_new_keyword.GetWindowText(((specializelist_recoder*)m_pitemdata)->keyword);

	CDialogEx::OnOK();
}


void clistctrlnewitem::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	CString t_cs;
	int t_DropCount=DragQueryFile(hDropInfo,-1,NULL,0);
	if(t_DropCount==1)
	{    
		DragQueryFile(hDropInfo,0,t_cs.GetBuffer(_MAX_PATH),_MAX_PATH);
		t_cs.ReleaseBuffer();
		if(PathIsDirectory(t_cs)||PathIsRoot(t_cs)) 
		{
			MessageBox(_T("error!"));
		}
		else
		{
			m_new_location.SetWindowText(t_cs);
			UpdateData(FALSE);
		}
	}
	CDialogEx::OnDropFiles(hDropInfo);
}
