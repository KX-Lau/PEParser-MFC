#pragma once


// CExportTable 对话框

class CExportTable : public CDialog
{
	DECLARE_DYNAMIC(CExportTable)

public:
	CExportTable(PVOID pbFile, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CExportTable();

	PVOID m_pbFile;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPORT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctllist;
};
