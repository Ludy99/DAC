
// DrawImageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DrawImage.h"
#include "DrawImageDlg.h"
#include "afxdialogex.h"
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawImageDlg 对话框



CDrawImageDlg::CDrawImageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDrawImageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawImageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawImageDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CDrawImageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDrawImageDlg::OnBnClickedCancel)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CDrawImageDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDrawImageDlg 消息处理程序

BOOL CDrawImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码
	SetEditText(IDC_EDIT4, L"10");
	SetEditText(IDC_EDIT5, L"3");

	SetEditText(IDC_EDIT6, L"15");
	SetEditText(IDC_EDIT7, L"100");
	SetEditText(IDC_EDIT8, L"600");
	SetEditText(IDC_EDIT9, L"400");

	return TRUE;
}

void CDrawImageDlg::SetEditText(unsigned int dwCtrlID, const wchar_t* pText)
{
	CWnd *pEdit = GetDlgItem(dwCtrlID);
	if (pEdit != NULL)
	{
		if(pText == NULL)
			pEdit->SetWindowText(L"");
		else
			pEdit->SetWindowText(pText);
	}
}

std::wstring CDrawImageDlg::GetEditText(unsigned int dwCtrlID)
{
	wchar_t wsText[1024] = L"";
	CWnd *pEdit = GetDlgItem(dwCtrlID);
	if(pEdit != NULL)
	{
		pEdit->GetWindowText(wsText, 1024);
	}
	std::wstring s1 = wsText;
	return s1;
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDrawImageDlg::OnPaint()
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
HCURSOR CDrawImageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDrawImageDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CDrawImageDlg::OnBnClickedButton1()
{
	Invalidate(true);
	UpdateWindow();
}

BOOL CDrawImageDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialogEx::OnEraseBkgnd(pDC);
	if (pDC == NULL)
	{
		return true;
	}

	// 从编辑框取值：
	std::wstring wsRangeX = GetEditText(IDC_EDIT4);
	std::wstring wsRangeY = GetEditText(IDC_EDIT5);
	std::wstring wsDrawLeft = GetEditText(IDC_EDIT6);
	std::wstring wsDrawTop = GetEditText(IDC_EDIT7);
	std::wstring wsDrawRight = GetEditText(IDC_EDIT8);
	std::wstring wsDrawBottom = GetEditText(IDC_EDIT9);

	// 定义
	float fRangeX = (float)wcstof(wsRangeX.c_str(), NULL);
	float fRangeY = (float)wcstof(wsRangeY.c_str(), NULL);

	// x轴与 y轴的起始量：
	int nStartX = (int)wcstol(wsDrawLeft.c_str(), NULL, 10);
	int nStartY = (int)wcstol(wsDrawTop.c_str(), NULL, 10);

	// X轴与Y轴的绘制区域，防止画出界：
	int nRangeWidth = (int)wcstol(wsDrawRight.c_str(), NULL, 10);
	int nRangeHeight = (int)wcstol(wsDrawBottom.c_str(), NULL, 10);

	// 计算坐标中心点：
	int nBaseX = nStartX + (nRangeWidth ) / 2;
	int nBaseY = nStartY + (nRangeHeight) / 2;

	// 计算单个刻度需要跨多少像素(X轴)：
	float fPixelX = ((float)nRangeWidth / (fRangeX*2.0f));
	// 计算单个刻度需要跨多少像素(Y轴)：
	float fPixelY = ((float)nRangeHeight / (fRangeY*10.0f*2.0f));

	// 画坐标轴：
	{
		// 绘制外框：
		pDC->Rectangle(nStartX, nStartY, nStartX + nRangeWidth, nStartY+nRangeHeight);

		// 绘制X轴基线（坐标轴）
		pDC->MoveTo(nStartX, nBaseY);
		pDC->LineTo(nStartX+nRangeWidth, nBaseY);

		// 绘制Y轴基线（坐标轴）
		pDC->MoveTo(nBaseX, nStartY);
		pDC->LineTo(nBaseX, nStartY+nRangeHeight);

		// 绘制刻度(+X轴)：
		float i = 0.0f, x = 0.0f, y = 0.0f;
		for (i = 0.0f; i < (float)fRangeX; i += 1.0f)
		{
			int nLen = 4;
			x = ((float)nBaseX + (fPixelX*(float)i));
			int xPos = (int)x;
			pDC->MoveTo(xPos, nBaseY);
			if (((int)i % 5) == 0)
			{
				wchar_t wsText[8] = L"";
				wsprintf(wsText, L"%d", (int)i);
				pDC->TextOutW(xPos, nBaseY+3, wsText, wcslen(wsText));
				pDC->LineTo(xPos, nBaseY - nLen * 2);
			}
			else
			{
				pDC->LineTo(xPos, nBaseY - nLen);
			}
		}
		// 绘制刻度(-X轴)：
		i = 0.0f, x = 0.0f;
		for (i = 0.0f; i < (float)fRangeX; i += 1.0f)
		{
			int nLen = 4;
			x = ((float)nBaseX - (fPixelX*(float)i));
			int xPos = (int)x;
			pDC->MoveTo(xPos, nBaseY);
			if (((int)i % 5) == 0)
			{
				if ((int)i != 0)
				{
					// '0'在画正坐标轴时画过了。
					wchar_t wsText[8] = L"";
					wsprintf(wsText, L"-%d", (int)i);
					pDC->TextOutW(xPos, nBaseY + 3, wsText, wcslen(wsText));
				}
				pDC->LineTo(xPos, nBaseY - nLen * 2);
			}
			else
			{
				pDC->LineTo(xPos, nBaseY - nLen);
			}
		}
		// 绘制刻度(+Y轴)：
		i = 0.0f, y = 0.0f;
		for (i = 0.0f; i < (float)(fRangeY*10.0f); i += 1.0f)
		{
			int nLen = 4;
			y = ((float)nBaseY - (fPixelY*(float)i));
			int yPos = (int)y;
			pDC->MoveTo(nBaseX, yPos);
			if (((int)i % 5) == 0)
			{
				if ((int)i != 0)
				{
					wchar_t wsText[8] = L"";
					swprintf(wsText, L"%.1f", i / 10.0f);
					// 文字向右移 2 像素：
					pDC->TextOutW(nBaseX + nLen * 2 + 2, yPos, wsText, wcslen(wsText));
				}
				pDC->LineTo(nBaseX + nLen * 2, yPos);
			}
			else
			{
				pDC->LineTo(nBaseX + nLen, yPos);
			}
		}
		// 绘制刻度(-Y轴)：
		i = 0.0f, y = 0.0f;
		for (i = 0.0f; i < (float)(fRangeY*10.0f); i += 1.0f)
		{
			int nLen = 4;
			y = ((float)nBaseY + (fPixelY*(float)i));
			int yPos = (int)y;
			pDC->MoveTo(nBaseX, yPos);
			if (((int)i % 5) == 0)
			{
				if ((int)i != 0)
				{
					wchar_t wsText[8] = L"";
					swprintf(wsText, L"-%.1f", (i/10.0f));
					// 文字向右移 2 像素：
					pDC->TextOutW(nBaseX + nLen * 2 + 2, yPos, wsText, wcslen(wsText));
				}
				pDC->LineTo(nBaseX + nLen * 2, yPos);
			}
			else
			{
				pDC->LineTo(nBaseX + nLen, yPos);
			}
		}
	}

	// 绘制算法图像：
	{
		float fX = 0.0f, fY = 0.0f;

		// 绘制正坐标轴上的图像：
		int nFirstPoint = 0;
		for (fX = 0.0f; fX <= (fRangeX); fX += 0.02f)
		{
			// 计算数值：
			float fSinXValue = sinf(fX);

			// Y 坐标对齐 Y 轴刻度：
			float fRealY = (nRangeHeight / 2.0f)*fSinXValue / fRangeY;

			// 绘制到屏幕上：
			int x = nBaseX + (int)(fX*fPixelX);
			int y = nBaseY - (int)fRealY;// 坐标正方向在上方，而上方屏幕坐标小，所以减；

			if (nFirstPoint == 0)
			{
				pDC->MoveTo(x, y);
				nFirstPoint = 1;
			}
			pDC->LineTo(x, y);
		}

		// 绘制负轴上的图像：
		nFirstPoint = 0;
		for (fX = 0.0f; fX >= (-fRangeX); fX -= 0.02f)
		{
			// 计算数值：
			float fSinXValue = sinf(fX);

			// Y 坐标对齐 Y 轴刻度：
			float fRealY = (nRangeHeight / 2.0f)*fSinXValue / fRangeY;

			// 绘制到屏幕上：
			int x = nBaseX + (int)(fX*fPixelX);
			int y = nBaseY - (int)fRealY;// 坐标负向方在下方，而下方屏幕坐标大，所以加；

			if (nFirstPoint == 0)
			{
				pDC->MoveTo(x, y);
				nFirstPoint = 1;
			}
			pDC->LineTo(x, y);
		}
	}
	return true;
}


