// COptionalDlg.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "COptionalDlg.h"
#include "afxdialogex.h"


// COptionalDlg 对话框

IMPLEMENT_DYNAMIC(COptionalDlg, CDialog)

COptionalDlg::COptionalDlg(PIMAGE_NT_HEADERS pNtHeader, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OPTIONAL_DIALOG, pParent)
	, m_pNtHeader(pNtHeader)
{

}

COptionalDlg::~COptionalDlg()
{
}

void COptionalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COptionalDlg, CDialog)
END_MESSAGE_MAP()


// COptionalDlg 消息处理程序


BOOL COptionalDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strTemp = "";
	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.Magic);
	SetDlgItemText(IDC_EDIT1, strTemp);

	strTemp.Format(_T("%02X"), m_pNtHeader->OptionalHeader.MajorLinkerVersion);
	SetDlgItemText(IDC_EDIT3, strTemp);

	strTemp.Format(_T("%02X"), m_pNtHeader->OptionalHeader.MinorLinkerVersion);
	SetDlgItemText(IDC_EDIT4, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfCode);
	SetDlgItemText(IDC_EDIT5, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfInitializedData);
	SetDlgItemText(IDC_EDIT6, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfUninitializedData);
	SetDlgItemText(IDC_EDIT7, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.AddressOfEntryPoint);
	SetDlgItemText(IDC_EDIT8, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.BaseOfCode);
	SetDlgItemText(IDC_EDIT9, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.BaseOfData);
	SetDlgItemText(IDC_EDIT10, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.ImageBase);
	SetDlgItemText(IDC_EDIT11, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SectionAlignment);
	SetDlgItemText(IDC_EDIT12, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.FileAlignment);
	SetDlgItemText(IDC_EDIT13, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.MajorOperatingSystemVersion);
	SetDlgItemText(IDC_EDIT14, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.MinorOperatingSystemVersion);
	SetDlgItemText(IDC_EDIT15, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.MajorImageVersion);
	SetDlgItemText(IDC_EDIT16, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.MinorImageVersion);
	SetDlgItemText(IDC_EDIT17, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.MajorSubsystemVersion);
	SetDlgItemText(IDC_EDIT18, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.MinorSubsystemVersion);
	SetDlgItemText(IDC_EDIT19, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.Win32VersionValue);
	SetDlgItemText(IDC_EDIT20, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfImage);
	SetDlgItemText(IDC_EDIT21, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfHeaders);
	SetDlgItemText(IDC_EDIT22, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.CheckSum);
	SetDlgItemText(IDC_EDIT23, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.Subsystem);
	SetDlgItemText(IDC_EDIT24, strTemp);

	strTemp.Format(_T("%04X"), m_pNtHeader->OptionalHeader.DllCharacteristics);
	SetDlgItemText(IDC_EDIT25, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfStackReserve);
	SetDlgItemText(IDC_EDIT26, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfStackCommit);
	SetDlgItemText(IDC_EDIT27, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfHeapReserve);
	SetDlgItemText(IDC_EDIT28, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.SizeOfHeapCommit);
	SetDlgItemText(IDC_EDIT29, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.LoaderFlags);
	SetDlgItemText(IDC_EDIT30, strTemp);

	strTemp.Format(_T("%08X"), m_pNtHeader->OptionalHeader.NumberOfRvaAndSizes);
	SetDlgItemText(IDC_EDIT31, strTemp);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
