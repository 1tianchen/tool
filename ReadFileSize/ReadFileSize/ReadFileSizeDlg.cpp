
// ReadFileSizeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ReadFileSize.h"
#include "ReadFileSizeDlg.h"
#include "afxdialogex.h"
#include <string>
//文件
#include <corecrt_io.h>
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma warning(disable : 4996)
// CReadFileSizeDlg 对话框



CReadFileSizeDlg::CReadFileSizeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_READFILESIZE_DIALOG, pParent)
	, cppfileSum(_T(""))
	, cppfilelien(_T(""))
	, cppfilesize(_T(""))

	, otherfilesum(_T(""))
	, otherfileline(_T(""))
	, otherfilesize(_T(""))

	, hfilesum(_T(""))
	, hfileline(_T(""))
	, hfilesize(_T(""))

	, AllfileSum(_T(""))
	, Allfilelien(_T(""))
	, AllfileSize(_T(""))
	, FileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReadFileSizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT9, cppfileSum);
	DDX_Text(pDX, IDC_EDIT10, cppfilelien);
	DDX_Text(pDX, IDC_EDIT11, cppfilesize);

	DDX_Text(pDX, IDC_EDIT4, otherfilesum);
	DDX_Text(pDX, IDC_EDIT5, otherfileline);
	DDX_Text(pDX, IDC_EDIT7, otherfilesize);

	DDX_Text(pDX, IDC_EDIT1, hfilesum);
	DDX_Text(pDX, IDC_EDIT2, hfileline);
	DDX_Text(pDX, IDC_EDIT3, hfilesize);


	DDX_Text(pDX, IDC_EDIT8, AllfileSum);
	DDX_Text(pDX, IDC_EDIT12, Allfilelien);
	DDX_Text(pDX, IDC_EDIT6, AllfileSize);
	DDX_Text(pDX, IDC_EDIT13, FileName);
}

BEGIN_MESSAGE_MAP(CReadFileSizeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CReadFileSizeDlg::OnBnClickedButton1)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CReadFileSizeDlg 消息处理程序

BOOL CReadFileSizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadFileSizeDlg::OnPaint()
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
HCURSOR CReadFileSizeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CReadFileSizeDlg::ReadFile(const char* str, int& fileline)
{
	fp = fopen(str, "r");
	char flag;
	while (!feof(fp))
	{
		flag=fgetc(fp);
		if(flag=='\n')fileline++;
	}
	fileline++;
	fclose(fp);
}

void CReadFileSizeDlg::OnBnClickedButton1()
{
	BROWSEINFOA bi;
	char  Buffer[MAX_PATH];
	//初始化入口参数 bi
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = "文件夹路径选择";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_BROWSEINCLUDEFILES;//BIF_RETURONLYFSDIRS 
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;
	LPITEMIDLIST pIDList = SHBrowseForFolderA(&bi); //调用显示选择对话框  //注意下 这个函数会分配内存 但不会释放 需要手动释放										  
	if (!pIDList)
	{
		return;
	}
	SHGetPathFromIDListA(pIDList, Buffer);
	CoTaskMemFree(pIDList); //释放pIDList所指向内存空间;
	GetFileInfomation(Buffer);

	
}

