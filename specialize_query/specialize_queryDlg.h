
// specialize_queryDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "listctrlactiveitemmodify.h"
#include "listctrlactiveitemcomment.h"
#include "listctrlnewitem.h"
#include "../sqlite3_lib/sqlite3.h"
#include "config.h"

// Cspecialize_queryDlg 对话框
class Cspecialize_queryDlg : public CDialogEx
{
// 构造
public:
	Cspecialize_queryDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SPECIALIZE_QUERY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CString listctrlgetitemtextfromactiveitem(NMHDR *v_pNMHDR,int v_subitem=0);
	CString m_listctrlactiveitemtext;
	int m_listctrlactiveitem;
	sqlite3 *m_db;
	int m_db_nrecoder;
	struct specializelist_recoder *m_specializelist_recoder[BUFFERSIZE];
	CString m_lastedit;
	int insertlogtable(CString v_hostname,CString v_operate,CString v_object,CString v_value);

public:
	// key word
	CEdit m_edit_keyword;
	// organization
	CComboBox m_combobox_organization;
	// specialize
	CListCtrl m_listctrl_specialize;
	afx_msg void OnCbnSelchangeComboorganization();
	afx_msg void OnEnChangeEditkeyword();
	afx_msg void OnNMRClickListspecialize(NMHDR *v_pNMHDR, LRESULT *v_pResult);
	afx_msg void OnNMDblclkListspecialize(NMHDR *v_pNMHDR, LRESULT *v_pResult);
	afx_msg void OnListctrlnew();
	afx_msg void OnListctrledit();
	CString getappdir();
	CString getdirfrompath(CString v_cspath);
	virtual void OnCancel();
	int unicode2char(CString v_cs,char* v_str);
	CString char2unicode(char* v_str,int v_strlen);
	CString m_hostname;
	void setdbandlistctrl();
	CString getsystemdatetime(int v_type=0);
};
