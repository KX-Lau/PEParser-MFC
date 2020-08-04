
// PE-ParserDlg.h: 头文件
//

#pragma once


// CPEParserDlg 对话框
class CPEParserDlg : public CDialogEx
{
// 构造
public:
	CPEParserDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEPARSER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnEnChangeEditFilepath();

	void displayDosHeader(PVOID pbFile);
	

	static DWORD RvaToRaw(PIMAGE_NT_HEADERS pNtHeader, DWORD Rva);

	afx_msg void OnBnClickedBtnFileheader();
	afx_msg void OnBnClickedBtnOptional();
	afx_msg void OnBnClickedBtnSection();
	afx_msg void OnBnClickedBtnDatadirectory();
};