void CReadFileSizeDlg::GetFileInfomation(const char* Buffer)
{
	Icfileline = 0;
	IcfileSize = 0;
	IcfileSum = 0;
	Ihfileline = 0;
	IhfileSize = 0;
	IhfileSum = 0;
	Iotherfileline = 0;
	IotherfileSize = 0;
	IotherfileSum = 0;
	IAllfileline = 0;
	IAllfileSize = 0;
	IAllfileSum = 0;

	CString wTxt;
	std::string temp = Buffer;
	std::string Path = Buffer;

	WIN32_FIND_DATAA fileData;
	if (PathIsDirectoryA(Path.c_str()))
	{
		Path = Path + "\\*.*";
		HANDLE hFind = FindFirstFileA(Path.c_str(), &fileData);
		while (hFind != INVALID_HANDLE_VALUE)
		{
			std::string FileRoot = temp + "\\" + fileData.cFileName;
			if (!PathIsDirectoryA(FileRoot.c_str()))
			{
				DWORD  SIZE = ((fileData.nFileSizeHigh * (MAXDWORD + 1)) + fileData.nFileSizeLow);
				if (FileRoot.find(".h", 0) != std::string::npos)
				{
					IhfileSum++;
					IhfileSize = SIZE + IhfileSize;
					ReadFile(FileRoot.c_str(), Ihfileline);
				}
				else if (FileRoot.find(".cpp", 0) != std::string::npos || FileRoot.find(".c", 0) != std::string::npos)
				{
					IcfileSum++;
					IcfileSize = SIZE + IcfileSize;
					ReadFile(FileRoot.c_str(), Icfileline);

				}
				else if (fileData.cFileName[0] != '.')
				{
					IotherfileSum++;
					IotherfileSize = SIZE + IotherfileSize;
					ReadFile(FileRoot.c_str(), Iotherfileline);
				}
			}
			if (!FindNextFileA(hFind, &fileData))break;

		}
		FindClose(hFind);
		IhfileSize = IhfileSize ? IhfileSize / 1024 + 1 : IhfileSize;
		IcfileSize = IcfileSize ? IcfileSize / 1024 + 1 : IcfileSize;
		IotherfileSize = IotherfileSize ? IotherfileSize / 1024 + 1 : IotherfileSize;
	}
	else
	{
		HANDLE hFind = FindFirstFileA(Path.c_str(), &fileData);//if (!FindNextFileA(hFind, &fileData))break;
		DWORD  SIZE = ((fileData.nFileSizeHigh * (MAXDWORD + 1)) + fileData.nFileSizeLow) / 1024 + 1;
		ReadFile(Path.c_str(), IAllfileline);
		if (Path.find(".h", 0) != std::string::npos)
		{
			Ihfileline = IAllfileline;
			IhfileSize = SIZE;
			IhfileSum++;
		}
		else if (Path.find(".cpp", 0) != std::string::npos || Path.find(".c", 0) != std::string::npos)
		{
			Icfileline = IAllfileline;
			IcfileSize = SIZE;
			IcfileSum++;
		}
		else if (fileData.cFileName[0] != '.')
		{
			Iotherfileline = IAllfileline;
			IotherfileSize = SIZE;
			IotherfileSum++;
		}
	}

	cppfileSum.Format(L"%d", IcfileSum);
	cppfilelien.Format(L"%d", Icfileline);

	cppfilesize.Format(L"%d KB", IcfileSize);

	otherfilesum.Format(L"%d", IotherfileSum);
	otherfileline.Format(L"%d", Iotherfileline);
	otherfilesize.Format(L"%d KB", IotherfileSize);

	hfilesum.Format(L"%d", IhfileSum);
	hfileline.Format(L"%d", Ihfileline);
	hfilesize.Format(L"%d KB", IhfileSize);

	IAllfileSum = IcfileSum + IotherfileSum + IhfileSum;
	IAllfileline = Icfileline + Iotherfileline + Ihfileline;
	IAllfileSize = IcfileSize + IotherfileSize + IhfileSize;
	if (IAllfileSize > 1024 * 20)
	{
		AllfileSize.Format(L"%d MB", IAllfileSize/1024);
	}
	else
	{
		AllfileSize.Format(L"%d KB", IAllfileSize);
	}
	AllfileSum.Format(L"%d", IAllfileSum);
	Allfilelien.Format(L"%d", IAllfileline);
	


	FileName = Buffer;
	UpdateData(FALSE);
}

void CReadFileSizeDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);


	// TODO: 在此添加消息处理程序代码和/或调用默认值
	WIN32_FIND_DATAA wfd;
	std::string strFileName;
	char  Buffer[MAX_PATH];
	int nCounts = DragQueryFileA(hDropInfo, 0xFFFFFFFF, NULL, 0);		//获取拖拽的总文件数
	for (int i = 0; i < nCounts; i++)
	{
		DragQueryFileA(hDropInfo, i, Buffer, MAX_PATH);
		FindClose(FindFirstFileA(Buffer, &wfd));
	}
	GetFileInfomation(Buffer);
	/*void CDropFileListCtrl::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	WCHAR filePath[MAX_PATH];
	WIN32_FIND_DATA wfd;
 
	CString strFileName;
	CString strFileSize;
	CString strCreateTime;
 
	int nCounts = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);		//获取拖拽的总文件数
	for (int i = 0; i < nCounts; i++)
	{
		DragQueryFile(hDropInfo, i, filePath, sizeof(filePath)*2);
		FindClose(FindFirstFile(filePath, &wfd));
 
		strFileName = wfd.cFileName;
		strFileSize.Format(_T("%d"), wfd.nFileSizeLow);
		CTime time(wfd.ftCreationTime);
		strCreateTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
 
		InsertItem(i, strFileName);
		SetItemText(i, 1, strFileSize);
		SetItemText(i, 2, strCreateTime);
	}
 
	CListCtrl::OnDropFiles(hDropInfo);
}*/


}
