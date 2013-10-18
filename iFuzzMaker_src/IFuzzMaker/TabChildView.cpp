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

// TabChildView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "TabChildView.h"
#include "GroupListCtrl.h"
#include "MainFrm.h"
#include "AppMessage.h"

// CTabChildView
IMPLEMENT_DYNCREATE(CTabChildView, CFormView)

CTabChildView::CTabChildView()
	: CFormView(AFX_IDW_PANE_FIRST)
{
	m_bInitialView = FALSE;
	m_lpActivateView = NULL;
	m_nTotal = 0;
	m_nChecked = 0;
	m_nSelected = 0;
}

CTabChildView::CTabChildView(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{
	m_bInitialView = FALSE;
	m_lpActivateView = NULL;
	m_nTotal = 0;
	m_nChecked = 0;
	m_nSelected = 0;
}

CTabChildView::~CTabChildView()
{
}

void CTabChildView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	m_nTotal = 0;
	m_nChecked = 0;
	m_nSelected = 0;
	EnableUpdateStatusBar( FALSE );
}

BEGIN_MESSAGE_MAP(CTabChildView, CFormView)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CTabChildView::OnEditSelectAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CTabChildView::OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_COPY, &CTabChildView::OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, &CTabChildView::OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, &CTabChildView::OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, &CTabChildView::OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, &CTabChildView::OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, &CTabChildView::OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, &CTabChildView::OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CTabChildView::OnUpdateEditUndo)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTabChildView 診断
#ifdef _DEBUG
void CTabChildView::AssertValid() const
{
	CFormView::AssertValid();
}

CIFuzzMakerDoc* CTabChildView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIFuzzMakerDoc)));
	return (CIFuzzMakerDoc*)m_pDocument;
}

#ifndef _WIN32_WCE
void CTabChildView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CTabChildView メッセージ ハンドラー
void CTabChildView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTabChildView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
#endif
}

int CTabChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rc;
	GetClientRect(rc);
	m_sizeInitWnd.cy = rc.bottom;
	m_sizeInitWnd.cx = rc.right;
	
	SetScrollSizes(MM_TEXT, CSize(0, 0));
	return 0;
}

BOOL CTabChildView::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);
	pDC->FillRect( rectClient, &afxGlobalData.brBarFace );

	return TRUE;
}

HBRUSH CTabChildView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if ( nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN )
	{ 
		CString szBuffer;
		TCHAR* lpBuffer = szBuffer.GetBufferSetLength(256);
		if(lpBuffer)
		{
			if( GetClassName(pWnd->GetSafeHwnd(), lpBuffer, 255) > 0 )
			{

				if( szBuffer.Compare( _T("Static") ) == 0 ||
					szBuffer.Compare( _T("Button") ) == 0 ||
					szBuffer.Compare( _T("msctls_trackbar32") ) == 0 )
				{
					CRect rectClient;
					pWnd->GetClientRect(rectClient);
					pDC->FillRect( rectClient, &afxGlobalData.brBarFace );
					pDC->SetBkMode(TRANSPARENT);
					return(HBRUSH) GetStockObject(HOLLOW_BRUSH);
				}
			}
		}
	} 
	return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CTabChildView::OnInitialUpdate()
{
	if(!m_bInitialView)
	{
		m_bInitialView = TRUE;
		SetScrollSizes(MM_TEXT, CSize(0, 0));
		OnInitialView();
	}
	CFormView::OnInitialUpdate();
}

//	Public
BOOL CTabChildView::CreateForm( const RECT& rect, CWnd* pParentWnd, int nID , CCreateContext* lpContext )
{
	return CFormView::Create( NULL, NULL, WS_CHILD | WS_VISIBLE, rect, pParentWnd,  nID, lpContext );
}


void CTabChildView::OnInitialView()
{
}

void CTabChildView::OnEditSelectAll()
{
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		CGroupListCtrl* lpList = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->SetSel( 0, -1 );
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->SetSel( 0, -1 );
			break;
		case CTRL_LIST:
			lpList = (CGroupListCtrl*)lpWnd;
			lpList->SetSelectedItem( -1 );
			break;
		}
	}
}


void CTabChildView::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	BOOL nEnable = FALSE;
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		CMFCListCtrl* lpList = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			nEnable = lpBrowse->GetWindowTextLength() > 0;
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			nEnable = lpEdit->GetWindowTextLength() > 0;
			break;
		case CTRL_LIST:
			lpList = (CMFCListCtrl*)lpWnd;
			nEnable = lpList->GetItemCount() > 0;
			break;
		}
	}
	pCmdUI->Enable( nEnable );
}


void CTabChildView::OnEditCopy()
{
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->Copy();
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->Copy();
			break;
		}
	}
}


