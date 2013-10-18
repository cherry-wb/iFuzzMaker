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


// JpegSelView.cpp : 実装ファイル
//
#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "JpegSelView.h"
#include "AppMessage.h"
#include "MainFrm.h"

// CJpegSelView
IMPLEMENT_DYNCREATE(CJpegSelView, CTabChildView)

CJpegSelView::CJpegSelView()
	: CTabChildView(CJpegSelView::IDD)
{
	m_bDoDataExchange = FALSE;
}

CJpegSelView::~CJpegSelView()
{
}

void CJpegSelView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_JPEG_BROWSE, m_wndJpegFileBrowseCtrl);
	DDX_Control(pDX, IDC_ANALYZE_BUTTON, m_wndAnalyzeButton);
	DDX_Control(pDX, IDC_JPEG_STRUCTURE_LIST, m_wndJpegStructureList);

	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndJpegFileBrowseCtrl.EnableFileBrowseButton( NULL, _T("JPEG (*.jpg;*.jpeg)|*.jpg;*.jpeg|All files (*.*)|*.*|"));
		m_wndJpegFileBrowseCtrl.SetInitDirectory( ((CMainFrame*)AfxGetMainWnd())->GetFixedDatas()->GetAppConfig().GetJpegSelFolder() );
		m_wndJpegStructureList.InitCtrl();
	}
	m_wndJpegFileBrowseCtrl.SetWindowText( _T("") );
	m_wndJpegStructureList.ClearList();
	EnableUpdateStatusBar( FALSE );

	if( GetDocument()->IsOpenFile() )
	{
		m_wndJpegFileBrowseCtrl.SetWindowText( GetDocument()->GetUserDatas()->GetJpegFileName() );
		GetDocument()->ResetOpenFile();
		AnalysisJpeg();
	}
}

BEGIN_MESSAGE_MAP(CJpegSelView, CTabChildView)
	ON_BN_CLICKED(IDC_ANALYZE_BUTTON, &CJpegSelView::OnClickedAnalyzeButton)
	ON_MESSAGE(WM_APP_EXIF_ANALYZED, OnExifAnalyzed)
	ON_COMMAND(ID_OP_ANALYSIS_JPEG, &CJpegSelView::OnOpAnalysisJpeg)
	ON_UPDATE_COMMAND_UI(ID_OP_ANALYSIS_JPEG, &CJpegSelView::OnUpdateOpAnalysisJpeg)
	ON_EN_UPDATE(IDC_JPEG_BROWSE, &CJpegSelView::OnEnUpdateJpegBrowse)
END_MESSAGE_MAP()


// CJpegSelView 診断
#ifdef _DEBUG
void CJpegSelView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CJpegSelView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG


// CJpegSelView メッセージ ハンドラー
void CJpegSelView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);
	m_wndResizer.SetAnchor( IDC_JPEG_BROWSE, ANCHOR_HORIZONTALLY );
	m_wndResizer.SetAnchor( IDC_ANALYZE_BUTTON, ANCHOR_TOP | ANCHOR_RIGHT );
	m_wndResizer.SetAnchor( IDC_JPEG_STRUCTURE_LIST, ANCHOR_ALL );
	m_wndResizer.InvokeOnResized();
}

void CJpegSelView::OnClickedAnalyzeButton()
{
	AnalysisJpeg();
}

LRESULT CJpegSelView::OnExifAnalyzed( WPARAM wParam, LPARAM lParam )
{
	CWaitCursor WaitCursor;
	m_wndJpegStructureList.SetListData( GetDocument()->GetUserDatas() );
	//	前回のフォルダを記憶
	m_wndJpegFileBrowseCtrl.SetInitDirectory();
	WaitCursor.Restore();

	return TRUE;
}

void CJpegSelView::OnOpAnalysisJpeg()
{
	AnalysisJpeg();
}

void CJpegSelView::OnUpdateOpAnalysisJpeg(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

BOOL CJpegSelView::AnalysisJpeg()
{
	CString szFileName;

	m_wndJpegFileBrowseCtrl.GetWindowText( szFileName );

	if( !PathFileExists( szFileName ) )
	{
		MessageBox( _T("ファイルが存在しません"), _T("エラー"), MB_ICONHAND );
		return FALSE;
	}

	GetDocument()->GetUserDatas()->SetJpegFileName( szFileName );

	m_wndJpegStructureList.ClearList();
	AfxGetMainWnd()->PostMessage( WM_APP_READ_JPEG, NULL, NULL );

	return TRUE;
}

void CJpegSelView::OnEnUpdateJpegBrowse()
{
	if( m_wndJpegFileBrowseCtrl.IsBrowse() )
		AnalysisJpeg();
}
