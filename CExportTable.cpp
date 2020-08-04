// CExportTable.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "CExportTable.h"
#include "afxdialogex.h"
#include "PE-ParserDlg.h"


// CExportTable 对话框

IMPLEMENT_DYNAMIC(CExportTable, CDialog)

CExportTable::CExportTable(PVOID pbFile, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EXPORT_DIALOG, pParent)
	,m_pbFile(pbFile)
{

}

CExportTable::~CExportTable()
{
}

void CExportTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPORT_LIST, m_ctllist);
}


BEGIN_MESSAGE_MAP(CExportTable, CDialog)
END_MESSAGE_MAP()


// CExportTable 消息处理程序


BOOL CExportTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	//添加列表框的网格线
	m_ctllist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//添加列标题
	m_ctllist.InsertColumn(0, "导出序号", LVCFMT_LEFT, 60);
	m_ctllist.InsertColumn(1, "RVA", LVCFMT_LEFT, 80);
	m_ctllist.InsertColumn(2, "偏移", LVCFMT_LEFT, 80);
	m_ctllist.InsertColumn(3, "函数名", LVCFMT_LEFT, 100);


	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_pbFile + ((PIMAGE_DOS_HEADER)m_pbFile)->e_lfanew);
	DWORD Export_table_Rva = pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if (Export_table_Rva)
	{
		//定位到导出表, RVA--->FOA
		DWORD Export_table_Raw = CPEParserDlg::RvaToRaw(pNtHeader, Export_table_Rva);

		//在FileBuffer中定位到导出表
		PIMAGE_EXPORT_DIRECTORY pExportDirectory = (PIMAGE_EXPORT_DIRECTORY)((DWORD)m_pbFile + Export_table_Raw);

		/*
		* Name: 指向该导出表文件名的RVA
		* Base: 导出函数的起始序号
		* NumberOfNames: 以函数名字导出的函数个数
		* NumberOfFunctions: 所有导出函数的个数: 最大序号 - 最小序号 + 1
		* AddressOfNames: 导出函数名称表---RVA
		* AddressOfFunctions: 导出函数地址表---RVA
		* AddressOfNameOrdinals: 导出函数序号表---RVA
		*/

		DWORD Export_table_Name = (DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, pExportDirectory->Name);
		DWORD* pNameOfAddress = (DWORD*)((DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, pExportDirectory->AddressOfNames));
		DWORD* pFunctionOfAddress = (DWORD*)((DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, pExportDirectory->AddressOfFunctions));
		WORD* pNameOrdinalOfAddress = (WORD*)((DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, pExportDirectory->AddressOfNameOrdinals));

		CString strTemp = "";
		strTemp.Format("%08X", pExportDirectory->Characteristics);
		SetDlgItemText(IDC_EDIT1, strTemp);

		strTemp.Format("%08X", pExportDirectory->TimeDateStamp);
		SetDlgItemText(IDC_EDIT3, strTemp);

		strTemp.Format("%04X", pExportDirectory->MajorVersion);
		SetDlgItemText(IDC_EDIT4, strTemp);

		strTemp.Format("%04X", pExportDirectory->MinorVersion);
		SetDlgItemText(IDC_EDIT5, strTemp);

		strTemp.Format("%s", Export_table_Name);
		SetDlgItemText(IDC_EDIT6, strTemp);

		strTemp.Format("%08X", pExportDirectory->Base);
		SetDlgItemText(IDC_EDIT7, strTemp);

		strTemp.Format("%08X", pExportDirectory->NumberOfFunctions);
		SetDlgItemText(IDC_EDIT8, strTemp);

		strTemp.Format("%08X", pExportDirectory->NumberOfNames);
		SetDlgItemText(IDC_EDIT9, strTemp);

		strTemp.Format("%08X", pExportDirectory->AddressOfFunctions);
		SetDlgItemText(IDC_EDIT10, strTemp);

		strTemp.Format("%08X", pExportDirectory->AddressOfNames);
		SetDlgItemText(IDC_EDIT12, strTemp);

		strTemp.Format("%08X", pExportDirectory->AddressOfNameOrdinals);
		SetDlgItemText(IDC_EDIT13, strTemp);

		strTemp.Format("%08X", pExportDirectory->Name);
		SetDlgItemText(IDC_EDIT14, strTemp);


		if (pExportDirectory->NumberOfFunctions != 0)
		{

			int NumberOfFunctions = (int)pExportDirectory->NumberOfFunctions;		//导出函数地址表的个数

			//pIsFound记录导出函数是否被遍历到
			int* pIsFound = (int*)malloc(sizeof(int) * NumberOfFunctions);
			int k;
			for (k = 0; k < pExportDirectory->NumberOfFunctions; k++)
			{
				pIsFound[k] = 0;
			}

			for (int i = 0; i < pExportDirectory->NumberOfNames; i++)
			{

				DWORD FunctionAddress = pFunctionOfAddress[pNameOrdinalOfAddress[i]];		//pNameOrdinalOfAddress 导出函数序号表
				DWORD FunName = (DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, pNameOfAddress[i]);		//pNameOfAddress 导出函数名称表
				pIsFound[pNameOrdinalOfAddress[i]] = 1;

				//Base + 序号 ---> 真正的导出序号
				m_ctllist.InsertItem(i, "");
				strTemp.Format("%04X", pExportDirectory->Base + pNameOrdinalOfAddress[i]);
				m_ctllist.SetItemText(i, 0, strTemp);

				//函数地址的RVA
				strTemp.Format("%08X", FunctionAddress);
				m_ctllist.SetItemText(i, 1, strTemp);

				strTemp.Format("%08X", CPEParserDlg::RvaToRaw(pNtHeader, FunctionAddress));
				m_ctllist.SetItemText(i, 2, strTemp);

				strTemp.Format("%10s", FunName);
				m_ctllist.SetItemText(i, 3, strTemp);

			}


			//导出函数地址表和导出函数名称名不一一对应时, 按导出函数序号查找
			if (pExportDirectory->NumberOfFunctions != pExportDirectory->NumberOfNames)
			{

				for (int m = 0; m < pExportDirectory->NumberOfFunctions; m++)
				{
					if (pIsFound[m] != 1)
					{
						m_ctllist.InsertItem(m, "");
						strTemp.Format("%X", pExportDirectory->Base + m);
						m_ctllist.SetItemText(m, 0, strTemp);

						strTemp = "——";
						m_ctllist.SetItemText(m, 1, strTemp);

						strTemp = "——";
						m_ctllist.SetItemText(m, 2, strTemp);

						strTemp = "——";
						m_ctllist.SetItemText(m, 3, strTemp);
					}
				}
			}

			free(pIsFound);

		}
	}
	else
	{
		MessageBox("该PE文件没有导出表！！！");
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