void CTabChildView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	BOOL nEnable = FALSE;
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		int nBeg = 0;
		int nEnd = 0;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->GetSel( nBeg, nEnd );
			nEnable = nBeg != nEnd;
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->GetSel( nBeg, nEnd );
			nEnable = nBeg != nEnd;
			break;
		}
	}
	pCmdUI->Enable( nEnable );
}


void CTabChildView::OnEditCut()
{
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->Cut();
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->Cut();
			break;
		}
	}
}


void CTabChildView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	BOOL nEnable = FALSE;
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		int nBeg = 0;
		int nEnd = 0;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->GetSel( nBeg, nEnd );
			nEnable = nBeg != nEnd;
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->GetSel( nBeg, nEnd );
			nEnable = nBeg != nEnd;
			break;
		}
	}
	pCmdUI->Enable( nEnable );
}


void CTabChildView::OnEditPaste()
{
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->Paste();
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->Paste();
			break;
		}
	}
}


void CTabChildView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	BOOL nEnable = FALSE;
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
		case CTRL_EDIT:
			nEnable = IsClipboardFormatAvailable(CF_TEXT);
			break;
		}
	}
	pCmdUI->Enable( nEnable );
}

void CTabChildView::OnEditUndo()
{
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			lpBrowse->Undo();
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			lpEdit->Undo();
			break;
		}
	}
}


void CTabChildView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	BOOL nEnable = FALSE;
	CWnd* lpWnd = GetFocus();
	if ( lpWnd )
	{
		CMFCEditBrowseCtrl* lpBrowse = NULL;
		CEdit* lpEdit = NULL;
		switch( GetActiveCtrl( lpWnd ) )
		{
		case CTRL_BROWSE:
			lpBrowse = (CMFCEditBrowseCtrl*)lpWnd;
			nEnable = lpBrowse->CanUndo();
			break;
		case CTRL_EDIT:
			lpEdit = (CEdit*)lpWnd;
			nEnable = lpEdit->CanUndo();
			break;
		}
	}
	pCmdUI->Enable( nEnable );
}


int CTabChildView::GetActiveCtrl( CWnd* pWnd )
{
	ASSERT( pWnd != NULL );
	if( pWnd )
	{
		HWND hWnd = pWnd->GetSafeHwnd();
		if (hWnd == NULL)
			return CTRL_UNKNOWN;

		CString szClassName;
		GetClassName(hWnd, szClassName.GetBufferSetLength(256), 255);
		if( _tcsicmp(szClassName, _T("Edit")) == 0 )
			return CTRL_EDIT;
		if( _tcsicmp(szClassName, _T("MFCEditBrowse")) == 0 )
			return CTRL_BROWSE;
		if( _tcsicmp(szClassName, _T("SysListView32")) == 0 )
			return CTRL_LIST;
	}
	return CTRL_UNKNOWN;

}

CView* CTabChildView::GetActivateView()
{
	CString szClassName;
	GetClassName(GetParent()->m_hWnd, szClassName.GetBufferSetLength(256), 255);

	if( szClassName.Find( _T("Afx:TabWnd") ) != 0 )
		return NULL;

	CMFCTabCtrl* lpMFCTabCtrl = (CMFCTabCtrl*)GetParent();
	int nActiveTab = lpMFCTabCtrl->GetActiveTab();
	if (nActiveTab < 0)
	{
		return NULL;
	}
	return DYNAMIC_DOWNCAST( CView, lpMFCTabCtrl->GetTabWnd(nActiveTab) );
}

void CTabChildView::EnableUpdateStatusBar( BOOL bEnable )
{
	KillTimer( TIMER_STATUSBAR );
	m_nTotal = 0;
	m_nChecked = 0;
	m_nSelected = 0;
	if( bEnable )
		SetTimer( TIMER_STATUSBAR, 0, NULL );
	else
		CTabChildView::OnUpdateStatusBar( 0, 0, 0 );
}

void CTabChildView::OnTimer(UINT_PTR nIDEvent)
{
	switch( nIDEvent )
	{
	case TIMER_STATUSBAR:
		KillTimer( TIMER_STATUSBAR );
		if( OnUpdateStatusBar( 0, 0, 0 ) )
			SetTimer( TIMER_STATUSBAR, UPDATE_STATUSBAR_TIMER, NULL );
		break;
	}

	CFormView::OnTimer(nIDEvent);
}

BOOL CTabChildView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	if( nTotal )
	{
		LPARAM lParam = MAKELONG(nChecked, nSelected);
		AfxGetMainWnd()->PostMessage( WM_APP_UPDATE_COUNT, nTotal, lParam );
	}else{
		AfxGetMainWnd()->PostMessage( WM_APP_UPDATE_COUNT, NULL, NULL );
	}
	return nTotal > 0;
}
