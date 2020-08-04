// CFileHeaderDlg.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "CFileHeaderDlg.h"
#include "afxdialogex.h"


// CFileHeaderDlg 对话框

IMPLEMENT_DYNAMIC(CFileHeaderDlg, CDialog)

CFileHeaderDlg::CFileHeaderDlg(PIMAGE_NT_HEADERS pNtHeader, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FILEHEADER_DIALOG, pParent)
	, m_machine(_T(""))	
	, m_numberOfSections(_T(""))
	, m_time(_T(""))
	, m_pCOFF(_T(""))
	, m_sizeCOFF(_T(""))
	, m_character(_T(""))
	, m_pNtHeader(pNtHeader)
	, m_sizeOptional(_T(""))
{
}

CFileHeaderDlg::~CFileHeaderDlg()
{
}

void CFileHeaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT100, m_machine);
	DDX_Text(pDX, IDC_EDIT2, m_numberOfSections);
	DDX_Text(pDX, IDC_EDIT3, m_time);
	DDX_Text(pDX, IDC_EDIT4, m_pCOFF);
	DDX_Text(pDX, IDC_EDIT5, m_sizeCOFF);
	DDX_Text(pDX, IDC_EDIT7, m_character);
	DDX_Text(pDX, IDC_EDIT6, m_sizeOptional);
}


BEGIN_MESSAGE_MAP(CFileHeaderDlg, CDialog)

END_MESSAGE_MAP()


// CFileHeaderDlg 消息处理程序




BOOL CFileHeaderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化	
	CString strTemp = "";
	strTemp.Format(_T("%04X"), m_pNtHeader->FileHeader.Machine);
	m_machine = strTemp;

	strTemp.Format(_T("%04X"), m_pNtHeader->FileHeader.NumberOfSections);
	m_numberOfSections = strTemp;

	strTemp.Format(_T("%08X"), m_pNtHeader->FileHeader.TimeDateStamp);
	m_time = strTemp;

	strTemp.Format(_T("%08X"), m_pNtHeader->FileHeader.PointerToSymbolTable);
	m_pCOFF = strTemp;

	strTemp.Format(_T("%08X"), m_pNtHeader->FileHeader.NumberOfSymbols);
	m_sizeCOFF = strTemp;

	strTemp.Format(_T("%04X"), m_pNtHeader->FileHeader.SizeOfOptionalHeader);
	m_sizeOptional = strTemp;

	strTemp.Format(_T("%04X"), m_pNtHeader->FileHeader.Characteristics);
	m_character = strTemp;

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




