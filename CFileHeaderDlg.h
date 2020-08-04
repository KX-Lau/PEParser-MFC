#pragma once


// CFileHeaderDlg 对话框

class CFileHeaderDlg : public CDialog
{
	DECLARE_DYNAMIC(CFileHeaderDlg)

public:
	CFileHeaderDlg(PIMAGE_NT_HEADERS pNtHeader, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CFileHeaderDlg();


// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILEHEADER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	PIMAGE_NT_HEADERS m_pNtHeader;

	virtual BOOL OnInitDialog();


	CString m_machine;
	CString m_numberOfSections;
	CString m_time;
	CString m_pCOFF;
	CString m_sizeCOFF;
	CString m_character;
	CString m_sizeOptional;
};
