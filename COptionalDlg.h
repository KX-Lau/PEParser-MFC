#pragma once


// COptionalDlg 对话框

class COptionalDlg : public CDialog
{
	DECLARE_DYNAMIC(COptionalDlg)

public:
	COptionalDlg(PIMAGE_NT_HEADERS pNtHeader, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COptionalDlg();

	PIMAGE_NT_HEADERS m_pNtHeader;


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONAL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
