#pragma once
#include "afxwin.h"

// clistctrlnewitem 对话框

class clistctrlnewitem : public CDialogEx
{
	DECLARE_DYNAMIC(clistctrlnewitem)

public:
	clistctrlnewitem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~clistctrlnewitem();
	CDialogEx *m_pappdlg;

// 对话框数据
	enum { IDD = IDD_DIALOG_new };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// new location
	CEdit m_new_location;
	// new category
	CComboBox m_new_category;
	// new keyword
	CEdit m_new_keyword;
	void* m_pitemdata;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
