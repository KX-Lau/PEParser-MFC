#pragma once


// CDataDirectoryDlg 对话框

class CDataDirectoryDlg : public CDialog
{
	DECLARE_DYNAMIC(CDataDirectoryDlg)

public:
	CDataDirectoryDlg(PVOID pbFile, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDataDirectoryDlg();

	//PIMAGE_NT_HEADERS m_pNtHeader;
	PVOID m_pbFile;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATADIRECTORY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnReloc();
	afx_msg void OnBnClickedBtnImport();
	afx_msg void OnBnClickedBtnExport();
};
