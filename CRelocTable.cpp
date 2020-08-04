// CRelocTable.cpp: 实现文件
//

#include "pch.h"
#include "PE-Parser.h"
#include "CRelocTable.h"
#include "afxdialogex.h"
#include "PE-ParserDlg.h"


// CRelocTable 对话框

IMPLEMENT_DYNAMIC(CRelocTable, CDialog)

CRelocTable::CRelocTable(PVOID pbFile, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RELOC_DIALOG, pParent)
	,m_pbFile(pbFile)
{

}

CRelocTable::~CRelocTable()
{
}

void CRelocTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELOC_LIST, m_ctllist);
}


BEGIN_MESSAGE_MAP(CRelocTable, CDialog)
END_MESSAGE_MAP()


// CRelocTable 消息处理程序


BOOL CRelocTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ctllist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ctllist.InsertColumn(0, "序号", LVCFMT_LEFT, 60);
	m_ctllist.InsertColumn(1, "RVA", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(2, "偏移", LVCFMT_LEFT, 70);
	m_ctllist.InsertColumn(3, "数据类型", LVCFMT_LEFT, 100);


	/*
	IMAGE_BASE_RELOCATION
	{
		DWORD VirtualAddress
		DWORD SizeOfBlock
	}
	WORD TypeOffset[0]
	WORD TypeOffset[1]
	...
	WORD TypeOffset[Count]

	*/

	PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)m_pbFile + ((PIMAGE_DOS_HEADER)m_pbFile)->e_lfanew);

	typedef struct  _OFFSET_TYPE
	{
		WORD offset : 12;
		WORD type : 4;
	}OFFSET_TYPE, * POFFSET_TYPE;


	//定位到重定位表， RVA--->FOA
	DWORD Reloc_Rva = pNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;

	if (Reloc_Rva)
	{
		//在FileBuffer中定位到重定位表
		PIMAGE_BASE_RELOCATION pReloc = (PIMAGE_BASE_RELOCATION)((DWORD)m_pbFile + CPEParserDlg::RvaToRaw(pNtHeader, Reloc_Rva));

		//从头循环遍历每个块
		while (pReloc->SizeOfBlock)
		{
			
			//某块中所有重定位项的个数
			DWORD Count = (pReloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);

			//重定位项:可以当做一个数组，宽度为2字节，每一个重定位项分为两个部分：高4位(重定位数据的类型)和低12位(重定位数据相对于VirtualAddress的偏移)
			//下移8个字节, 定位到每一块中的重定位项开端
			POFFSET_TYPE pOffset = (POFFSET_TYPE)(pReloc + 1);

			CString strTemp = "";

			//循环遍历每个重定位项
			for (int i = 0; i < Count; ++i)
			{
				//重定位数据
				if (pOffset[i].type == IMAGE_REL_BASED_HIGHLOW)
				{
					//重定位数据的RVA
					DWORD Reloc_Data_Rva = pReloc->VirtualAddress + pOffset[i].offset;
					DWORD Reloc_Data_Foa = (DWORD)(CPEParserDlg::RvaToRaw(pNtHeader, Reloc_Data_Rva));

					m_ctllist.InsertItem(i, "");
					strTemp.Format("%d", i+1);
					m_ctllist.SetItemText(i, 0, strTemp);

					strTemp.Format("%08X", Reloc_Data_Rva);
					m_ctllist.SetItemText(i, 1, strTemp);

					strTemp.Format("%08X", Reloc_Data_Foa);
					m_ctllist.SetItemText(i, 2, strTemp);

					strTemp.Format("HIGHLOW (%d)", pOffset[i].type);
					m_ctllist.SetItemText(i, 3, strTemp);
					
				}
			}

			//指向下一个重定向块
			pReloc = (PIMAGE_BASE_RELOCATION)((DWORD)pReloc + pReloc->SizeOfBlock);
		}
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
