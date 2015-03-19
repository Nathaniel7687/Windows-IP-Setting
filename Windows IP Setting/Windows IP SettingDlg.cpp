#pragma warning(disable: 4996)
// Windows IP SettingDlg.cpp : implementation file
//

#include "afxdialogex.h"
#include "Windows IP Setting.h"
#include "Windows IP SettingDlg.h"
#include "IP_ADAPTER_INFO.h"
#include <MSXML2.H>
#pragma comment (lib, "msxml2.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWindowsIPSettingDlg dialog
CWindowsIPSettingDlg::CWindowsIPSettingDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CWindowsIPSettingDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWindowsIPSettingDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_NIL_COMBO, m_NIList);
    DDX_Control(pDX, IDC_IPSL_COMBO, m_IPSList);
    DDX_Control(pDX, IDC_IPADDR, m_IPAddr);
    DDX_Control(pDX, IDC_IPMASK, m_IPMask);
    DDX_Control(pDX, IDC_IPGATE, m_IPGate);
    DDX_Control(pDX, IDC_IPDNS, m_IPDNS);
    DDX_Control(pDX, IDC_IPDHCP, m_IPDHCP);
}

BEGIN_MESSAGE_MAP(CWindowsIPSettingDlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDCANCEL, &CWindowsIPSettingDlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_CHANGE, &CWindowsIPSettingDlg::OnBnClickedChange)
    ON_CBN_SELCHANGE(IDC_NIL_COMBO, &CWindowsIPSettingDlg::OnCbnSelchangeNilCombo)
    ON_CBN_SELCHANGE(IDC_IPSL_COMBO, &CWindowsIPSettingDlg::OnCbnSelchangeIpslCombo)
END_MESSAGE_MAP()


// CWindowsIPSettingDlg message handlers

BOOL CWindowsIPSettingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    
    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    // TODO: Add extra initialization here
    list = createHeadNode();
	
    getAdapterInfo(list);
    
    ListNode *prev = list->head;

    // (시작)어댑터 리스트 생성
    CBitmap list_bmp;
    list_bmp.LoadBitmapW(IDB_LISTBMP);
    
    m_ImgList.Create(16, 16, ILC_COLOR8, 3, 3);
    m_ImgList.Add(&list_bmp, RGB(255, 0, 0));
    
    m_NIList.SetImageList(&m_ImgList);

    COMBOBOXEXITEM cbi;
    cbi.mask = CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_TEXT;

	//CString tmp1;
	//	
	//tmp1.Format(L"%d", prev->data.adapName.GetLength());
	//m_IPDHCP.SetWindowTextW(tmp1);

    for(int i = 0; prev != NULL; i++) {
        cbi.iItem = i;

        if(prev->data.type == 1) {
            cbi.iImage = 1;
            cbi.iSelectedImage = 1;
        }
        else if(prev->data.type == 2) {
            cbi.iImage = 2;
            cbi.iSelectedImage = 2;
        }
        else {
            cbi.iImage = 0;
            cbi.iSelectedImage = 0;
        }
        
		cbi.pszText = (LPTSTR)(LPCTSTR)prev->data.adapName;
		cbi.cchTextMax = prev->data.adapName.GetLength();
        m_NIList.InsertItem(&cbi);
		
        prev = prev->link;
    }
    // (종료)어댑터 리스트 생성

    //// (시작) XML 사용
    //CoInitialize(NULL);
    //IXMLDOMDocument* pXml;
    //CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER, IID_IXMLDOMDocument2, (void**)&pXml);
    //variant_t fileName(szXMLFilePathName);
    //VARIANT_BOOL bLoad;
    //pXml->load(fileName, &bLoad)

    //m_IPSList.AddString(_T("Automatic IP Setting"));


    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWindowsIPSettingDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWindowsIPSettingDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CWindowsIPSettingDlg::OnBnClickedCancel()
{
    // TODO: Add your control notification handler code here

    CDialogEx::OnCancel();
}


void CWindowsIPSettingDlg::OnBnClickedChange()
{
    // TODO: Add your control notification handler code here

}


void CWindowsIPSettingDlg::OnCbnSelchangeNilCombo()
{
    Node *prev = list->head;

    for(int i = 0; i < m_NIList.GetCurSel(); i++) {
        prev = prev->link;
    }

	m_IPAddr.SetWindowTextW((LPCTSTR)(CString)prev->data.ipAddress);
    m_IPMask.SetWindowTextW((LPCTSTR)(CString)prev->data.ipMask);
    m_IPGate.SetWindowTextW((LPCTSTR)(CString)prev->data.ipGateway);
    //m_IPDNS.SetWindowTextW((LPCTSTR)(CString)prev->data.ipDNS);

    //if(prev->data.dhcp == 0)
    //    m_IPDHCP.SetWindowTextW(_T("No"));
    //else if(prev->data.dhcp == 1)
    //    m_IPDHCP.SetWindowTextW(_T("Yes"));
}


void CWindowsIPSettingDlg::OnCbnSelchangeIpslCombo()
{
    // TODO: Add your control notification handler code here


}

bool CWindowsIPSettingDlg::WriteToFile(const char* filename, const char* buffer, int len)
{
  FILE* r = fopen(filename, "wb");
  if (NULL == r)
    return false;
  size_t fileSize = fwrite(buffer, 1, len, r);
  fclose(r);

  return true;
}
