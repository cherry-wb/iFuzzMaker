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

// ExifSelView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "ExifSelView.h"
#include "AppMessage.h"

// CExifSelView
IMPLEMENT_DYNCREATE(CExifSelView, CTabChildView)

CExifSelView::CExifSelView()
	: CTabChildView(CExifSelView::IDD)
{
	m_bDoDataExchange = FALSE;
	m_lpExifListView = NULL;
	m_lpExifInfoView = NULL;
	m_lpCreateContext = NULL;
}

CExifSelView::~CExifSelView()
{
}

void CExifSelView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_FRAME_STATIC, m_wndFrameStatic);

	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndFrameStatic.SetClient( &m_wndSplitter );

		CRect rc;
		m_wndSplitter.GetClientRect( rc );
		m_wndSplitter.SetColumnInfo( 0, (int)(rc.Width()*0.7), 0 );
		m_wndSplitter.RecalcLayout();
	}
}

BEGIN_MESSAGE_MAP(CExifSelView, CTabChildView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CExifSelView 診断
#ifdef _DEBUG
void CExifSelView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CExifSelView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG

// CExifSelView メッセージ ハンドラー
void CExifSelView::OnInitialView()
{
	CRect rc;
	GetClientRect( rc );
	rc.DeflateRect( 3, 3 );
	m_wndSplitter.MoveWindow( rc );

	m_wndResizer.Hook(this,m_sizeInitWnd);
	m_wndResizer.SetAnchor( IDC_FRAME_STATIC, ANCHOR_ALL );
	m_wndResizer.InvokeOnResized();

	GetActivateView();
}

BOOL CExifSelView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	if( m_lpExifListView )
		m_lpExifListView->EnableUpdateStatusBar( TRUE );
	return FALSE;
}

int CExifSelView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabChildView::OnCreate(lpCreateStruct) == -1)
		return -1;

	if( !m_wndSplitter.CreateStatic( this, 1, 2 ) )
	{
		return -1;
	}
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CExifListView), CSize(100,100), (CCreateContext*)lpCreateStruct->lpCreateParams))
	{
		return -1;
	}
	if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CExifInfoView), CSize(100,100), (CCreateContext*)lpCreateStruct->lpCreateParams))
	{
		return -1;
	}
	m_lpExifListView = (CExifListView*)m_wndSplitter.GetPane( 0, 0 );
	m_lpExifInfoView = (CExifInfoView*)m_wndSplitter.GetPane( 0, 1 );
	m_lpExifListView->SetExifInfoView( m_lpExifInfoView );

	return 0;
}
