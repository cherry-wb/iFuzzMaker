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

// ExifInfoView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "ExifInfoView.h"
#include "AppMessage.h"
#include "FealdEntryData.h"

// CExifInfoView

IMPLEMENT_DYNCREATE(CExifInfoView, CTabChildView)

CExifInfoView::CExifInfoView()
	: CTabChildView(CExifInfoView::IDD)
{
	m_bDoDataExchange = FALSE;
}

CExifInfoView::~CExifInfoView()
{
}

void CExifInfoView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAG_LABEL, m_wndTagLabel);
	DDX_Control(pDX, IDC_TAG_EDIT, m_wndTagEdit);
	DDX_Control(pDX, IDC_TAGNAME_LABEL, m_wndTagNameLabel);
	DDX_Control(pDX, IDC_TAGNAME_EDIT, m_wndTagNameEdit);
	DDX_Control(pDX, IDC_DESCRIPTION_LABEL, m_wndDescriptionLabel);
	DDX_Control(pDX, IDC_DESCRIPTION_EDIT, m_wndDescriptionEdit);
	DDX_Control(pDX, IDC_TAGID_LABEL, m_wndTagIDLabel);
	DDX_Control(pDX, IDC_TAGID_EDIT, m_wndTagIDEdit);
	DDX_Control(pDX, IDC_TYPE_LABEL, m_wndTypeLabel);
	DDX_Control(pDX, IDC_TYPE_EDIT, m_wndTypeEdit);
	DDX_Control(pDX, IDC_COUNT_LABEL, m_wndCountLabel);
	DDX_Control(pDX, IDC_COUNT_EDIT, m_wndCountEdit);
	DDX_Control(pDX, IDC_DEFAULT_LABEL, m_wndDefaultLabel);
	DDX_Control(pDX, IDC_DEFAULT_EDIT, m_wndDefaultEdit);
	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		SetScrollSizes(MM_TEXT, CSize(0, m_sizeInitWnd.cy));
	}
	OnExifSelect( NULL, NULL );
}

BEGIN_MESSAGE_MAP(CExifInfoView, CTabChildView)
	ON_MESSAGE(WM_APP_EXIF_SELECT, OnExifSelect)
END_MESSAGE_MAP()


// CExifInfoView 診断

#ifdef _DEBUG
void CExifInfoView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CExifInfoView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG

// CExifInfoView メッセージ ハンドラー
void CExifInfoView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);

	m_wndResizer.SetAnchor( IDC_TAG_LABEL, ANCHOR_LEFT | ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_TAG_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP );

	m_wndResizer.SetAnchor( IDC_TAGNAME_LABEL, ANCHOR_LEFT | ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_TAGNAME_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_TOP );

	m_wndResizer.SetAnchor( IDC_DESCRIPTION_LABEL, ANCHOR_LEFT | ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_DESCRIPTION_EDIT, ANCHOR_ALL );

	m_wndResizer.SetAnchor( IDC_TAGID_LABEL, ANCHOR_LEFT | ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_TAGID_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_BOTTOM );

	m_wndResizer.SetAnchor( IDC_TYPE_LABEL, ANCHOR_LEFT | ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_TYPE_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_BOTTOM );

	m_wndResizer.SetAnchor( IDC_COUNT_LABEL, ANCHOR_LEFT | ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_COUNT_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_BOTTOM );

	m_wndResizer.SetAnchor( IDC_DEFAULT_LABEL, ANCHOR_LEFT | ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_DEFAULT_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT | ANCHOR_BOTTOM );

	m_wndResizer.InvokeOnResized();
}

LRESULT CExifInfoView::OnExifSelect( WPARAM wParam, LPARAM lParam )
{
	CString szBuff;
	CFealdEntryData *lpFealdEntryData = (CFealdEntryData*)lParam;

	if( lpFealdEntryData )
	{

		CFealdEntryInfo *lpFealdEntryInfo = lpFealdEntryData->GetFealdEntryInfo();
		CTagTypeInfo *lpTagTypeInfo = lpFealdEntryData->GetTagTypeInfo();
	
		m_wndTagEdit.SetWindowText( lpFealdEntryInfo?lpFealdEntryInfo->GetDispName():_T("") ); 
		m_wndTagNameEdit.SetWindowText( lpFealdEntryInfo?lpFealdEntryInfo->GetTagName():_T("") ); 
		m_wndDescriptionEdit.SetWindowText( lpFealdEntryInfo?lpFealdEntryInfo->GetDiscription()+_T("\r\n\r\n")+lpFealdEntryInfo->GetValues():_T("") ); 
		m_wndTagIDEdit.SetWindowText( lpFealdEntryData?lpFealdEntryData->GetTagID():_T("") ); 
	
		if( lpFealdEntryData )
			szBuff = lpFealdEntryData->GetTagID();
		else
			szBuff = _T("");
		m_wndTagIDEdit.SetWindowText( szBuff ); 

		if( lpFealdEntryData && lpTagTypeInfo )
			szBuff.Format( _T("%d（0x%08X）：%s"), lpFealdEntryData->GetType(), lpFealdEntryData->GetType(), lpTagTypeInfo->GetTagTypeName());
		else if( lpFealdEntryData )
			szBuff.Format( _T("%d（0x%08X）：Unknown"), lpFealdEntryData->GetType(), lpFealdEntryData->GetType() );
		else
			szBuff = _T("");
		m_wndTypeEdit.SetWindowText( szBuff ); 

		if( lpFealdEntryData )
			szBuff.Format( _T("%d（0x%08X）"), lpFealdEntryData->GetCount(), lpFealdEntryData->GetCount() );
		else
			szBuff = _T("");
		m_wndCountEdit.SetWindowText( szBuff ); 

		m_wndDefaultEdit.SetWindowText( lpFealdEntryInfo?lpFealdEntryInfo->GetDefault():_T("") ); 
	}else{
		m_wndTagEdit.SetWindowText( _T("") );
		m_wndTagNameEdit.SetWindowText( _T("") );
		m_wndDescriptionEdit.SetWindowText( _T("") );
		m_wndTagIDEdit.SetWindowText( _T("") );
		m_wndTypeEdit.SetWindowText( _T("") );
		m_wndCountEdit.SetWindowText( _T("") );
		m_wndDefaultEdit.SetWindowText( _T("") );
	}
	return TRUE;
}