#pragma once


// CSectionDlg 对话框

class CSectionDlg : public CDialog
{
	DECLARE_DYNAMIC(CSectionDlg)

public:
	CSectionDlg(PVOID pbFile, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSectionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECTION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctllist;
	//PIMAGE_NT_HEADERS m_pNtHeader;
	PVOID m_pbFile;

	virtual BOOL OnInitDialog();
};
