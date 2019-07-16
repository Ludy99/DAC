
// DrawImageDlg.h : ͷ�ļ�
//

#pragma once
#include <string>

// CDrawImageDlg �Ի���
class CDrawImageDlg : public CDialogEx
{
// ����
public:
	CDrawImageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAWIMAGE_DIALOG };

	std::wstring GetEditText(unsigned int dwCtrlID);
	void SetEditText(unsigned int dwCtrlID, const wchar_t* pText);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
