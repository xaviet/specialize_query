#pragma once
#include "afxwin.h"

// clistctrlactiveitemmodify �Ի���

class clistctrlactiveitemmodify : public CDialogEx
{
	DECLARE_DYNAMIC(clistctrlactiveitemmodify)

public:
	clistctrlactiveitemmodify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~clistctrlactiveitemmodify();
	CDialogEx *m_pappdlg;

// �Ի�������
	enum { IDD = IDD_DIALOG_modify };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
