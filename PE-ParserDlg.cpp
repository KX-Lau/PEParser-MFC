
// PE-ParserDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PE-Parser.h"
#include "PE-ParserDlg.h"
#include "afxdialogex.h"
#include "PE-Parser.h"
#include "CFileHeaderDlg.h"
#include "COptionalDlg.h"
#include "CSectionDlg.h"
#include "CDataDirectoryDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPEParserDlg 对话框



CPEParserDlg::CPEParserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PEPARSER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEParserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPEParserDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPENFILE, &CPEParserDlg::OnBnClickedBtnOpenfile)
	ON_EN_CHANGE(IDC_EDIT_FILEPATH, &CPEParserDlg::OnEnChangeEditFilepath)
	ON_BN_CLICKED(IDC_BTN_FILEHEADER, &CPEParserDlg::OnBnClickedBtnFileheader)
	ON_BN_CLICKED(IDC_BTN_OPTIONAL, &CPEParserDlg::OnBnClickedBtnOptional)
	ON_BN_CLICKED(IDC_BTN_SECTION, &CPEParserDlg::OnBnClickedBtnSection)
	ON_BN_CLICKED(IDC_BTN_DATADIRECTORY, &CPEParserDlg::OnBnClickedBtnDatadirectory)
END_MESSAGE_MAP()


// CPEParserDlg 消息处理程序

BOOL CPEParserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPEParserDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPEParserDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPEParserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HANDLE hFile;
HANDLE hMapping;
PVOID pbFile;
PIMAGE_DOS_HEADER pDosHeader;
PIMAGE_NT_HEADERS pNtHeader;

void CPEParserDlg::OnBnClickedBtnOpenfile()
{
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("dll"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_FILEPATH, strFilePath);
	}

	//获取到文件句柄
	hFile = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//创建一个新的文件映射对象
	hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

	//将文件映射对象映射到内存, 并获取到指向该内存块第一个字节的指针
	pbFile = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);


	if (!bIsPe(pbFile))
	{
		MessageBox("不是一个PE文件！！！");

		if (hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
		}
		if (hMapping != NULL)
		{
			CloseHandle(hMapping);
		}
		if (pbFile != NULL)
		{
			UnmapViewOfFile(pbFile);
		}
		
		SetDlgItemText(IDC_EDIT_FILEPATH, "");

	}

	pDosHeader = (PIMAGE_DOS_HEADER)pbFile;
	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pbFile + pDosHeader->e_lfanew);

	displayDosHeader(pbFile);	

}


void CPEParserDlg::OnEnChangeEditFilepath()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CPEParserDlg::displayDosHeader(PVOID pbFile)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pbFile;
	CString strTemp = "";
	strTemp.Format(_T("%04X"), pDosHeader->e_magic);
	SetDlgItemText(IDC_EDIT2, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_cblp);
	SetDlgItemText(IDC_EDIT3, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_cp);
	SetDlgItemText(IDC_EDIT4, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_crlc);
	SetDlgItemText(IDC_EDIT5, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_cparhdr);
	SetDlgItemText(IDC_EDIT6, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_minalloc);
	SetDlgItemText(IDC_EDIT7, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_maxalloc);
	SetDlgItemText(IDC_EDIT8, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_ss);
	SetDlgItemText(IDC_EDIT9, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_sp);
	SetDlgItemText(IDC_EDIT10, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_csum);
	SetDlgItemText(IDC_EDIT11, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_ip);
	SetDlgItemText(IDC_EDIT12, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_cs);
	SetDlgItemText(IDC_EDIT13, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_lfarlc);
	SetDlgItemText(IDC_EDIT14, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_ovno);
	SetDlgItemText(IDC_EDIT15, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_oemid);
	SetDlgItemText(IDC_EDIT16, strTemp);
	strTemp.Format(_T("%04X"), pDosHeader->e_oeminfo);
	SetDlgItemText(IDC_EDIT17, strTemp);
	strTemp.Format(_T("%08X"), pDosHeader->e_lfanew);
	SetDlgItemText(IDC_EDIT18, strTemp);

};


//RVA--->FOA
DWORD CPEParserDlg::RvaToRaw(PIMAGE_NT_HEADERS pNtHeader, DWORD Rva)
{
	PIMAGE_SECTION_HEADER pSectionHeader = (PIMAGE_SECTION_HEADER)IMAGE_FIRST_SECTION(pNtHeader);

	for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; i++)
	{

		DWORD SectionBeginRva = pSectionHeader[i].VirtualAddress;
		DWORD SectionEndRva = pSectionHeader[i].VirtualAddress + pSectionHeader[i].SizeOfRawData;

		if (Rva >= SectionBeginRva && Rva <= SectionEndRva)
		{
			DWORD Temp = Rva - SectionBeginRva;						//偏移量
			DWORD Raw = Temp + pSectionHeader[i].PointerToRawData;	//偏移量 + 节区在硬盘上的地址
			return Raw;
		}
	}
};


void CPEParserDlg::OnBnClickedBtnFileheader()
{
	if (pNtHeader == NULL)
	{
		MessageBox("还没有打开文件！！！");
	}
	else
	{
		CFileHeaderDlg FileHeaderDlg(pNtHeader);
		FileHeaderDlg.DoModal();
	}
}


void CPEParserDlg::OnBnClickedBtnOptional()
{
	if (pNtHeader == NULL)
	{
		MessageBox("还没有打开文件！！！");
	}
	else
	{
		COptionalDlg OptionalDlg(pNtHeader);
		OptionalDlg.DoModal();
	}
	
}


void CPEParserDlg::OnBnClickedBtnSection()
{
	if (pNtHeader == NULL)
	{
		MessageBox("还没有打开文件！！！");
	}
	else
	{
		CSectionDlg SectionDlg(pbFile);
		SectionDlg.DoModal();
	}
	

}


void CPEParserDlg::OnBnClickedBtnDatadirectory()
{
	if (pNtHeader == NULL)
	{
		MessageBox("还没有打开文件！！！");
	}
	else
	{
		CDataDirectoryDlg DataDirectoryDlg(pbFile);
		DataDirectoryDlg.DoModal();
	}
	
}
