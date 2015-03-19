
// Windows IP SettingDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "Singly Linked List.h"
#include "afxwin.h"


// CWindowsIPSettingDlg dialog
class CWindowsIPSettingDlg : public CDialogEx
{
// Construction
public:
	CWindowsIPSettingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WINDOWSIPSETTING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CImageList m_ImgList;
    CComboBoxEx m_NIList;
    CComboBox m_IPSList;
    HeadNode *list;

    CIPAddressCtrl m_IPAddr;
    CIPAddressCtrl m_IPMask;
    CIPAddressCtrl m_IPGate;
    CIPAddressCtrl m_IPDNS;
    CEdit m_IPDHCP;

    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedChange();
    afx_msg void OnCbnSelchangeNilCombo();
    afx_msg void OnCbnSelchangeIpslCombo();
    bool WriteToFile(const char *, const char *, int);
};
