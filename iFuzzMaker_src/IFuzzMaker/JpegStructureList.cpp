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

// JpegStructureList.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "JpegStructureList.h"

// CJpegStructureList
IMPLEMENT_DYNAMIC(CJpegStructureList, CColumnTreeCtrl)

CJpegStructureList::CJpegStructureList()
{

}

CJpegStructureList::~CJpegStructureList()
{
}


BEGIN_MESSAGE_MAP(CJpegStructureList, CColumnTreeCtrl)
END_MESSAGE_MAP()

// CJpegStructureList メッセージ ハンドラー
BOOL CJpegStructureList::InitCtrl()
{
	ModifyStyle( NULL, WS_CLIPCHILDREN );

	UINT uTreeStyle = TVS_HASBUTTONS | /*TVS_HASLINES |*/ TVS_LINESATROOT | TVS_FULLROWSELECT | TVS_SHOWSELALWAYS;
	GetTreeCtrl().ModifyStyle(0,uTreeStyle);

	InsertColumn( COL_NAME, _T("セグメント/タグ"), LVCFMT_LEFT, 240 );
	InsertColumn( COL_OFFSET, _T("オフセット"), LVCFMT_RIGHT, 150 );
	InsertColumn( COL_SIZE, _T("サイズ/エントリ数"), LVCFMT_RIGHT, 150 );
	InsertColumn( COL_MARKER, _T("マーカー/タグ"), LVCFMT_LEFT, 90 );
	InsertColumn( COL_DESCRIPTION, _T("名称"), LVCFMT_LEFT, 200 );
	
	m_ImageList.Create(16, 16, ILC_COLOR24|ILC_MASK, 0, 0);
	CBitmap bmp;
    bmp.LoadBitmap( IDB_JPEG_STRUCTURE_BITMAP );
    m_ImageList.Add( &bmp, RGB(255, 0, 255) );
	GetTreeCtrl().SetImageList( &m_ImageList, TVSIL_NORMAL );

	LOGFONT lpLogfont;
	ZeroMemory( &lpLogfont, sizeof(LOGFONT) );

	GetParent()->GetFont()->GetLogFont( &lpLogfont );

	ZeroMemory( lpLogfont.lfFaceName, sizeof(lpLogfont.lfFaceName) );
	_tcscpy_s( lpLogfont.lfFaceName, sizeof(lpLogfont.lfFaceName)/sizeof(TCHAR), _T("ＭＳ ゴシック") );
	m_GothicFont.CreateFontIndirect( &lpLogfont );

	return TRUE;
}

