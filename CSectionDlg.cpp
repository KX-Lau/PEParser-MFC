// CSectionDlg.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "CSectionDlg.h"
#include "afxdialogex.h"


// CSectionDlg 对话框

IMPLEMENT_DYNAMIC(CSectionDlg, CDialog)

CSectionDlg::CSectionDlg(PVOID pbFile, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SECTION_DIALOG, pParent)
	, m_pbFile(pbFile)
{

}

CSectionDlg::~CSectionDlg()
{
}

void CSectionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctllist);
}


BEGIN_MESSAGE_MAP(CSectionDlg, CDialog)
END_MESSAGE_MAP()


// CSectionDlg 消息处理程序


BOOL CSectionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//添加列表框的网格线
	m_ctllist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);


	//添加列标题
	m_ctllist.InsertColumn(0, "名称", LVCFMT_LEFT, 53);
	m_ctllist.InsertColumn(1, "虚拟大小", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(2, "虚拟偏移", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(3, "RAW 大小", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(4, "RAW 偏移", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(5, "特征值", LVCFMT_LEFT, 70);


	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_pbFile + ((PIMAGE_DOS_HEADER)m_pbFile)->e_lfanew);
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)IMAGE_FIRST_SECTION(pNtHeader);

	/*m_ctllist.InsertItem(0, "");
	CString strTemp = "";
	strTemp.Format("%s", pSectionHeader->Name);
	m_ctllist.SetItemText(0, 0, strTemp);

	CString strTemp1 = "";
	strTemp1.Format("%X", pSectionHeader->VirtualAddress);
	m_ctllist.SetItemText(0, 1, strTemp1);*/

	for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++)
	{
		
		CString strTemp = "";

		m_ctllist.InsertItem(i, "");

		strTemp.Format("%s", pSectionHeader->Name);
		m_ctllist.SetItemText(i, 0, strTemp);

		strTemp.Format("%08X", pSectionHeader->Misc.VirtualSize);
		m_ctllist.SetItemText(i, 1, strTemp);

		strTemp.Format("%08X", pSectionHeader->VirtualAddress);
		m_ctllist.SetItemText(i, 2, strTemp);

		strTemp.Format("%08X", pSectionHeader->SizeOfRawData);
		m_ctllist.SetItemText(i, 3, strTemp);

		strTemp.Format("%08X", pSectionHeader->PointerToRawData);
		m_ctllist.SetItemText(i, 4, strTemp);

		strTemp.Format("%08X", pSectionHeader->Characteristics);
		m_ctllist.SetItemText(i, 5, strTemp);

		pSectionHeader++;
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
