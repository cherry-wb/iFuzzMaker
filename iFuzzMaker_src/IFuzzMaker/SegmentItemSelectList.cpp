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

// SegmentItemSelectList.cpp : 実装ファイル
//
#include "stdafx.h"
#include "IFuzzMaker.h"
#include "SegmentItemSelectList.h"
#include "EndianConverter.h"

// CSegmentItemSelectList
IMPLEMENT_DYNAMIC(CSegmentItemSelectList, CGroupListCtrl)

CSegmentItemSelectList::CSegmentItemSelectList()
{
	m_lpUserDatas = NULL;
}

CSegmentItemSelectList::~CSegmentItemSelectList()
{
}

BEGIN_MESSAGE_MAP(CSegmentItemSelectList, CGroupListCtrl)
END_MESSAGE_MAP()

// CSegmentItemSelectList メッセージ ハンドラー
BOOL CSegmentItemSelectList::InitCtrl()
{
	CGroupListCtrl::InitCtrl();

	InsertColumn( COL_DISPNAME, _T("セグメント要素"), LVCFMT_LEFT, 200 );
	InsertColumn( COL_OFFSET, _T("オフセット"), LVCFMT_RIGHT, 140 );
	InsertColumn( COL_SIZE, _T("サイズ"), LVCFMT_RIGHT, 140 );
	InsertColumn( COL_DATA_VALUE, _T("データ値"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_DATA_HEX, _T("データ値(HEX)"), LVCFMT_LEFT, 250 );
	InsertColumn( COL_DESCRIPTION, _T("説明"), LVCFMT_LEFT, 300 );

	return TRUE;
}

BOOL CSegmentItemSelectList::SetListData( CUserDatas *lpUserDatas )
{
	int nGroup = 0;
	int nItem = 0;
	int nDataCount = 0;
	BOOL bEndianness = FALSE;
	CString szBuffer;
	CString szBufferHex;
	CSegmentData *lpSegmentData = NULL;
	CSegmentInfo *lpSegmentInfo = NULL;

	m_lpUserDatas = lpUserDatas;

	ClearList();

	EnableGroupView( TRUE );
	m_lpUserDatas->SetCheckedSegmentItemDataCount( 0 );
	for(int nSegmentCount=0; nSegmentCount<lpUserDatas->GetSegmentDataArray().GetSize(); nSegmentCount++ )
	{
		//	セグメント
		lpSegmentData = lpUserDatas->GetSegmentDataArray().GetAt( nSegmentCount );
		lpSegmentInfo = lpSegmentData->GetSegmentInfo();

		if( lpSegmentInfo )
		{
			if( lpSegmentInfo->IsAnalysisSegment() )
			{
				szBuffer.Format( _T("[%s] %s"), lpSegmentInfo->GetMarkerName(), lpSegmentInfo->GetSegmentName() );
				nGroup = InsertGroup( nGroup, szBuffer );
				for( int nSegmentItemDataCnt=0; nSegmentItemDataCnt<lpSegmentData->GetSegmentItemDataArray()->GetSize(); nSegmentItemDataCnt++ )
				{
					CSegmentItemData *lpSegmentItemData = lpSegmentData->GetSegmentItemDataArray()->GetAt(nSegmentItemDataCnt);
					CSegmentItemInfo *lpSegmentItemInfo = lpSegmentItemData->GetSegmentItemInfo();

					InsertItem( nItem, lpSegmentItemInfo->GetItemName(), 0, nGroup );

					SetItemData( nItem, (DWORD_PTR)lpSegmentItemData );
					SetCheck( nItem, lpSegmentItemData->GetCheck() );

					szBuffer.Format( _T("%u (0x%08X)"), lpSegmentItemData->GetOffset(), lpSegmentItemData->GetOffset() );
					SetItemText( nItem, COL_OFFSET, szBuffer );

					szBuffer.Format( _T("%u (0x%08X)"), lpSegmentItemData->GetSize(), lpSegmentItemData->GetSize() );
					SetItemText( nItem, COL_SIZE, szBuffer );

					int nSize = lpSegmentItemData->GetSize();
					if( !lpSegmentItemData->IsOverflow() )
					{
						CString szWork;
						CString szWorkHex;
						szBuffer = _T("");
						szBufferHex = _T("");
						switch( lpSegmentItemData->GetDataType() )
						{
						case CSegmentItemData::ITEM_TYPE_FILE:
							break;
						case CSegmentItemData::ITEM_TYPE_BYTE:
							for(nDataCount=0;nDataCount<nSize;nDataCount++)
							{
								szWork.Format( _T("%u "), lpSegmentItemData->GetData()[nDataCount] );
								szWorkHex.Format( _T("%02X "), lpSegmentItemData->GetData()[nDataCount] );
								szBuffer += szWork;
								szBufferHex += szWorkHex;
							}
							break;
						case CSegmentItemData::ITEM_TYPE_ASCII:
							for(nDataCount=0;nDataCount<nSize;nDataCount++)
							{
								szWork.Format( _T("%c"), lpSegmentItemData->GetData()[nDataCount] );
								szWorkHex.Format( _T("%02X "), lpSegmentItemData->GetData()[nDataCount] );
								szBuffer += szWork;
								szBufferHex += szWorkHex;
							}
							break;
						case CSegmentItemData::ITEM_TYPE_SHORT:
							//	2
							for(nDataCount=0;nDataCount<nSize/2;nDataCount++)
							{
								szWork.Format( _T("%u "), CEndianConverter::ConvertToShort( &lpSegmentItemData->GetData()[nDataCount*2] ) );
								szWorkHex.Format( _T("%02X %02X "), lpSegmentItemData->GetData()[nDataCount*2], lpSegmentItemData->GetData()[nDataCount*2+1] );
								szBuffer += szWork;
								szBufferHex += szWorkHex;
							}
							break;
						case CSegmentItemData::ITEM_TYPE_LONG:
							//	4
							for(nDataCount=0;nDataCount<nSize/4;nDataCount++)
							{
								szWork.Format( _T("%u "), CEndianConverter::ConvertToInteger( &lpSegmentItemData->GetData()[nDataCount*4] ) );
								szWorkHex.Format( _T("%02X %02X %02X %02X "), lpSegmentItemData->GetData()[nDataCount*4], lpSegmentItemData->GetData()[nDataCount*4+1], lpSegmentItemData->GetData()[nDataCount*4+2], lpSegmentItemData->GetData()[nDataCount*4+3] );
								szBuffer += szWork;
								szBufferHex += szWorkHex;
							}
							break;
						}
						SetItemText( nItem, COL_DATA_VALUE, szBuffer );
						SetItemText( nItem, COL_DATA_HEX, szBufferHex );
					}
					SetItemText( nItem, COL_DESCRIPTION, lpSegmentItemInfo->GetDescription() );
				}
				nGroup++;
			}
		}
	}
	return TRUE;
}

COLORREF CSegmentItemSelectList::OnGetCellTextColor( int nRow, int nColum )
{
	return CGroupListCtrl::OnGetCellTextColor( nRow, nColum );
}

HFONT CSegmentItemSelectList::OnGetCellFont( int nRow, int nColum, DWORD dwData )
{
	switch(nColum)
	{
	case COL_OFFSET:
	case COL_SIZE:
	case COL_DATA_VALUE:
	case COL_DATA_HEX:
		return m_GothicFont;
		break;
	}

	return CGroupListCtrl::OnGetCellFont( nRow, nColum, dwData );
}

void CSegmentItemSelectList::OnCheckItem( int nItem, BOOL bCheck )
{
	CSegmentItemData *lpSegmentItemData = (CSegmentItemData*)GetItemData( nItem );
	if( lpSegmentItemData )
		lpSegmentItemData->SetCheck( bCheck );
	if( m_lpUserDatas )
		m_lpUserDatas->SetCheckedSegmentItemDataCount( m_lpUserDatas->GetCheckedSegmentItemDataCount() + (bCheck?1:-1) );
}
