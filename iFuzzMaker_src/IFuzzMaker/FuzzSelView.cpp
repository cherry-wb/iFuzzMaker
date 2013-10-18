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

// FuzzSelView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "FuzzSelView.h"
#include "AppMessage.h"

// CFuzzSelView
IMPLEMENT_DYNCREATE(CFuzzSelView, CTabChildView)

CFuzzSelView::CFuzzSelView()
	: CTabChildView(CFuzzSelView::IDD)
{
	m_bDoDataExchange = FALSE;
}

CFuzzSelView::~CFuzzSelView()
{
}

void CFuzzSelView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FUZZ_SELECT_LIST, m_wndFuzzSelectList);
	DDX_Control(pDX, IDC_LIST_BUTTON, m_wndCreateListButton);
	DDX_Control(pDX, IDC_COUNT_LABEL, m_wndCountLabel);

	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndFuzzSelectList.InitCtrl();
	}
	m_wndFuzzSelectList.ClearList();
	EnableUpdateStatusBar( FALSE );


}

BEGIN_MESSAGE_MAP(CFuzzSelView, CTabChildView)
	ON_BN_CLICKED(IDC_LIST_BUTTON, &CFuzzSelView::OnBnClickedListButton)
	ON_MESSAGE(WM_APP_EXIF_ANALYZED, OnExifAnalyzed)
	ON_MESSAGE(WM_APP_GROUP_DISP, OnGroupDisp)
	ON_MESSAGE(WM_APP_FUZZ_LIST_DISP, OnFuzzListDisp)
	ON_COMMAND(ID_OP_VIEW_FUZZLIST, &CFuzzSelView::OnOpViewFuzzlist)
	ON_UPDATE_COMMAND_UI(ID_OP_VIEW_FUZZLIST, &CFuzzSelView::OnUpdateOpViewFuzzlist)
END_MESSAGE_MAP()


// CFuzzSelView 診断
#ifdef _DEBUG
void CFuzzSelView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CFuzzSelView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG

// CFuzzSelView メッセージ ハンドラー
void CFuzzSelView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);
	
	m_wndResizer.SetAnchor( IDC_COUNT_LABEL, ANCHOR_LEFT | ANCHOR_RIGHT| ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_LIST_BUTTON, ANCHOR_RIGHT | ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_FUZZ_SELECT_LIST, ANCHOR_ALL );

	m_wndResizer.InvokeOnResized();
}

BOOL CFuzzSelView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	if( m_wndFuzzSelectList.GetItemCount() )
	{
		nTotal = m_wndFuzzSelectList.GetItemCount();
		nChecked = GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount();
		nSelected = m_wndFuzzSelectList.GetSelectedCount();

		if( m_nTotal != nTotal || m_nChecked != nChecked || m_nSelected != nSelected )
		{
			m_nTotal = nTotal;
			m_nChecked = nChecked;
			m_nSelected = nSelected;
			return CTabChildView::OnUpdateStatusBar( m_nTotal, m_nChecked, m_nSelected );
		}
		return TRUE;
	}
	return FALSE;
}

void CFuzzSelView::OnBnClickedListButton()
{
	ViewFuzzlist();
}

LRESULT CFuzzSelView::OnExifAnalyzed( WPARAM wParam, LPARAM lParam )
{
	GetDocument()->GetUserDatas()->SetCheckedFuzzDataCount( 0 );
	m_wndFuzzSelectList.ClearList();
	return TRUE;
}

LRESULT CFuzzSelView::OnGroupDisp( WPARAM wParam, LPARAM lParam )
{
	GetDocument()->GetUserDatas()->SetCheckedFuzzDataCount( 0 );
	m_wndFuzzSelectList.ClearList();
	return TRUE;
}

LRESULT CFuzzSelView::OnFuzzListDisp( WPARAM wParam, LPARAM lParam )
{
	CWaitCursor WaitCursor;
	m_wndFuzzSelectList.SetListData( GetDocument()->GetUserDatas() );
	EnableUpdateStatusBar( TRUE );
	WaitCursor.Restore();
	return TRUE;
}

void CFuzzSelView::OnOpViewFuzzlist()
{
	ViewFuzzlist();
}

void CFuzzSelView::OnUpdateOpViewFuzzlist(CCmdUI *pCmdUI)
{
	BOOL bEnable = GetDocument()->GetUserDatas()->GetCheckedFealdEntryDataCount() && GetDocument()->GetUserDatas()->GetCheckedPatternDataCount();
	m_wndCreateListButton.EnableWindow( bEnable );
	pCmdUI->Enable( bEnable );
}

BOOL CFuzzSelView::ViewFuzzlist()
{
	m_wndFuzzSelectList.ClearList();
	AfxGetMainWnd()->PostMessage( WM_APP_CREATE_FUZZ_LIST, NULL, NULL );
	return TRUE;
}
