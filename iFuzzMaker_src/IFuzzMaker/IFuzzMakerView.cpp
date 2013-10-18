//================================================================================
//  独立行政法人情報処理推進機構 (IPA)
//  - Information-technology Promotion Agency, Japan -
//
//                                                    独立行政法人情報処理推進機構
//                                                   技術本部 セキュリティセンター
//                                                情報セキュリティ技術ラボラトリー
//
//      -- JPEG テスト支援ツール iFuzzMaker  --
//                                                                Date：2013/07/30
//--------------------------------------------------------------------------------
//  Copyright (c) 2013, IPA, Japan.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//      * Neither the name of the IPA nor the
//        names of its contributors may be used to endorse or promote products
//        derived from this software without specific prior written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==============================================================================


// IFuzzMakerView.cpp : CIFuzzMakerView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、サムネイル、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "IFuzzMaker.h"
#endif

#include "IFuzzMakerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MainFrm.h"
#include "IFuzzMakerView.h"
#include "AppMessage.h"

// CIFuzzMakerView

IMPLEMENT_DYNCREATE(CIFuzzMakerView, CFormView)

BEGIN_MESSAGE_MAP(CIFuzzMakerView, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, &CIFuzzMakerView::OnTabChange)
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGING_ACTIVE_TAB, &CIFuzzMakerView::OnTabChangeing)
	ON_COMMAND(ID_OP_ANALYSIS_JPEG, &CIFuzzMakerView::OnOpAnalysisJpeg)
	ON_UPDATE_COMMAND_UI(ID_OP_ANALYSIS_JPEG, &CIFuzzMakerView::OnUpdateOpAnalysisJpeg)
	ON_COMMAND(ID_OP_READ_PATTERN, &CIFuzzMakerView::OnOpReadPattern)
	ON_UPDATE_COMMAND_UI(ID_OP_READ_PATTERN, &CIFuzzMakerView::OnUpdateOpReadPattern)
	ON_COMMAND(ID_OP_VIEW_FUZZLIST, &CIFuzzMakerView::OnOpViewFuzzlist)
	ON_UPDATE_COMMAND_UI(ID_OP_VIEW_FUZZLIST, &CIFuzzMakerView::OnUpdateOpViewFuzzlist)
	ON_COMMAND(ID_OP_CREATE_FUZZFILE, &CIFuzzMakerView::OnOpCreateFuzzfile)
	ON_UPDATE_COMMAND_UI(ID_OP_CREATE_FUZZFILE, &CIFuzzMakerView::OnUpdateOpCreateFuzzfile)
	ON_COMMAND(ID_OP_CANCEL_CREATE_FUZZFILE, &CIFuzzMakerView::OnOpCancelCreateFuzzfile)
	ON_UPDATE_COMMAND_UI(ID_OP_CANCEL_CREATE_FUZZFILE, &CIFuzzMakerView::OnUpdateOpCancelCreateFuzzfile)
	ON_MESSAGE(WM_APP_START_CREATE_FUZZ, OnStartCreateFuzz)
	ON_MESSAGE(WM_APP_END_CREATE_FUZZ, OnEndCreateFuzz)
END_MESSAGE_MAP()

// CIFuzzMakerView コンストラクション/デストラクション
CIFuzzMakerView::CIFuzzMakerView()
	: CFormView(CIFuzzMakerView::IDD)
{
	m_lpJpegSelView = NULL;
	m_lpExifSelView = NULL;
	m_lpSegmentItemSelView = NULL;
	m_lpPatternSelView = NULL;
	m_lpFuzzSelView = NULL;
	m_lpFuzzCreateView = NULL;
}

CIFuzzMakerView::~CIFuzzMakerView()
{
}

void CIFuzzMakerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CIFuzzMakerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(0, 0));
	GetDocument()->SetFixedDatas( ((CMainFrame*)AfxGetMainWnd())->GetFixedDatas() );
}

// CIFuzzMakerView 診断

#ifdef _DEBUG
void CIFuzzMakerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIFuzzMakerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIFuzzMakerDoc* CIFuzzMakerView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIFuzzMakerDoc)));
	return (CIFuzzMakerDoc*)m_pDocument;
}
#endif //_DEBUG


