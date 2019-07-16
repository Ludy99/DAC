
// DrawImageDlg.h : 头文件
//

#pragma once
#include <string>

// CDrawImageDlg 对话框
class CDrawImageDlg : public CDialogEx
{
// 构造
public:
	CDrawImageDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRAWIMAGE_DIALOG };

	std::wstring GetEditText(unsigned int dwCtrlID);
	void SetEditText(unsigned int dwCtrlID, const wchar_t* pText);

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
	afx_msg void OnBnClickedOk(){}
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();
};
