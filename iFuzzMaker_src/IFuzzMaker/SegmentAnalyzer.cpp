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

#include "StdAfx.h"
#include "SegmentAnalyzer.h"
#include "EndianConverter.h"

CSegmentAnalyzer::CSegmentAnalyzer(void)
{
	m_nMaxBufferSize = 0;
	m_lpSegmentItemDataArray = NULL;
	m_lpSegmentData = NULL;
}

CSegmentAnalyzer::~CSegmentAnalyzer(void)
{
}

BOOL CSegmentAnalyzer::Analyze( unsigned int nMaxBufferSize, CSegmentData *lpSegmentData )
{
	unsigned int nOffset = 0;
	unsigned char* lpBuffer = NULL;

	m_nMaxBufferSize = nMaxBufferSize;
	m_lpSegmentData = lpSegmentData;

	lpBuffer = lpSegmentData->GetData();
	nOffset = lpSegmentData->GetOffset();

	m_lpSegmentItemDataArray = lpSegmentData->GetSegmentItemDataArray();
	CSegmentItemInfoArray *lpSegmentItemInfoArray = lpSegmentData->GetSegmentInfo()->GetSegmentItemInfoArray();

	AnalyzeSegmentItem( lpBuffer, nOffset, lpSegmentItemInfoArray );

	return TRUE;
}

int CSegmentAnalyzer::AnalyzeSegmentItem( unsigned char* lpBuffer, unsigned int nOffset, CSegmentItemInfoArray *lpSegmentItemInfoArray, int nArrayCount )
{
	unsigned int nSize = 0;
	unsigned int nItemCount = 0;
	unsigned int nCount = 0;
	unsigned int nRepeatCount = 0;

	CMap<CString, LPCTSTR, CSegmentItemData*, CSegmentItemData*> CountTagMap;
	for( nItemCount=0; nItemCount<(unsigned int)lpSegmentItemInfoArray->GetCount(); nItemCount++ )
	{
		nRepeatCount = 1;
		CString szItemTag;
		CSegmentItemData *lpSegmentItemData = NULL;
		CSegmentItemInfo *lpSegmentItemInfo = lpSegmentItemInfoArray->GetAt( nItemCount );

		if( CountTagMap.Lookup( lpSegmentItemInfo->GetCountTag(), lpSegmentItemData ) )
		{
			switch( lpSegmentItemData->GetDataType() )
			{
			case CSegmentItemData::ITEM_TYPE_BYTE:
				nRepeatCount = lpSegmentItemData->GetData()[0];
				break;
			case CSegmentItemData::ITEM_TYPE_SHORT:
				nRepeatCount = CEndianConverter::ConvertToShort(lpSegmentItemData->GetData());
				break;
			case CSegmentItemData::ITEM_TYPE_LONG:
				nRepeatCount = CEndianConverter::ConvertToInteger(lpSegmentItemData->GetData());
				break;
			default:
				nRepeatCount = 1;
			}
			lpSegmentItemData = NULL;
		}

		for( nCount=0; nCount<nRepeatCount; nCount++ )
		{
			if( lpSegmentItemInfo->GetDataType() == 0 )
			{
				nSize = AnalyzeSegmentItem( lpBuffer, nOffset, lpSegmentItemInfo->GetSegmentItemInfoArray() ) - nOffset;
				nOffset += nSize;
				lpBuffer += nSize;
			}else{
				m_lpSegmentItemDataArray->AddWithNew(lpSegmentItemData);
				if( lpSegmentItemData )
				{
					lpSegmentItemData->SetData( lpBuffer );
					lpSegmentItemData->SetOffset( nOffset );
					lpSegmentItemData->SetSize( lpSegmentItemInfo->GetDataSize() );
					lpSegmentItemData->SetDataType( lpSegmentItemInfo->GetDataType() );
					lpSegmentItemData->SetSegmentItemInfo( lpSegmentItemInfo );
					lpSegmentItemData->SetMarkerName( m_lpSegmentData->GetSegmentInfo()->GetMarkerName() );
					lpSegmentItemData->SetItemName( lpSegmentItemInfo->GetItemName() );

					if( lpSegmentItemData->QueryOverflow( m_nMaxBufferSize ) )
					{
						continue;
					}

					nOffset += lpSegmentItemInfo->GetDataSize();
					lpBuffer += lpSegmentItemInfo->GetDataSize();

					if( !CountTagMap.PLookup( lpSegmentItemInfo->GetItemTag() ) )
					{
						CountTagMap.SetAt( lpSegmentItemInfo->GetItemTag(), lpSegmentItemData );
					}
					TRACE( _T("%s (%d) ["), lpSegmentItemInfo->GetItemTag(), lpSegmentItemInfo->GetDataSize() );
					for( int datacnt=0; datacnt<lpSegmentItemInfo->GetDataSize(); datacnt++ )
						TRACE( datacnt==0?_T("%02X"):_T(" %02X"), lpSegmentItemData->GetData()[datacnt] );
					TRACE( _T("]\n") );
				}
			}
		}
	}
	return nOffset;
}

int CSegmentAnalyzer::FindCountTag( CString szCountTag )
{

	return 1;
}

