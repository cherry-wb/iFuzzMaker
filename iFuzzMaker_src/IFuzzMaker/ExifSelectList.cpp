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

// ExifSelectList.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "ExifSelectList.h"
#include "EndianConverter.h"
#include "AppMessage.h"

// CExifSelectList
IMPLEMENT_DYNAMIC(CExifSelectList, CGroupListCtrl)

CExifSelectList::CExifSelectList()
{
	m_lpUserDatas = NULL;
}

CExifSelectList::~CExifSelectList()
{
}


BEGIN_MESSAGE_MAP(CExifSelectList, CGroupListCtrl)
END_MESSAGE_MAP()


// CExifSelectList メッセージ ハンドラー
BOOL CExifSelectList::InitCtrl()
{
	CGroupListCtrl::InitCtrl();

	InsertColumn( COL_DISPNAME, _T("タグ名"), LVCFMT_LEFT, 200 );
	InsertColumn( COL_OFFSET, _T("オフセット"), LVCFMT_RIGHT, 140 );
	InsertColumn( COL_BINARY, _T("フィールドエントリ"), LVCFMT_LEFT, 180 );
	InsertColumn( COL_TAG, _T("タグ"), LVCFMT_LEFT, 40 );
	InsertColumn( COL_TYPE, _T("タイプ"), LVCFMT_LEFT, 80 );
	InsertColumn( COL_COUNT, _T("カウント"), LVCFMT_RIGHT, 50 );
	InsertColumn( COL_VALUE_OFFSET, _T("値/オフセット"), LVCFMT_RIGHT, 150 );

	InsertColumn( COL_DATA_OFFSET, _T("データオフセット"), LVCFMT_RIGHT, 120 );
	InsertColumn( COL_DATA_SIZE, _T("データサイズ"), LVCFMT_RIGHT, 80 );
	InsertColumn( COL_DATA_VALUE, _T("データ値"), LVCFMT_LEFT, 200 );

	return TRUE;
}

