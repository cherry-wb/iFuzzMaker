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


// PatternSelView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "PatternSelView.h"
#include "AppMessage.h"
#include "MainFrm.h"

// CPatternSelView
IMPLEMENT_DYNCREATE(CPatternSelView, CTabChildView)

CPatternSelView::CPatternSelView()
	: CTabChildView(CPatternSelView::IDD)
{
	m_bDoDataExchange = FALSE;
}

CPatternSelView::~CPatternSelView()
{
}

void CPatternSelView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATTERN_SELECT_LIST, m_wndPatternSelectList);
	DDX_Control(pDX, IDC_GROUP_BROWSE, m_wndGroupFileBrowseCtrl);
	DDX_Control(pDX, IDC_GROUP_BUTTON, m_wndGroupButton);
	
	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndGroupFileBrowseCtrl.EnableFileBrowseButton(NULL, _T("TEXT (*.txt)|*.txt|All files (*.*)|*.*|"));
		m_wndGroupFileBrowseCtrl.SetInitDirectory( ((CMainFrame*)AfxGetMainWnd())->GetFixedDatas()->GetAppConfig().GetPatternSelFolder() );
		m_wndPatternSelectList.InitCtrl();
	}
	m_wndGroupFileBrowseCtrl.SetWindowText( _T("") );
	m_wndPatternSelectList.ClearList();
	EnableUpdateStatusBar( FALSE );
}

BEGIN_MESSAGE_MAP(CPatternSelView, CTabChildView)
	ON_BN_CLICKED(IDC_GROUP_BUTTON, &CPatternSelView::OnBnClickedGroupButton)
	ON_MESSAGE(WM_APP_GROUP_DISP, OnGroupDisp)
	ON_COMMAND(ID_OP_READ_PATTERN, &CPatternSelView::OnOpReadPattern)
	ON_UPDATE_COMMAND_UI(ID_OP_READ_PATTERN, &CPatternSelView::OnUpdateOpReadPattern)
	ON_EN_CHANGE(IDC_GROUP_BROWSE, &CPatternSelView::OnEnChangeGroupBrowse)
END_MESSAGE_MAP()


// CPatternSelView 診断
#ifdef _DEBUG
void CPatternSelView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CPatternSelView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPatternSelView メッセージ ハンドラー
void CPatternSelView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);

	m_wndResizer.SetAnchor( IDC_GROUP_BROWSE, ANCHOR_HORIZONTALLY );
	m_wndResizer.SetAnchor( IDC_GROUP_BUTTON, ANCHOR_TOP | ANCHOR_RIGHT );
	m_wndResizer.SetAnchor( IDC_PATTERN_SELECT_LIST, ANCHOR_ALL );

	m_wndResizer.InvokeOnResized();
}

void CPatternSelView::OnBnClickedGroupButton()
{
	ReadPattern();
}

LRESULT CPatternSelView::OnGroupDisp( WPARAM wParam, LPARAM lParam )
{
	m_wndPatternSelectList.SetListData( GetDocument()->GetUserDatas() );
	EnableUpdateStatusBar( TRUE );
	//	前回のフォルダを記憶
	m_wndGroupFileBrowseCtrl.SetInitDirectory();
	return TRUE;
}

BOOL CPatternSelView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	if( m_wndPatternSelectList.GetItemCount() )
	{
		nTotal = m_wndPatternSelectList.GetItemCount();
		nChecked = GetDocument()->GetUserDatas()->GetCheckedPatternDataCount();
		nSelected = m_wndPatternSelectList.GetSelectedCount();

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


void CPatternSelView::OnOpReadPattern()
{
	ReadPattern();
}


void CPatternSelView::OnUpdateOpReadPattern(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TRUE );
}

BOOL CPatternSelView::ReadPattern()
{
	CString szFileName;

	m_wndGroupFileBrowseCtrl.GetWindowText( szFileName );

	if( !PathFileExists( szFileName ) )
	{
		MessageBox( _T("ファイルが存在しません"), _T("エラー"), MB_ICONHAND );
		return FALSE;
	}

	CString szDir;
	GetCurrentDirectory( 255, szDir.GetBufferSetLength(256) );

	GetDocument()->GetUserDatas()->SetGroupFileName( szFileName );
	
	m_wndPatternSelectList.ClearList();
	AfxGetMainWnd()->PostMessage( WM_APP_READ_GROUP, NULL, NULL );

	return TRUE;
}


void CPatternSelView::OnEnChangeGroupBrowse()
{
	if( m_wndGroupFileBrowseCtrl.IsBrowse() )
		ReadPattern();
}