// CIFuzzMakerView メッセージ ハンドラー
BOOL CIFuzzMakerView::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);
	CMFCVisualManager::GetInstance()->OnFillPopupWindowBackground(pDC,rectClient);
	return TRUE;
}

HBRUSH CIFuzzMakerView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(NULL_BRUSH);
}


int CIFuzzMakerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;


	m_wndTabCtrl.SetImageList( IDB_TAB_ICON_BITMAP, 16, RGB(255, 0, 255) );

	CRect rc;
	GetClientRect( rc );
	m_wndTabCtrl.Create( CMFCTabCtrl::STYLE_3D_ONENOTE, rc, this, ID_TAB, CMFCTabCtrl::LOCATION_TOP );
	m_wndTabCtrl.EnableTabSwap( FALSE );
	m_wndTabCtrl.SetActiveTabBoldFont();

	m_wndResizer.Hook(this);
	m_wndResizer.SetAnchor( ID_TAB, ANCHOR_ALL );
	m_wndResizer.InvokeOnResized();

	CRuntimeClass *pJpegSelView = RUNTIME_CLASS(CJpegSelView);
	m_lpJpegSelView = (CJpegSelView*) pJpegSelView->CreateObject();
	if(m_lpJpegSelView == NULL)
		return -1;
	if( !m_lpJpegSelView->CreateForm( CRect(0,0,0,0), &m_wndTabCtrl, CJpegSelView::IDD, (CCreateContext*)lpCreateStruct->lpCreateParams ))
		return -1;
	m_wndTabCtrl.AddTab( m_lpJpegSelView, _T("JPEG選択"), TAB_JPEG_SEL, FALSE );

	CRuntimeClass *pExifSelView = RUNTIME_CLASS(CExifSelView);
	m_lpExifSelView = (CExifSelView*) pExifSelView->CreateObject();
	if(m_lpExifSelView == NULL)
		return -1;
	if( !m_lpExifSelView->CreateForm( CRect(0,0,0,0), &m_wndTabCtrl, CExifSelView::IDD, (CCreateContext*)lpCreateStruct->lpCreateParams ))
		return -1;
	m_wndTabCtrl.AddTab( m_lpExifSelView, _T("Exifタグ選択"), TAB_EXIF_SEL, FALSE );

	CRuntimeClass *pSegmentItemSelView = RUNTIME_CLASS(CSegmentItemSelView);
	m_lpSegmentItemSelView = (CSegmentItemSelView*) pSegmentItemSelView->CreateObject();
	if(m_lpSegmentItemSelView == NULL)
		return -1;
	if( !m_lpSegmentItemSelView->CreateForm( CRect(0,0,0,0), &m_wndTabCtrl, CSegmentItemSelView::IDD, (CCreateContext*)lpCreateStruct->lpCreateParams ))
		return -1;
	m_wndTabCtrl.AddTab( m_lpSegmentItemSelView, _T("セグメント要素選択"), TAB_SEGMENT_ITEM_SEL, FALSE );

	CRuntimeClass *pPatternSelView = RUNTIME_CLASS(CPatternSelView);
	m_lpPatternSelView = (CPatternSelView*) pPatternSelView->CreateObject();
	if(m_lpPatternSelView == NULL)
		return -1;
	if( !m_lpPatternSelView->CreateForm( CRect(0,0,0,0), &m_wndTabCtrl, CPatternSelView::IDD, (CCreateContext*)lpCreateStruct->lpCreateParams ))
		return -1;
	m_wndTabCtrl.AddTab( m_lpPatternSelView, _T("テストデータ生成ルール選択"), TAB_PATTERN_SEL, FALSE );

	CRuntimeClass *pFuzzSelView = RUNTIME_CLASS(CFuzzSelView);
	m_lpFuzzSelView = (CFuzzSelView*) pFuzzSelView->CreateObject();
	if(m_lpFuzzSelView == NULL)
		return -1;
	if( !m_lpFuzzSelView->CreateForm( CRect(0,0,0,0), &m_wndTabCtrl, CFuzzSelView::IDD, (CCreateContext*)lpCreateStruct->lpCreateParams ))
		return -1;
	m_wndTabCtrl.AddTab( m_lpFuzzSelView, _T("テスト値選択"), TAB_FUZZ_SEL, FALSE );

	CRuntimeClass *pFuzzCreateView = RUNTIME_CLASS(CFuzzCreateView);
	m_lpFuzzCreateView = (CFuzzCreateView*) pFuzzCreateView->CreateObject();
	if(m_lpFuzzCreateView == NULL)
		return -1;
	if( !m_lpFuzzCreateView->CreateForm( CRect(0,0,0,0), &m_wndTabCtrl, CFuzzCreateView::IDD, (CCreateContext*)lpCreateStruct->lpCreateParams ))
		return -1;
	m_wndTabCtrl.AddTab( m_lpFuzzCreateView, _T("テストデータ出力"), TAB_FUZZ_CREATE, FALSE );
	

	return 0;
}

