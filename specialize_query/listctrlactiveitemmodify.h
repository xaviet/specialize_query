#pragma once
#include "afxwin.h"

// clistctrlactiveitemmodify 对话框

class clistctrlactiveitemmodify : public CDialogEx
{
	DECLARE_DYNAMIC(clistctrlactiveitemmodify)

public:
	clistctrlactiveitemmodify(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~clistctrlactiveitemmodify();
	CDialogEx *m_pappdlg;

// 对话框数据
	enum { IDD = IDD_DIALOG_modify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// modify name
	CEdit m_modify_name;
	void* m_pitemdata;
	// modify keyword
	CEdit m_modify_keyword;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
