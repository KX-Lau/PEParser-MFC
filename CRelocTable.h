#pragma once


// CRelocTable 对话框

class CRelocTable : public CDialog
{
	DECLARE_DYNAMIC(CRelocTable)

public:
	CRelocTable(PVOID pbFile, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRelocTable();
	PVOID m_pbFile;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RELOC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_ctllist;
};