LRESULT CIFuzzMakerView::OnTabChangeing( WPARAM wParam, LPARAM lParam )
{
	if( GetDocument()->GetUserDatas()->GetFuzzCreateing() )
	{
		m_wndTabCtrl.SetActiveTab(TAB_FUZZ_CREATE);
		return TRUE;
	}
	return FALSE;
}

LRESULT CIFuzzMakerView::OnTabChange( WPARAM wParam, LPARAM lParam )
{
	if( !m_lpJpegSelView || !m_lpExifSelView || !m_lpPatternSelView || !m_lpFuzzSelView || !m_lpFuzzCreateView )
		return FALSE;

	int nActiveTab = m_wndTabCtrl.GetActiveTab();

	switch( nActiveTab )
	{
	case TAB_JPEG_SEL:
		m_lpExifSelView->EnableUpdateStatusBar( FALSE );
		m_lpSegmentItemSelView->EnableUpdateStatusBar( FALSE );
		m_lpPatternSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzCreateView->EnableUpdateStatusBar( FALSE );
		m_lpJpegSelView->EnableUpdateStatusBar( TRUE );
		break;
	case TAB_EXIF_SEL:
		m_lpJpegSelView->EnableUpdateStatusBar( FALSE );
		m_lpSegmentItemSelView->EnableUpdateStatusBar( FALSE );
		m_lpPatternSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzCreateView->EnableUpdateStatusBar( FALSE );
		m_lpExifSelView->EnableUpdateStatusBar( TRUE );
		break;
	case TAB_SEGMENT_ITEM_SEL:
		m_lpJpegSelView->EnableUpdateStatusBar( FALSE );
		m_lpExifSelView->EnableUpdateStatusBar( FALSE );
		m_lpPatternSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzCreateView->EnableUpdateStatusBar( FALSE );
		m_lpSegmentItemSelView->EnableUpdateStatusBar( TRUE );
		break;
	case TAB_PATTERN_SEL:
		m_lpJpegSelView->EnableUpdateStatusBar( FALSE );
		m_lpExifSelView->EnableUpdateStatusBar( FALSE );
		m_lpSegmentItemSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzCreateView->EnableUpdateStatusBar( FALSE );
		m_lpPatternSelView->EnableUpdateStatusBar( TRUE );
		break;
	case TAB_FUZZ_SEL:
		m_lpJpegSelView->EnableUpdateStatusBar( FALSE );
		m_lpExifSelView->EnableUpdateStatusBar( FALSE );
		m_lpSegmentItemSelView->EnableUpdateStatusBar( FALSE );
		m_lpPatternSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzCreateView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzSelView->EnableUpdateStatusBar( TRUE );
		break;
	case TAB_FUZZ_CREATE:
		m_lpJpegSelView->EnableUpdateStatusBar( FALSE );
		m_lpExifSelView->EnableUpdateStatusBar( FALSE );
		m_lpSegmentItemSelView->EnableUpdateStatusBar( FALSE );
		m_lpPatternSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzSelView->EnableUpdateStatusBar( FALSE );
		m_lpFuzzCreateView->EnableUpdateStatusBar( TRUE );
		break;
	}
	return TRUE;
}

