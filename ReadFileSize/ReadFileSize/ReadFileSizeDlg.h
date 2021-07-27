
// ReadFileSizeDlg.h: 头文件
//

#pragma once


// CReadFileSizeDlg 对话框
class CReadFileSizeDlg : public CDialogEx
{
// 构造
public:
	CReadFileSizeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READFILESIZE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void ReadFile(const char* str, int& fileline);
	//virtual void DragAcceptFiles(BOOL bAccept = TRUE);
public:
	FILE* fp;
	int Icfileline{}, IcfileSize{}, IcfileSum{};//C/CPP文件  行 大小(字节)  数量
	int Ihfileline{}, IhfileSize{}, IhfileSum{};//h文件  行 大小(字节)  数量
	int Iotherfileline{}, IotherfileSize{}, IotherfileSum{};//其他文件  行 大小(字节)  数量
	int IAllfileline{}, IAllfileSize{}, IAllfileSum{};//P文件  行 大小(字节)  数量
public:
	afx_msg void OnBnClickedButton1();
	CString cppfileSum;
	CString cppfilelien;
	CString cppfilesize;

	CString otherfilesum;
	CString otherfileline;
	CString otherfilesize;

	CString hfilesum;
	CString hfileline;
	CString hfilesize;


	CString AllfileSum;
	CString Allfilelien;
	CString AllfileSize;
	CString FileName;
public:
	void GetFileInfomation(const char*);
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
