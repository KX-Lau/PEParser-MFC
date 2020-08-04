// CImportTable.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "CImportTable.h"
#include "afxdialogex.h"
#include "PE-ParserDlg.h"


// CImportTable 对话框

IMPLEMENT_DYNAMIC(CImportTable, CDialog)

CImportTable::CImportTable(PVOID pbFile, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_IMPORT_DIALOG, pParent)
	,m_pbFile(pbFile)
{

}

CImportTable::~CImportTable()
{
}

void CImportTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMPORT_LIST, m_ctllist);
}


BEGIN_MESSAGE_MAP(CImportTable, CDialog)
END_MESSAGE_MAP()


// CImportTable 消息处理程序


BOOL CImportTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	//添加列表框的网格线
	m_ctllist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//添加列标题
	m_ctllist.InsertColumn(0, "DLL名称", LVCFMT_LEFT, 60);
	m_ctllist.InsertColumn(1, "原始 First Thunk", LVCFMT_LEFT, 100);
	m_ctllist.InsertColumn(2, "名称", LVCFMT_LEFT, 80);
	m_ctllist.InsertColumn(3, "First Thunk", LVCFMT_LEFT, 80);

	m_ctllist.InsertColumn(4, "API名称", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(5, "Thunk RVA", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(6, "Thunk 偏移", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(7, "Thunk 值", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(8, "提示", LVCFMT_LEFT, 66);

	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_pbFile + ((PIMAGE_DOS_HEADER)m_pbFile)->e_lfanew);

	//定位到导入表的虚拟地址, RVA--->FOA
	DWORD Import_table_Raw = CPEParserDlg::RvaToRaw(pNtHeader, (DWORD)pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	//在FileBuffer中定位到导入表
	PIMAGE_IMPORT_DESCRIPTOR pImportDirectory = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)m_pbFile + Import_table_Raw);

	CString strTemp = "";

	//循环打印
	while (1)
	{
		//遍历到结尾跳出循环
		if (pImportDirectory->OriginalFirstThunk == 0 && pImportDirectory->TimeDateStamp == 0 && pImportDirectory->ForwarderChain == 0 && pImportDirectory->Name == 0 && pImportDirectory->FirstThunk == 0)
		{
			break;
		}

		//导入的DLL文件名
		DWORD Import_table_Name = (DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, pImportDirectory->Name);

		//导入名称表INT, RVA
		DWORD INT_RVA = pImportDirectory->OriginalFirstThunk;
		
		DWORD Import_table_OriginalFirstThunk = (DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, INT_RVA);
		
		DWORD* pTrunkData = (DWORD*)Import_table_OriginalFirstThunk;

		//导入地址表IAT
		DWORD Import_table_FirstThunk = pImportDirectory->FirstThunk;
				
		int n = 0;

		//INT以0为结束
		while (pTrunkData[n] != 0)
		{
			DWORD TrunkData = pTrunkData[n];


			/*
			*IMAGE_THUNK_DATA的最高位为0时，以函数名方式导入，是一个RVA，指向IMAGE_IMPORT_BY_NAME
			*IMAGE_THUNK_DATA的最高位为1时，以序号导入，低31位被看作一个函数序号
			*/

			//以函数名导入
			if (TrunkData < IMAGE_ORDINAL_FLAG32)
			{

				PIMAGE_IMPORT_BY_NAME pImportByName = (PIMAGE_IMPORT_BY_NAME)((DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, TrunkData));		
				
				m_ctllist.InsertItem(n, "");
				strTemp.Format("%s", Import_table_Name);
				m_ctllist.SetItemText(n, 0, strTemp);

				strTemp.Format("%08X", pImportDirectory->OriginalFirstThunk);
				m_ctllist.SetItemText(n, 1, strTemp);

				strTemp.Format("%08X", pImportDirectory->Name);
				m_ctllist.SetItemText(n, 2, strTemp);

				strTemp.Format("%08X", Import_table_FirstThunk);
				m_ctllist.SetItemText(n, 3, strTemp);

				strTemp.Format("%s", pImportByName->Name);
				m_ctllist.SetItemText(n, 4, strTemp);

				strTemp.Format("%08X", INT_RVA);
				m_ctllist.SetItemText(n, 5, strTemp);    

				strTemp.Format("%08X", CPEParserDlg::RvaToRaw(pNtHeader, INT_RVA));
				m_ctllist.SetItemText(n, 6, strTemp);

				strTemp.Format("%08X", TrunkData);
				m_ctllist.SetItemText(n, 7, strTemp);

				strTemp.Format("%04X", pImportByName->Hint);
				m_ctllist.SetItemText(n, 8, strTemp);

			}

			//以序号导入
			else
			{
				//函数序号--->低31位
				DWORD funum = (DWORD)(TrunkData - IMAGE_ORDINAL_FLAG32);	

				m_ctllist.InsertItem(n, "");
				strTemp.Format("%s", Import_table_Name);
				m_ctllist.SetItemText(n, 0, strTemp);

				strTemp.Format("%08X", pImportDirectory->OriginalFirstThunk);
				m_ctllist.SetItemText(n, 1, strTemp);

				strTemp.Format("%08X", pImportDirectory->Name);
				m_ctllist.SetItemText(n, 2, strTemp);

				strTemp.Format("%08X", Import_table_FirstThunk);
				m_ctllist.SetItemText(n, 3, strTemp);

				strTemp.Format("%16X", funum);
				m_ctllist.SetItemText(n, 4, strTemp);

				strTemp.Format("%08X", INT_RVA);
				m_ctllist.SetItemText(n, 5, strTemp);

				strTemp.Format("%08X", CPEParserDlg::RvaToRaw(pNtHeader, INT_RVA));
				m_ctllist.SetItemText(n, 6, strTemp);

				strTemp.Format("%08X", TrunkData);
				m_ctllist.SetItemText(n, 7, strTemp);

				strTemp = "——";
				m_ctllist.SetItemText(n, 8, strTemp);
			}
			n++;

			INT_RVA = INT_RVA + sizeof(INT_RVA);
		}

		//下一个导入表
		pImportDirectory++;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
