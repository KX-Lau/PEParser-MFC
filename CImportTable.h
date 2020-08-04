#pragma once


// CImportTable 对话框

class CImportTable : public CDialog
{
	DECLARE_DYNAMIC(CImportTable)

public:
	CImportTable(PVOID pbFile, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CImportTable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMPORT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ctllist;
	PVOID m_pbFile;
	virtual BOOL OnInitDialog();
};
