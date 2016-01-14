// listctrlactiveitemmodify.cpp : 实现文件
//

#include "stdafx.h"
#include "specialize_query.h"
#include "listctrlactiveitemmodify.h"
#include "afxdialogex.h"
#include "config.h"

// clistctrlactiveitemmodify 对话框

IMPLEMENT_DYNAMIC(clistctrlactiveitemmodify, CDialogEx)

clistctrlactiveitemmodify::clistctrlactiveitemmodify(CWnd* pParent /*=NULL*/)
	: CDialogEx(clistctrlactiveitemmodify::IDD, pParent)
{

}

clistctrlactiveitemmodify::~clistctrlactiveitemmodify()
{
}

void clistctrlactiveitemmodify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_modify_name, m_modify_name);
	DDX_Control(pDX, IDC_EDIT_modify_keyword, m_modify_keyword);
}


BEGIN_MESSAGE_MAP(clistctrlactiveitemmodify, CDialogEx)
END_MESSAGE_MAP()


// clistctrlactiveitemmodify 消息处理程序


BOOL clistctrlactiveitemmodify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯
	m_modify_name.SetWindowText(((specializelist_recoder*)m_pitemdata)->name);
	m_modify_keyword.SetWindowText(((specializelist_recoder*)m_pitemdata)->keyword);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void clistctrlactiveitemmodify::OnOK()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	UpdateData(TRUE);
	m_modify_keyword.GetWindowText(((specializelist_recoder*)m_pitemdata)->keyword);
	CDialogEx::OnOK();
}