BOOL CJpegStructureList::SetListData( CUserDatas *lpUserDatas )
{
	int nIcon = 0; 
	int nRow = 0;
	int nSegmentCount = 0;
	CSegmentData *lpSegmentData = NULL;
	CSegmentInfo *lpSegmentInfo = NULL;

	ClearList();

	LockWindowUpdate();
	GetTreeCtrl().LockWindowUpdate();

	CString szWork;
	for(nSegmentCount=0; nSegmentCount<lpUserDatas->GetSegmentDataArray().GetSize(); nSegmentCount++ )
	{
		//	セグメント
		lpSegmentData = lpUserDatas->GetSegmentDataArray().GetAt( nSegmentCount );
		lpSegmentInfo = lpSegmentData->GetSegmentInfo();

		HTREEITEM hRoot = NULL;
		HTREEITEM hIfd = NULL;
		HTREEITEM hItem = NULL;
	
		if( lpSegmentData->GetDataType() == CSegmentData::DATATYPE_MARKER )
		{
			hRoot = GetTreeCtrl().InsertItem( lpSegmentInfo->GetMarkerName(), ICON_SEGMENT, ICON_SEGMENT );
			GetTreeCtrl().SetItemData( hRoot, (DWORD_PTR)lpSegmentInfo );
		}else if( lpSegmentData->GetDataType() == CSegmentData::DATATYPE_IMAGE ){
			hRoot = GetTreeCtrl().InsertItem( _T("Image"), ICON_IMAGE, ICON_IMAGE );
			GetTreeCtrl().SetItemData( hRoot, (DWORD_PTR)lpSegmentInfo );
		}else{
			hRoot = GetTreeCtrl().InsertItem( _T("Unknown"), ICON_UNKNOWN_SEGMENT, ICON_UNKNOWN_SEGMENT );
			GetTreeCtrl().SetItemData( hRoot, NULL );
		}

		szWork.Format( _T("%d (0x%08X)"), lpSegmentData->GetOffset(), lpSegmentData->GetOffset() );
		SetItemText( hRoot, COL_OFFSET, szWork );

		szWork.Format( _T("%d (0x%08X)"), lpSegmentData->GetSize(), lpSegmentData->GetSize() );
		SetItemText( hRoot, COL_SIZE, szWork );

		if( lpSegmentData->GetDataType() == CSegmentData::DATATYPE_MARKER )
		{
			szWork = lpSegmentInfo->GetMarker();
		}else if( lpSegmentData->GetDataType() == CSegmentData::DATATYPE_IMAGE ){
			szWork = _T("");
		}else{
			szWork = _T("");
		}
		SetItemText( hRoot, COL_MARKER, szWork );

		if( lpSegmentData->GetDataType() == CSegmentData::DATATYPE_MARKER )
		{
			szWork = lpSegmentInfo->GetSegmentName();
		}else if( lpSegmentData->GetDataType() == CSegmentData::DATATYPE_IMAGE ){
			szWork = _T("画像データ");
		}else{
			szWork = _T("");
		}
		SetItemText( hRoot, COL_DESCRIPTION, szWork );

		for( int nExifDataCnt=0; nExifDataCnt<lpSegmentData->GetExifDataArray()->GetSize(); nExifDataCnt++ )
		{
			CExifData* lpExifData = lpSegmentData->GetExifDataArray()->GetAt(nExifDataCnt);


			for( int ImageFileDirectoryDataCnt=0; ImageFileDirectoryDataCnt<lpExifData->GetImageFileDirectoryDataArray()->GetSize(); ImageFileDirectoryDataCnt++ )
			{
				//	IFD
				CImageFileDirectoryData* lpImageFileDirectoryData = lpExifData->GetImageFileDirectoryDataArray()->GetAt(ImageFileDirectoryDataCnt);
				CImageFileDirectoryInfo* lpImageFileDirectoryInfo = lpImageFileDirectoryData->GetImageFileDirectoryInfo();

				if(lpImageFileDirectoryInfo)
				{
					hIfd = GetTreeCtrl().InsertItem( lpImageFileDirectoryInfo->GetIfdName(), ICON_IFD, ICON_IFD, hRoot );
					GetTreeCtrl().SetItemData( hIfd, (DWORD_PTR)lpImageFileDirectoryData );
				}else{
					hIfd = GetTreeCtrl().InsertItem( _T("Unknown"), ICON_UNKNOWN_IFD, ICON_UNKNOWN_IFD, hRoot );
					GetTreeCtrl().SetItemData( hIfd, NULL );
				}

				szWork.Format( _T("%d (0x%08X)"), lpImageFileDirectoryData->GetOffset(), lpImageFileDirectoryData->GetOffset() );
				SetItemText( hIfd, COL_OFFSET, szWork );

				szWork.Format( _T("%d (0x%08X)"), lpImageFileDirectoryData->GetEntryCount(), lpImageFileDirectoryData->GetEntryCount() );
				SetItemText( hIfd, COL_SIZE, szWork );

				if( lpImageFileDirectoryInfo && lpImageFileDirectoryInfo->GetOrder() == _T("n") )
				{
					SetItemText( hIfd, COL_MARKER, lpImageFileDirectoryInfo->GetIfdID() );
					SetItemText( hIfd, COL_DESCRIPTION, lpImageFileDirectoryInfo->GetDispName() );
				}else if( lpImageFileDirectoryInfo && (lpImageFileDirectoryInfo->GetOrder() == _T("1") || lpImageFileDirectoryInfo->GetOrder() == _T("2") ) )
				{
					SetItemText( hIfd, COL_DESCRIPTION, lpImageFileDirectoryInfo->GetDispName() );
				}

				for( int nFealdEntryDataCnt=0; nFealdEntryDataCnt<lpImageFileDirectoryData->GetFealdEntryDataArray()->GetSize(); nFealdEntryDataCnt++ )
				{
					//	FealdEntry
					CFealdEntryData *lpFealdEntryData = lpImageFileDirectoryData->GetFealdEntryDataArray()->GetAt(nFealdEntryDataCnt);
					CFealdEntryInfo *lpFealdEntryInfo = lpFealdEntryData->GetFealdEntryInfo();

					if(lpFealdEntryInfo)
					{
						hItem = GetTreeCtrl().InsertItem( lpFealdEntryInfo->GetTagName(), ICON_FEALDENTRY, ICON_FEALDENTRY, hIfd );
						GetTreeCtrl().SetItemData( hItem, (DWORD_PTR)lpFealdEntryData );
					}else{
						hItem = GetTreeCtrl().InsertItem( _T("Unknown"), ICON_UNKNOWN_FEALDENTRY, ICON_UNKNOWN_FEALDENTRY, hIfd );
						GetTreeCtrl().SetItemData( hItem, NULL );
					}

					szWork.Format( _T("%d (0x%08X)"), lpFealdEntryData->GetOffset(), lpFealdEntryData->GetOffset() );
					SetItemText( hItem, COL_OFFSET, szWork );

					szWork.Format( _T("%d (0x%08X)"), lpFealdEntryData->GetSize(), lpFealdEntryData->GetSize() );
					SetItemText( hItem, COL_SIZE, szWork );

					if(lpFealdEntryInfo)
					{
						SetItemText( hItem, COL_MARKER, lpFealdEntryInfo->GetTagID() );
						SetItemText( hItem, COL_DESCRIPTION, lpFealdEntryInfo->GetDispName() );
					}else{
						SetItemText( hItem, COL_MARKER, lpFealdEntryData->GetTagID() );
					}

				}
				GetTreeCtrl().Expand( hIfd, TVE_EXPAND );
			}
			GetTreeCtrl().Expand( hRoot, TVE_EXPAND );
		}
	}

	GetTreeCtrl().SelectItem( GetTreeCtrl().GetRootItem() );
	
	UnlockWindowUpdate();
	GetTreeCtrl().UnlockWindowUpdate();

	return TRUE;
}

BOOL CJpegStructureList::ClearList()
{
	LockWindowUpdate();
	GetTreeCtrl().LockWindowUpdate();
	GetTreeCtrl().DeleteAllItems();
	UnlockWindowUpdate();
	GetTreeCtrl().UnlockWindowUpdate();

	return TRUE;
}

COLORREF CJpegStructureList::OnGetCellTextColor( HTREEITEM hItem, int nColumn )
{
	HTREEITEM hSelectedItem = GetTreeCtrl().GetSelectedItem();
	if( !GetTreeCtrl().GetItemData( hItem ) )
		return( hSelectedItem==hItem?RGB(255,255,255):RGB(192,192,192) );
	return CColumnTreeCtrl::OnGetCellTextColor( hItem, nColumn );
}

CFont* CJpegStructureList::OnGetCellFont( HTREEITEM hItem, int nColumn )
{
	switch(nColumn)
	{
	case COL_OFFSET:
	case COL_SIZE:
	case COL_MARKER:
		return &m_GothicFont;
		break;
	}
	return CColumnTreeCtrl::OnGetCellFont( hItem, nColumn );
}
