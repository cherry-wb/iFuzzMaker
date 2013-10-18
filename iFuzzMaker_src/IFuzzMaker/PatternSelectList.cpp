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


// PatternSelectList.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "PatternSelectList.h"
#include "AppMessage.h"

// CPatternSelectList
IMPLEMENT_DYNAMIC(CPatternSelectList, CGroupListCtrl)

CPatternSelectList::CPatternSelectList()
{
	m_lpUserDatas = NULL;
}

CPatternSelectList::~CPatternSelectList()
{
}

BEGIN_MESSAGE_MAP(CPatternSelectList, CGroupListCtrl)
END_MESSAGE_MAP()


// CPatternSelectList メッセージ ハンドラー
BOOL CPatternSelectList::InitCtrl()
{
	CGroupListCtrl::InitCtrl();

	InsertColumn( COL_DISPNAME, _T("ルール名"), LVCFMT_LEFT, 150 );
	InsertColumn( COL_DATATYPE, _T("データ形式"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_VALUE, _T("値"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_REPEAT, _T("繰返し数"), LVCFMT_RIGHT, 60 );
	InsertColumn( COL_WRITEMODE, _T("書換モード"), LVCFMT_LEFT, 70 );
	InsertColumn( COL_FUZZAREA, _T("変更箇所"), LVCFMT_LEFT, 80 );
	InsertColumn( COL_SEARCHFIELD, _T("変更箇所指定"), LVCFMT_LEFT, 90 );
	InsertColumn( COL_FIELDKEY, _T("対象変更箇所"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_DESCRIPTION, _T("説明"), LVCFMT_LEFT, 200 );

	return TRUE;
}

BOOL CPatternSelectList::SetListData( CUserDatas *lpUserDatas )
{
	int nGroup = 0;
	int nItem = 0;
	CString szBuffer;

	m_lpUserDatas = lpUserDatas;

	ClearList();
	EnableGroupView( TRUE );
	m_lpUserDatas->SetCheckedPatternDataCount( 0 );
	for( int nPatternGroupData=0; nPatternGroupData<lpUserDatas->GetPatternGroupDataArray().GetSize(); nPatternGroupData++ )
	{
		CPatternGroupData* lpPatternGroupData = lpUserDatas->GetPatternGroupDataArray().GetAt(nPatternGroupData);
		nGroup = InsertGroup( nPatternGroupData, lpPatternGroupData->GetDispName() );

		for( int nPatternData=0; nPatternData<lpPatternGroupData->GetPatternDataArray()->GetSize(); nPatternData++ )
		{
			CPatternData* lpPatternData = lpPatternGroupData->GetPatternDataArray()->GetAt(nPatternData);
			InsertItem( nItem, lpPatternData->GetDispName(), 0, nGroup );

			SetItemData( nItem, (DWORD_PTR)lpPatternData );

			SetCheck( nItem, lpPatternData->GetCheck() );

			switch(lpPatternData->GetDataType())
			{
			case CPatternData::DATATYPE_TEXT:
				szBuffer = _T("テキスト");
				break;
			case CPatternData::DATATYPE_DEC_8:
				szBuffer = _T("10進数(8)");
				break;
			case CPatternData::DATATYPE_DEC_16_LITTLE:
				szBuffer = _T("10進数(16II)");
				break;
			case CPatternData::DATATYPE_DEC_16_BIG:
				szBuffer = _T("10進数(16MM)");
				break;
			case CPatternData::DATATYPE_DEC_32_LITTLE:
				szBuffer = _T("10進数(32II)");
				break;
			case CPatternData::DATATYPE_DEC_32_BIG:
				szBuffer = _T("10進数(32MM)");
				break;
			case CPatternData::DATATYPE_HEX:
				szBuffer = _T("16進数");
				break;
			case CPatternData::DATATYPE_BIN:
				szBuffer = _T("ファイル(バイナリ)");
				break;
			default:
				szBuffer = _T("不明");
			}
			SetItemText( nItem, COL_DATATYPE, szBuffer );

			CString szWork;
			szBuffer = _T("");
			switch(lpPatternData->GetDataType())
			{
			case CPatternData::DATATYPE_TEXT:
				szBuffer = lpPatternData->GetValue();
				break;
			case CPatternData::DATATYPE_DEC_8:
			case CPatternData::DATATYPE_DEC_16_LITTLE:
			case CPatternData::DATATYPE_DEC_16_BIG:
			case CPatternData::DATATYPE_DEC_32_LITTLE:
			case CPatternData::DATATYPE_DEC_32_BIG:
				szBuffer = lpPatternData->GetValue();
				break;
			case CPatternData::DATATYPE_HEX:
				szBuffer = lpPatternData->GetValue();
				break;
			case CPatternData::DATATYPE_BIN:
				for( int nReadCnt=0; nReadCnt<lpPatternData->GetBinaryDataArray()->GetSize(); nReadCnt++ )
				{
					szWork.Format( _T("%02X "), lpPatternData->GetBinaryDataArray()->GetAt(nReadCnt) );
					szBuffer += szWork;
				}
				break;
			default:
				szBuffer = _T("");
			}
			SetItemText( nItem, COL_VALUE, szBuffer );

			if( lpPatternData->GetRepeat() == 0 )
				szBuffer = _T("n");
			else
				szBuffer.Format( _T("%d"), lpPatternData->GetRepeat() );
			SetItemText( nItem, COL_REPEAT, szBuffer );

			switch( lpPatternData->GetWriteMode() )
			{
			case CPatternData::WRITEMODE_REPLACE:
				szBuffer = _T("置換");
				break;
			case CPatternData::WRITEMODE_OVERWRITE:
				szBuffer = _T("上書");
				break;
			case CPatternData::WRITEMODE_INSERT:
				szBuffer = _T("挿入");
				break;
			}
			SetItemText( nItem, COL_WRITEMODE, szBuffer );

			switch(lpPatternData->GetFuzzArea())
			{
			case CPatternData::FUZZAREA_TAG:
				szBuffer = _T("タグ");
				break;
			case CPatternData::FUZZAREA_TYPE:
				szBuffer = _T("タイプ");
				break;
			case CPatternData::FUZZAREA_COUNT:
				szBuffer = _T("カウント");
				break;
			case CPatternData::FUZZAREA_VALUE:
				szBuffer = _T("値");
				break;
			case CPatternData::FUZZAREA_OFFSET:
				szBuffer = _T("オフセット");
				break;
			case CPatternData::FUZZAREA_SEGMENT:
				szBuffer = _T("セグメント要素");
				break;
			case CPatternData::FUZZAREA_FILE:
				szBuffer = _T("ファイル指定位置");
				break;
			}
			SetItemText( nItem, COL_FUZZAREA, szBuffer );

			switch(lpPatternData->GetSearchField())
			{
			case CPatternData::SEARCHFIELD_NONE:
				szBuffer = _T("なし");
				break;
			case CPatternData::SEARCHFIELD_TAG:
				szBuffer = _T("タグ");
				break;
			case CPatternData::SEARCHFIELD_TYPE:
				szBuffer = _T("タイプ");
				break;
			case CPatternData::SEARCHFIELD_SEGMENT:
				szBuffer = _T("要素");
				break;
			case CPatternData::SEARCHFIELD_FILE:
				szBuffer = _T("ファイル位置");
				break;
			}
			SetItemText( nItem, COL_SEARCHFIELD, szBuffer );

			if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_NONE )
				szBuffer = _T("");
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TAG && lpPatternData->GetFealdEntryInfo() )
				szBuffer.Format( _T("%s : %s"), lpPatternData->GetFieldKey(), lpPatternData->GetFealdEntryInfo()->GetTagName() );
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TYPE && lpPatternData->GetTagTypeInfo() )
				szBuffer.Format( _T("%s : %s"), lpPatternData->GetFieldKey(), lpPatternData->GetTagTypeInfo()->GetTagTypeName() );
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_SEGMENT && lpPatternData->GetSegmentItemInfo() )
				szBuffer = lpPatternData->GetSegmentItemInfo()->GetItemName();
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_FILE )
				szBuffer.Format( _T("%s"), lpPatternData->GetFieldKey()==_T("-1")?_T("ファイル末尾"):lpPatternData->GetFieldKey() );
			else
				szBuffer.Format( _T("%s : Unknown"), lpPatternData->GetFieldKey() );
			SetItemText( nItem, COL_FIELDKEY, szBuffer );
			SetItemText( nItem, COL_DESCRIPTION, lpPatternData->GetDescription() );
			nItem++;
		}
	}

	return TRUE;
}

void CPatternSelectList::OnCheckItem( int nItem, BOOL bCheck )
{
	CPatternData *lpPatternData = (CPatternData*)GetItemData( nItem );
	if( lpPatternData )
		lpPatternData->SetCheck( bCheck );
	if( m_lpUserDatas )
		m_lpUserDatas->SetCheckedPatternDataCount( m_lpUserDatas->GetCheckedPatternDataCount() + (bCheck?1:-1) );
}
