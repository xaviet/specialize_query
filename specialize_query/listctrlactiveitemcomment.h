#pragma once
#include "afxwin.h"


// clistctrlactiveitemcomment �Ի���

class clistctrlactiveitemcomment : public CDialogEx
{
	DECLARE_DYNAMIC(clistctrlactiveitemcomment)

public:
	clistctrlactiveitemcomment(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~clistctrlactiveitemcomment();
	CDialogEx *m_pappdlg;

// �Ի�������
	enum { IDD = IDD_DIALOG_listctrlitemcomment };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// comment
	CEdit m_comment;
	void* m_pitemdata;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
