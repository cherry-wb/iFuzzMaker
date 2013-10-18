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

// ExifListView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "ExifListView.h"
#include "AppMessage.h"


// CExifListView
IMPLEMENT_DYNCREATE(CExifListView, CTabChildView)

CExifListView::CExifListView()
	: CTabChildView(CExifListView::IDD)
{
	m_lpExifInfoView = NULL;
	m_lpExifInfo = NULL;
	m_bDoDataExchange = FALSE;
}

CExifListView::~CExifListView()
{
}

void CExifListView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EXIF_SELECT_LIST, m_wndExifSelectList);

	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndExifSelectList.InitCtrl();
	}
	m_wndExifSelectList.ClearList();
	m_lpExifInfo = NULL;
}

BEGIN_MESSAGE_MAP(CExifListView, CTabChildView)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_EXIF_SELECT_LIST, &CExifListView::OnItemchangedExifSelectList)
	ON_MESSAGE(WM_APP_EXIF_ANALYZED, OnExifAnalyzed)
END_MESSAGE_MAP()


// CExifListView 診断
#ifdef _DEBUG
void CExifListView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CExifListView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG

// CExifListView メッセージ ハンドラー
void CExifListView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);

	m_wndResizer.SetAnchor( IDC_EXIF_SELECT_LIST, ANCHOR_ALL );

	m_wndResizer.InvokeOnResized();

	GetActivateView();
}

LRESULT CExifListView::OnExifAnalyzed( WPARAM wParam, LPARAM lParam )
{
	m_lpExifInfoView->SendMessage( WM_APP_EXIF_SELECT, NULL, NULL );
	m_wndExifSelectList.SetListData( GetDocument()->GetUserDatas() );
	EnableUpdateStatusBar( TRUE );
	return TRUE;
}

BOOL CExifListView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	m_lpExifInfoView->RedrawWindow();
	if( m_wndExifSelectList.GetItemCount() )
	{
		nTotal = m_wndExifSelectList.GetItemCount();
		nChecked = GetDocument()->GetUserDatas()->GetCheckedFealdEntryDataCount();
		nSelected = m_wndExifSelectList.GetSelectedCount();

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

void CExifListView::OnItemchangedExifSelectList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	int nItem = m_wndExifSelectList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED | LVNI_FOCUSED);
	if( nItem >= 0 )
	{
		LPARAM lParam = (LPARAM)m_wndExifSelectList.GetItemData( nItem );
		if( m_lpExifInfo != lParam )
		{
			m_lpExifInfoView->SendMessage( WM_APP_EXIF_SELECT, NULL, lParam );
			m_lpExifInfo = lParam;
		}
	}
	*pResult = 0;
}

void CExifListView::SetExifInfoView(CExifInfoView* lpExifInfoView)
{
	m_lpExifInfoView = lpExifInfoView;
}

CExifInfoView* CExifListView::GetExifInfoView()
{
	return m_lpExifInfoView;
}