BOOL CExifSelectList::SetListData( CUserDatas *lpUserDatas )
{
	int nGroup = 0;
	int nItem = 0;
	int nDataCount = 0;
	BOOL bEndianness = FALSE;
	CString szBuffer;
	CSegmentData *lpSegmentData = NULL;
	CSegmentInfo *lpSegmentInfo = NULL;

	m_lpUserDatas = lpUserDatas;

	ClearList();

	EnableGroupView( TRUE );
	m_lpUserDatas->SetCheckedFealdEntryDataCount( 0 );
	for(int nSegmentCount=0; nSegmentCount<lpUserDatas->GetSegmentDataArray().GetSize(); nSegmentCount++ )
	{
		//	セグメント
		lpSegmentData = lpUserDatas->GetSegmentDataArray().GetAt( nSegmentCount );
		lpSegmentInfo = lpSegmentData->GetSegmentInfo();

		for( int nExifDataCnt=0; nExifDataCnt<lpSegmentData->GetExifDataArray()->GetSize(); nExifDataCnt++ )
		{
			CExifData* lpExifData = lpSegmentData->GetExifDataArray()->GetAt(nExifDataCnt);

			bEndianness = lpExifData->GetEndiannessType()==CExifData::BIG_ENDIAN?TRUE:FALSE;

			for( int ImageFileDirectoryDataCnt=0; ImageFileDirectoryDataCnt<lpExifData->GetImageFileDirectoryDataArray()->GetSize(); ImageFileDirectoryDataCnt++ )
			{
				//	IFD
				CImageFileDirectoryData* lpImageFileDirectoryData = lpExifData->GetImageFileDirectoryDataArray()->GetAt(ImageFileDirectoryDataCnt);
				CImageFileDirectoryInfo* lpImageFileDirectoryInfo = lpImageFileDirectoryData->GetImageFileDirectoryInfo();

				if( lpImageFileDirectoryInfo )
					szBuffer.Format( _T("[%s] %s"),
						lpImageFileDirectoryInfo->GetIfdName(),
						lpImageFileDirectoryInfo->GetDispName() );
				else
					szBuffer = _T("Unknown");
				nGroup = InsertGroup( ImageFileDirectoryDataCnt, szBuffer );

				for( int nFealdEntryDataCnt=0; nFealdEntryDataCnt<lpImageFileDirectoryData->GetFealdEntryDataArray()->GetSize(); nFealdEntryDataCnt++ )
				{
					//	FealdEntry
					CFealdEntryData *lpFealdEntryData = lpImageFileDirectoryData->GetFealdEntryDataArray()->GetAt(nFealdEntryDataCnt);
					CFealdEntryInfo *lpFealdEntryInfo = lpFealdEntryData->GetFealdEntryInfo();

					if( !lpFealdEntryInfo )
					{
						lpFealdEntryData->SetCheck( FALSE );
						continue;
					}
					InsertItem( nItem, lpFealdEntryInfo?lpFealdEntryInfo->GetTagName():_T("Unknown"), 0, ImageFileDirectoryDataCnt );

					SetItemData( nItem, (DWORD_PTR)lpFealdEntryData );

					SetCheck( nItem, lpFealdEntryData->GetCheck() );

					szBuffer.Format( _T("%u (0x%08X)"), lpFealdEntryData->GetOffset(), lpFealdEntryData->GetOffset() );
					SetItemText( nItem, COL_OFFSET, szBuffer );

					SetItemText( nItem, COL_TAG, lpFealdEntryData->GetTagID() );

					CTagTypeInfo *lpTagTypeInfo = lpFealdEntryData->GetTagTypeInfo();
					SetItemText( nItem, COL_TYPE, lpTagTypeInfo?lpTagTypeInfo->GetTagTypeName():_T("Unknown") );

					szBuffer.Format( _T("%u"), lpFealdEntryData->GetCount() );
					SetItemText( nItem, COL_COUNT, szBuffer );

					szBuffer.Format( _T("%u (0x%08X)"), lpFealdEntryData->GetValueOrOffset(), lpFealdEntryData->GetValueOrOffset() );
					SetItemText( nItem, COL_VALUE_OFFSET, szBuffer );

					if( lpFealdEntryData->IsOverflow() )
						continue;

					szBuffer.Format( _T("%02X%02X|%02X%02X|%02X%02X%02X%02X|%02X%02X%02X%02X"), 
						lpFealdEntryData->GetData()[0],
						lpFealdEntryData->GetData()[1],
						lpFealdEntryData->GetData()[2],
						lpFealdEntryData->GetData()[3],
						lpFealdEntryData->GetData()[4],
						lpFealdEntryData->GetData()[5],
						lpFealdEntryData->GetData()[6],
						lpFealdEntryData->GetData()[7],
						lpFealdEntryData->GetData()[8],
						lpFealdEntryData->GetData()[9],
						lpFealdEntryData->GetData()[10],
						lpFealdEntryData->GetData()[11] );
					SetItemText( nItem, COL_BINARY, szBuffer );
					for( int nTagDataCnt=0; nTagDataCnt<lpFealdEntryData->GetTagDataArray()->GetSize(); nTagDataCnt++ )
					{
						CTagData* lpTagData = lpFealdEntryData->GetTagDataArray()->GetAt( nTagDataCnt );
						
						szBuffer.Format( _T("%u (0x%08X)"), lpTagData->GetOffset(), lpTagData->GetOffset() );
						SetItemText( nItem, COL_DATA_OFFSET, szBuffer );

						szBuffer.Format( _T("%u"), lpTagData->GetSize() );
						SetItemText( nItem, COL_DATA_SIZE, szBuffer );

						//	値
						if(lpTagTypeInfo)
						{
							if( !lpTagData->IsOverflow() )
							{
								CString szWork;
								szBuffer = _T("");
								switch(lpTagTypeInfo->GetTagType())
								{
								case TAG_TYPE_BYTE:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%u "), lpTagData->GetData()[nDataCount] );
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_ASCII:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%c"), lpTagData->GetData()[nDataCount] );
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_SHORT:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%u "), CEndianConverter::ConvertToShort( &lpTagData->GetData()[nDataCount*2], bEndianness ) );
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_LONG:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%u "), CEndianConverter::ConvertToInteger( &lpTagData->GetData()[nDataCount*4], bEndianness ) );
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_RATIONAL:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%u/%u "), 
											CEndianConverter::ConvertToInteger( &lpTagData->GetData()[nDataCount*8], bEndianness ),
											CEndianConverter::ConvertToInteger( &lpTagData->GetData()[nDataCount*8+4], bEndianness ));
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_UNDEFINED:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%c"), lpTagData->GetData()[nDataCount] );
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_SLONG:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%d "), CEndianConverter::ConvertToInteger( &lpTagData->GetData()[nDataCount*4], bEndianness ) );
										szBuffer += szWork;
									}
									break;
								case TAG_TYPE_SRATIONAL:
									for(nDataCount=0;nDataCount<lpFealdEntryData->GetCount();nDataCount++)
									{
										szWork.Format( _T("%d/%d "), 
											CEndianConverter::ConvertToInteger( &lpTagData->GetData()[nDataCount*8], bEndianness ),
											CEndianConverter::ConvertToInteger( &lpTagData->GetData()[nDataCount*8+4], bEndianness ));
										szBuffer += szWork;
									}
									break;
								}
								SetItemText( nItem, COL_DATA_VALUE, szBuffer );
							}
						}
					}
					nItem++;
				}
			}
		}
	}
	SetSelectedItem( 0 );
	return TRUE;
}

COLORREF CExifSelectList::OnGetCellTextColor( int nRow, int nColum )
{
	return CGroupListCtrl::OnGetCellTextColor( nRow, nColum );
}

HFONT CExifSelectList::OnGetCellFont( int nRow, int nColum, DWORD dwData )
{
	switch(nColum)
	{
	case COL_OFFSET:
	case COL_TAG:
	case COL_COUNT:
	case COL_VALUE_OFFSET:
	case COL_BINARY:
	case COL_DATA_OFFSET:
	case COL_DATA_SIZE:
		return m_GothicFont;
		break;
	}

	return CGroupListCtrl::OnGetCellFont( nRow, nColum, dwData );
}

void CExifSelectList::OnCheckItem( int nItem, BOOL bCheck )
{
	CFealdEntryData *lpFealdEntryData = (CFealdEntryData*)GetItemData( nItem );
	if( lpFealdEntryData )
		lpFealdEntryData->SetCheck( bCheck );
	if( m_lpUserDatas )
		m_lpUserDatas->SetCheckedFealdEntryDataCount( m_lpUserDatas->GetCheckedFealdEntryDataCount() + (bCheck?1:-1) );
}
