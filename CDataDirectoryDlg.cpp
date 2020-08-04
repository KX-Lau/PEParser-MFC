// CDataDirectoryDlg.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "CDataDirectoryDlg.h"
#include "afxdialogex.h"
#include "CImportTable.h"
#include "CExportTable.h"
#include "CRelocTable.h"

// CDataDirectoryDlg 对话框

IMPLEMENT_DYNAMIC(CDataDirectoryDlg, CDialog)

CDataDirectoryDlg::CDataDirectoryDlg(PVOID pbFile, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DATADIRECTORY_DIALOG, pParent)
	,m_pbFile(pbFile)
{

}

CDataDirectoryDlg::~CDataDirectoryDlg()
{
}

void CDataDirectoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDataDirectoryDlg, CDialog)
	
	ON_BN_CLICKED(IDC_BTN_RELOC, &CDataDirectoryDlg::OnBnClickedBtnReloc)
	ON_BN_CLICKED(IDC_BTN_IMPORT, &CDataDirectoryDlg::OnBnClickedBtnImport)
	ON_BN_CLICKED(IDC_BTN_EXPORT, &CDataDirectoryDlg::OnBnClickedBtnExport)
END_MESSAGE_MAP()


// CDataDirectoryDlg 消息处理程序




BOOL CDataDirectoryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_pbFile + ((PIMAGE_DOS_HEADER)m_pbFile)->e_lfanew);

	CString strTemp = "";
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[0].VirtualAddress);
	SetDlgItemText(IDC_EDIT1, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[0].Size);
	SetDlgItemText(IDC_EDIT4, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[1].VirtualAddress);
	SetDlgItemText(IDC_EDIT5, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[1].Size);
	SetDlgItemText(IDC_EDIT6, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[2].VirtualAddress);
	SetDlgItemText(IDC_EDIT7, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[2].Size);
	SetDlgItemText(IDC_EDIT8, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[3].VirtualAddress);
	SetDlgItemText(IDC_EDIT23, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[3].Size);
	SetDlgItemText(IDC_EDIT24, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[4].VirtualAddress);
	SetDlgItemText(IDC_EDIT25, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[4].Size);
	SetDlgItemText(IDC_EDIT26, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[5].VirtualAddress);
	SetDlgItemText(IDC_EDIT27, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[5].Size);
	SetDlgItemText(IDC_EDIT28, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[6].VirtualAddress);
	SetDlgItemText(IDC_EDIT29, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[6].Size);
	SetDlgItemText(IDC_EDIT30, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[7].VirtualAddress);
	SetDlgItemText(IDC_EDIT31, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[7].Size);
	SetDlgItemText(IDC_EDIT32, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[8].VirtualAddress);
	SetDlgItemText(IDC_EDIT33, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[8].Size);
	SetDlgItemText(IDC_EDIT34, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[9].VirtualAddress);
	SetDlgItemText(IDC_EDIT35, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[9].Size);
	SetDlgItemText(IDC_EDIT36, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[10].VirtualAddress);
	SetDlgItemText(IDC_EDIT37, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[10].Size);
	SetDlgItemText(IDC_EDIT38, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[11].VirtualAddress);
	SetDlgItemText(IDC_EDIT39, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[11].Size);
	SetDlgItemText(IDC_EDIT40, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[12].VirtualAddress);
	SetDlgItemText(IDC_EDIT41, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[12].Size);
	SetDlgItemText(IDC_EDIT42, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[13].VirtualAddress);
	SetDlgItemText(IDC_EDIT43, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[13].Size);
	SetDlgItemText(IDC_EDIT44, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[14].VirtualAddress);
	SetDlgItemText(IDC_EDIT45, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[14].Size);
	SetDlgItemText(IDC_EDIT46, strTemp);

	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[15].VirtualAddress);
	SetDlgItemText(IDC_EDIT47, strTemp);
	strTemp.Format(_T("%04X"), pNtHeader->OptionalHeader.DataDirectory[15].Size);
	SetDlgItemText(IDC_EDIT48, strTemp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDataDirectoryDlg::OnBnClickedBtnReloc()
{
	// TODO: 在此添加控件通知处理程序代码
	CRelocTable RelocTable(m_pbFile);
	RelocTable.DoModal();
}


void CDataDirectoryDlg::OnBnClickedBtnImport()
{
	// TODO: 在此添加控件通知处理程序代码
	CImportTable ImportTable(m_pbFile);
	ImportTable.DoModal();
}


void CDataDirectoryDlg::OnBnClickedBtnExport()
{
	CExportTable ExportTable(m_pbFile);
	ExportTable.DoModal();
}
