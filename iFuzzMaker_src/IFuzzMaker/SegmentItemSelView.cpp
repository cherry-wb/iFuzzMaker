//================================================================================
//  �Ɨ��s���@�l��񏈗����i�@�\ (IPA)
//  - Information-technology Promotion Agency, Japan -
//
//                                                    �Ɨ��s���@�l��񏈗����i�@�\
//                                                   �Z�p�{�� �Z�L�����e�B�Z���^�[
//                                                ���Z�L�����e�B�Z�p���{���g���[
//
//      -- JPEG �e�X�g�x���c�[�� iFuzzMaker  --
//                                                                Date�F2013/07/30
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

// SegmentItemSelView.cpp : �����t�@�C��
//
#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "SegmentItemSelView.h"
#include "AppMessage.h"

// CSegmentItemSelView
IMPLEMENT_DYNCREATE(CSegmentItemSelView, CTabChildView)

CSegmentItemSelView::CSegmentItemSelView()
	: CTabChildView(CSegmentItemSelView::IDD)
{
	m_bDoDataExchange = FALSE;
}

CSegmentItemSelView::~CSegmentItemSelView()
{
}

void CSegmentItemSelView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITEM_SELECT_LIST, m_wndSegmentItemSelectList);

	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndSegmentItemSelectList.InitCtrl();
	}
	m_wndSegmentItemSelectList.ClearList();
	EnableUpdateStatusBar( FALSE );

}

BEGIN_MESSAGE_MAP(CSegmentItemSelView, CTabChildView)
	ON_MESSAGE(WM_APP_EXIF_ANALYZED, OnExifAnalyzed)
END_MESSAGE_MAP()

// CSegmentItemSelView �f�f
#ifdef _DEBUG
void CSegmentItemSelView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CSegmentItemSelView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG

// CSegmentItemSelView ���b�Z�[�W �n���h���[
void CSegmentItemSelView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);

	m_wndResizer.SetAnchor( IDC_ITEM_SELECT_LIST, ANCHOR_ALL );

	m_wndResizer.InvokeOnResized();
}

BOOL CSegmentItemSelView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	if( m_wndSegmentItemSelectList.GetItemCount() )
	{
		nTotal = m_wndSegmentItemSelectList.GetItemCount();
		nChecked = GetDocument()->GetUserDatas()->GetCheckedSegmentItemDataCount();
		nSelected = m_wndSegmentItemSelectList.GetSelectedCount();

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

LRESULT CSegmentItemSelView::OnExifAnalyzed( WPARAM wParam, LPARAM lParam )
{
	m_wndSegmentItemSelectList.SetListData( GetDocument()->GetUserDatas() );
	EnableUpdateStatusBar( TRUE );
	return TRUE;
}