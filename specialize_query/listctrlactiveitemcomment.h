#pragma once
#include "afxwin.h"


// clistctrlactiveitemcomment 对话框

class clistctrlactiveitemcomment : public CDialogEx
{
	DECLARE_DYNAMIC(clistctrlactiveitemcomment)

public:
	clistctrlactiveitemcomment(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~clistctrlactiveitemcomment();
	CDialogEx *m_pappdlg;

// 对话框数据
	enum { IDD = IDD_DIALOG_listctrlitemcomment };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// comment
	CEdit m_comment;
	void* m_pitemdata;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