void CIFuzzMakerView::OnOpAnalysisJpeg()
{
	m_lpJpegSelView->PostMessage( WM_COMMAND, ID_OP_ANALYSIS_JPEG, NULL );
}

void CIFuzzMakerView::OnUpdateOpAnalysisJpeg(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TAB_JPEG_SEL == m_wndTabCtrl.GetActiveTab() );
}

void CIFuzzMakerView::OnOpReadPattern()
{
	m_lpPatternSelView->PostMessage( WM_COMMAND, ID_OP_READ_PATTERN, NULL );
}

void CIFuzzMakerView::OnUpdateOpReadPattern(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TAB_PATTERN_SEL == m_wndTabCtrl.GetActiveTab() );
}

void CIFuzzMakerView::OnOpViewFuzzlist()
{
	m_lpFuzzSelView->PostMessage( WM_COMMAND, ID_OP_VIEW_FUZZLIST, NULL );
}

void CIFuzzMakerView::OnUpdateOpViewFuzzlist(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TAB_FUZZ_SEL == m_wndTabCtrl.GetActiveTab() &&
					GetDocument()->GetUserDatas()->GetCheckedFealdEntryDataCount() && 
					GetDocument()->GetUserDatas()->GetCheckedPatternDataCount() );
}

void CIFuzzMakerView::OnOpCreateFuzzfile()
{
	m_lpFuzzCreateView->PostMessage( WM_COMMAND, ID_OP_CREATE_FUZZFILE, NULL );
}


void CIFuzzMakerView::OnUpdateOpCreateFuzzfile(CCmdUI *pCmdUI)
{
	BOOL bEnable = GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount() && !GetDocument()->GetUserDatas()->GetFuzzCreateing();
	pCmdUI->Enable(bEnable);
}


void CIFuzzMakerView::OnOpCancelCreateFuzzfile()
{
	m_lpFuzzCreateView->PostMessage( WM_COMMAND, ID_OP_CANCEL_CREATE_FUZZFILE, NULL );
}


void CIFuzzMakerView::OnUpdateOpCancelCreateFuzzfile(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( GetDocument()->GetUserDatas()->GetFuzzCreateing() );
}


BOOL CIFuzzMakerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFormView::PreCreateWindow(cs);
}


LRESULT CIFuzzMakerView::OnStartCreateFuzz( WPARAM wParam, LPARAM lParam )
{
	COLORREF clrText = afxGlobalData.GetColor(COLOR_GRAYTEXT);

	m_wndTabCtrl.SetTabTextColor( TAB_JPEG_SEL, clrText );
	m_wndTabCtrl.SetTabTextColor( TAB_EXIF_SEL, clrText );
	m_wndTabCtrl.SetTabTextColor( TAB_SEGMENT_ITEM_SEL, clrText );
	m_wndTabCtrl.SetTabTextColor( TAB_PATTERN_SEL, clrText );
	m_wndTabCtrl.SetTabTextColor( TAB_FUZZ_SEL, clrText );
	m_wndTabCtrl.RedrawWindow();
	return TRUE;
}

LRESULT CIFuzzMakerView::OnEndCreateFuzz( WPARAM wParam, LPARAM lParam )
{
	m_wndTabCtrl.SetTabTextColor( TAB_JPEG_SEL, afxGlobalData.clrBtnText );
	m_wndTabCtrl.SetTabTextColor( TAB_EXIF_SEL, afxGlobalData.clrBtnText );
	m_wndTabCtrl.SetTabTextColor( TAB_SEGMENT_ITEM_SEL, afxGlobalData.clrBtnText );
	m_wndTabCtrl.SetTabTextColor( TAB_PATTERN_SEL, afxGlobalData.clrBtnText );
	m_wndTabCtrl.SetTabTextColor( TAB_FUZZ_SEL, afxGlobalData.clrBtnText );

	m_wndTabCtrl.RedrawWindow();
	return TRUE;
}
