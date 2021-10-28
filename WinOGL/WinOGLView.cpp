#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MODE_EDIT, &CWinOGLView::OnModeEdit)
	ON_UPDATE_COMMAND_UI(ID_MODE_EDIT, &CWinOGLView::OnUpdateModeEdit)
	ON_COMMAND(ID_MODE_OBJECT, &CWinOGLView::OnModeObject)
	ON_UPDATE_COMMAND_UI(ID_MODE_OBJECT, &CWinOGLView::OnUpdateModeObject)
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	clickX = 0;
	clickY = 0;
}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画

void CWinOGLView::OnDraw(CDC* pDC)
{
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(pDC->m_hDC, m_hRC);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT /*GL_DEPTH_BUFFER_BIT*/);

	AC.Draw();

	glFlush();
	SwapBuffers(pDC->m_hDC);

	wglMakeCurrent(pDC->m_hDC, NULL);
}


// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー

int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		24,
		0,0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}

void CWinOGLView::OnDestroy()
{
	CView::OnDestroy();
	wglDeleteContext(m_hRC);
}

BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CWinOGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);

	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double hi;

	if (cx > cy)
	{
		hi = (double)cx / cy;
		glOrtho(-1 * hi, 1 * hi, -1, 1, -100, 100);
	}
	else
	{
		hi = (double)cy / cx;
		glOrtho(-1, 1, -1 * hi, 1 * hi, -100, 100);
	}

	glMatrixMode(GL_MODELVIEW);

	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}

//最初のウィンドウの処理
void CWinOGLView::SettingWindow(CPoint point)
{
	CRect rect;
	GetClientRect(rect);

	float hi;
	float w = rect.Width();
	float h = rect.Height();

	clickX = (float)point.x / w;
	clickY = 1 - (float)point.y / h;

	if (w > h)
	{
		hi = (float)w / h;
		clickX = (float)clickX * 2 - 1;
		clickX = (float)clickX * hi;
		clickY = (float)clickY * 2 - 1;
		glOrtho(-1 * hi, 1 * hi, -1, 1, -100, 100);
	}
	else
	{
		hi = (float)h / w;
		clickX = (float)clickX * 2 - 1;
		clickY = (float)clickY * 2 - 1;
		clickY = (float)clickY * hi;
		glOrtho(-1, 1, -1 * hi, 1 * hi, -100, 100);
	}

	point.x = clickX;
	point.y = clickY;
}

void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SettingWindow(point);

	//オブジェクトモード
	if (Mode_Object == true)
	{
		AC.ChooseShape(clickX, clickY);
	}

	//エディットモード
	if (Mode_Edit == true)
	{
		AC.SaveClick(clickX, clickY);
	}	

	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}

void CWinOGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SettingWindow(point);

	//エディットモード
	if (Mode_Edit == true)
	{
		AC.ChooseLine(clickX, clickY);
		AC.ChooseClick(clickX, clickY);
	}

	RedrawWindow();
	CView::OnRButtonDown(nFlags, point);
}


void CWinOGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		ChangeMode(++Mode_Num);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//モード切り替え(num:0=Object,1=Edit)
void CWinOGLView::ChangeMode(int num)
{
	if (Mode_Num > 1)
	{
		Mode_Num = 0;
		
	}

	num = Mode_Num;

	if (num == 0)
	{
		Mode_Object = true;
		Mode_Edit = false;
		AC.FreeChooseVertex();
	}
	else if (num == 1)
	{
		Mode_Edit = true;
		Mode_Object = false;
		AC.FreeChooseShape();
	}
	RedrawWindow();
}

void CWinOGLView::OnModeEdit()
{
	Mode_Edit = true;
	Mode_Object = false;
	AC.FreeChooseShape();
	Mode_Num = 1;
	RedrawWindow();
}
void CWinOGLView::OnUpdateModeEdit(CCmdUI* pCmdUI)
{
	if (Mode_Edit == true)
	{
		pCmdUI->SetCheck(true);
	}
	else
	{
		pCmdUI->SetCheck(false);
	}
}
void CWinOGLView::OnModeObject()
{
	Mode_Object = true;
	Mode_Edit = false;
	AC.FreeChooseVertex();
	Mode_Num = 0;
	RedrawWindow();
}
void CWinOGLView::OnUpdateModeObject(CCmdUI* pCmdUI)
{
	if (Mode_Object == true)
	{
		pCmdUI->SetCheck(true);
	}
	else
	{
		pCmdUI->SetCheck(false);
	}
}
