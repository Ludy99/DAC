
// DrawImageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawImage.h"
#include "DrawImageDlg.h"
#include "afxdialogex.h"
#pragma warning(disable:4996)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawImageDlg �Ի���



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


// CDrawImageDlg ��Ϣ�������

BOOL CDrawImageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_MAXIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDrawImageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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

	// �ӱ༭��ȡֵ��
	std::wstring wsRangeX = GetEditText(IDC_EDIT4);
	std::wstring wsRangeY = GetEditText(IDC_EDIT5);
	std::wstring wsDrawLeft = GetEditText(IDC_EDIT6);
	std::wstring wsDrawTop = GetEditText(IDC_EDIT7);
	std::wstring wsDrawRight = GetEditText(IDC_EDIT8);
	std::wstring wsDrawBottom = GetEditText(IDC_EDIT9);

	// ����
	float fRangeX = (float)wcstof(wsRangeX.c_str(), NULL);
	float fRangeY = (float)wcstof(wsRangeY.c_str(), NULL);

	// x���� y�����ʼ����
	int nStartX = (int)wcstol(wsDrawLeft.c_str(), NULL, 10);
	int nStartY = (int)wcstol(wsDrawTop.c_str(), NULL, 10);

	// X����Y��Ļ������򣬷�ֹ�����磺
	int nRangeWidth = (int)wcstol(wsDrawRight.c_str(), NULL, 10);
	int nRangeHeight = (int)wcstol(wsDrawBottom.c_str(), NULL, 10);

	// �����������ĵ㣺
	int nBaseX = nStartX + (nRangeWidth ) / 2;
	int nBaseY = nStartY + (nRangeHeight) / 2;

	// ���㵥���̶���Ҫ���������(X��)��
	float fPixelX = ((float)nRangeWidth / (fRangeX*2.0f));
	// ���㵥���̶���Ҫ���������(Y��)��
	float fPixelY = ((float)nRangeHeight / (fRangeY*10.0f*2.0f));

	// �������᣺
	{
		// �������
		pDC->Rectangle(nStartX, nStartY, nStartX + nRangeWidth, nStartY+nRangeHeight);

		// ����X����ߣ������ᣩ
		pDC->MoveTo(nStartX, nBaseY);
		pDC->LineTo(nStartX+nRangeWidth, nBaseY);

		// ����Y����ߣ������ᣩ
		pDC->MoveTo(nBaseX, nStartY);
		pDC->LineTo(nBaseX, nStartY+nRangeHeight);

		// ���ƿ̶�(+X��)��
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
		// ���ƿ̶�(-X��)��
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
					// '0'�ڻ���������ʱ�����ˡ�
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
		// ���ƿ̶�(+Y��)��
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
					// ���������� 2 ���أ�
					pDC->TextOutW(nBaseX + nLen * 2 + 2, yPos, wsText, wcslen(wsText));
				}
				pDC->LineTo(nBaseX + nLen * 2, yPos);
			}
			else
			{
				pDC->LineTo(nBaseX + nLen, yPos);
			}
		}
		// ���ƿ̶�(-Y��)��
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
					// ���������� 2 ���أ�
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

	// �����㷨ͼ��
	{
		float fX = 0.0f, fY = 0.0f;

		// �������������ϵ�ͼ��
		int nFirstPoint = 0;
		for (fX = 0.0f; fX <= (fRangeX); fX += 0.02f)
		{
			// ������ֵ��
			float fSinXValue = sinf(fX);

			// Y ������� Y ��̶ȣ�
			float fRealY = (nRangeHeight / 2.0f)*fSinXValue / fRangeY;

			// ���Ƶ���Ļ�ϣ�
			int x = nBaseX + (int)(fX*fPixelX);
			int y = nBaseY - (int)fRealY;// �������������Ϸ������Ϸ���Ļ����С�����Լ���

			if (nFirstPoint == 0)
			{
				pDC->MoveTo(x, y);
				nFirstPoint = 1;
			}
			pDC->LineTo(x, y);
		}

		// ���Ƹ����ϵ�ͼ��
		nFirstPoint = 0;
		for (fX = 0.0f; fX >= (-fRangeX); fX -= 0.02f)
		{
			// ������ֵ��
			float fSinXValue = sinf(fX);

			// Y ������� Y ��̶ȣ�
			float fRealY = (nRangeHeight / 2.0f)*fSinXValue / fRangeY;

			// ���Ƶ���Ļ�ϣ�
			int x = nBaseX + (int)(fX*fPixelX);
			int y = nBaseY - (int)fRealY;// ���긺�����·������·���Ļ��������Լӣ�

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


