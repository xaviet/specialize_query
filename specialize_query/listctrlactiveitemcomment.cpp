// listctrlactiveitemcomment.cpp : 实现文件
//

#include "stdafx.h"
#include "specialize_query.h"
#include "listctrlactiveitemcomment.h"
#include "afxdialogex.h"
#include "config.h"

// clistctrlactiveitemcomment 对话框

IMPLEMENT_DYNAMIC(clistctrlactiveitemcomment, CDialogEx)

clistctrlactiveitemcomment::clistctrlactiveitemcomment(CWnd* pParent /*=NULL*/)
	: CDialogEx(clistctrlactiveitemcomment::IDD, pParent)
{

}

clistctrlactiveitemcomment::~clistctrlactiveitemcomment()
{
}

void clistctrlactiveitemcomment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_listctrlitemcomment, m_comment);
}


BEGIN_MESSAGE_MAP(clistctrlactiveitemcomment, CDialogEx)
END_MESSAGE_MAP()


// clistctrlactiveitemcomment 消息处理程序


BOOL clistctrlactiveitemcomment::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ÔÚ´ËÌí¼Ó¶îÍâµÄ³õÊ¼»¯

	m_comment.SetWindowText(((specializelist_recoder*)m_pitemdata)->comment);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// Òì³£: OCX ÊôÐÔÒ³Ó¦·µ»Ø FALSE
}


void clistctrlactiveitemcomment::OnOK()
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	
	UpdateData(TRUE);
	m_comment.GetWindowText(((specializelist_recoder*)m_pitemdata)->comment);

	CDialogEx::OnOK();
}
