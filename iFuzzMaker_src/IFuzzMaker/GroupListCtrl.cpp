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

// GroupListCtrl.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "GroupListCtrl.h"

// CGroupListCtrl
IMPLEMENT_DYNAMIC(CGroupListCtrl, CMFCListCtrl)

CGroupListCtrl::CGroupListCtrl()
{
	m_bEnable = TRUE;
}

CGroupListCtrl::~CGroupListCtrl()
{
}

BEGIN_MESSAGE_MAP(CGroupListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CGroupListCtrl::OnNMRClick)
	ON_COMMAND(ID_SELECT_LIST_CHECK, &CGroupListCtrl::OnSelectListCheck)
	ON_UPDATE_COMMAND_UI(ID_SELECT_LIST_CHECK, &CGroupListCtrl::OnUpdateSelectListCheck)
	ON_COMMAND(ID_SELECT_LIST_UNCHECK, &CGroupListCtrl::OnSelectListUncheck)
	ON_UPDATE_COMMAND_UI(ID_SELECT_LIST_UNCHECK, &CGroupListCtrl::OnUpdateSelectListUncheck)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SELECT_ALL, &CGroupListCtrl::OnUpdateEditSelectAll)
	ON_COMMAND(ID_EDIT_SELECT_ALL, &CGroupListCtrl::OnEditSelectAll)
	ON_NOTIFY_REFLECT_EX(LVN_ITEMCHANGED, &CGroupListCtrl::OnLvnItemchanged)
END_MESSAGE_MAP()

// CGroupListCtrl メッセージ ハンドラー
void CGroupListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	if( GetExtendedStyle() & LVS_EX_CHECKBOXES )
	{
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		CPoint point;
		GetCursorPos(&point);
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_LIST_POPUP, point.x, point.y, this, TRUE);
	}
	*pResult = 0;
}

BOOL CGroupListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	BOOL bChanged = FALSE;
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	if( pNMLV->uChanged & LVIF_STATE )
	{
		if( ((pNMLV->uNewState & LVIS_STATEIMAGEMASK) == INDEXTOSTATEIMAGEMASK(2)) !=
			((pNMLV->uOldState & LVIS_STATEIMAGEMASK) == INDEXTOSTATEIMAGEMASK(2)) )
		{
			OnCheckItem( pNMLV->iItem, ((pNMLV->uNewState & LVIS_STATEIMAGEMASK) == INDEXTOSTATEIMAGEMASK(2)) );
			bChanged = TRUE;
		}
		if( (pNMLV->uNewState & LVIS_SELECTED) !=
			(pNMLV->uOldState & LVIS_SELECTED) )
		{
			OnSelectItem( pNMLV->iItem, (pNMLV->uNewState & LVIS_SELECTED) );
			bChanged = TRUE;
		}
	}

	*pResult = 0;
	return !m_bEnable;
}

void CGroupListCtrl::OnCheckItem( int nItem, BOOL bCheck )
{
}

void CGroupListCtrl::OnSelectItem( int nItem, BOOL bSelect )
{
}

BOOL CGroupListCtrl::InitCtrl()
{
	ModifyStyle( NULL, LVS_REPORT | LVS_SHOWSELALWAYS  );
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES /*| LVS_EX_AUTOSIZECOLUMNS*/ );

	LOGFONT lpLogfont;
	ZeroMemory( &lpLogfont, sizeof(LOGFONT) );
	GetParent()->GetFont()->GetLogFont( &lpLogfont );

	ZeroMemory( lpLogfont.lfFaceName, sizeof(lpLogfont.lfFaceName) );
	_tcscpy_s( lpLogfont.lfFaceName, sizeof(lpLogfont.lfFaceName)/sizeof(TCHAR), _T("ＭＳ ゴシック") );
	m_GothicFont.CreateFontIndirect( &lpLogfont );
	return TRUE;
}

BOOL CGroupListCtrl::ClearList()
{
	RemoveAllGroups();
	DeleteAllItems();
	return TRUE;
}

int CGroupListCtrl::InsertGroup( int nGroupID, CString szHeader )
{
	LVGROUP lvGroup;
	SecureZeroMemory( &lvGroup, sizeof(LVGROUP) );

	lvGroup.mask = LVGF_GROUPID | LVGF_HEADER | LVGF_STATE | LVGF_ALIGN;

	lvGroup.iGroupId = nGroupID;
	lvGroup.cbSize = sizeof(lvGroup);
	lvGroup.pszHeader = szHeader.GetBuffer();
	lvGroup.cchHeader = szHeader.GetLength();
	if( afxGlobalData.bIsWindows7 )
		lvGroup.state = LVGS_COLLAPSIBLE;
	else
		lvGroup.state = LVGS_COLLAPSED;
	lvGroup.uAlign = LVGA_HEADER_LEFT;
	return CMFCListCtrl::InsertGroup(nGroupID, &lvGroup );
}

int CGroupListCtrl::InsertItem( int nItem, CString szItem, int nImage, int nGroupID )
{
	LVITEM lvItem;
	SecureZeroMemory( &lvItem, sizeof(LVITEM) );

	CMFCListCtrl::InsertItem( nItem, szItem, nImage );

	lvItem.mask = LVIF_GROUPID;
	lvItem.iItem = nItem;
	lvItem.iSubItem = 0;
	lvItem.iGroupId = nGroupID;
	return CMFCListCtrl::SetItem( &lvItem );
}

void CGroupListCtrl::SetSelectedItemCheck( BOOL bCheck )
{
	EnableItemChangedEvent( FALSE );
	POSITION pos = GetFirstSelectedItemPosition();
	while(pos)
		SetCheck( GetNextSelectedItem(pos), bCheck );
	EnableItemChangedEvent( TRUE );
}

void CGroupListCtrl::SetItemImage( int nItem, int nImage )
{
	LVITEM lvItem;
	SecureZeroMemory( &lvItem, sizeof(LVITEM) );

	lvItem.iItem = nItem; 
	lvItem.mask = LVIF_IMAGE;
	lvItem.iImage = nImage;
	SetItem(&lvItem);
}

void CGroupListCtrl::OnSelectListCheck()
{
	SetSelectedItemCheck( TRUE );
}


void CGroupListCtrl::OnUpdateSelectListCheck(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( GetSelectedCount() );
}


void CGroupListCtrl::OnSelectListUncheck()
{
	SetSelectedItemCheck( FALSE );
}


void CGroupListCtrl::OnUpdateSelectListUncheck(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( GetSelectedCount() );
}


void CGroupListCtrl::OnUpdateEditSelectAll(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( GetItemCount() );
}


void CGroupListCtrl::OnEditSelectAll()
{
	SetSelectedItem( -1 );
}

void CGroupListCtrl::EnableItemChangedEvent( BOOL bEnable )
{
}

void CGroupListCtrl::SetSelectedItem( int nItem )
{
	int nState = LVIS_SELECTED | (nItem<0?NULL:LVIS_FOCUSED);
	EnableItemChangedEvent( FALSE );
	SetItemState(nItem, nState, nState);
	EnableItemChangedEvent( TRUE );
}
