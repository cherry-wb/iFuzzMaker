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
#include "SegmentItemInfoLoader.h"

int CSegmentItemInfoLoader::m_nNodeCount = 0;

CSegmentItemInfoLoader::CSegmentItemInfoLoader(void)
{
	m_lpSegmentItemInfoArray = NULL;
	m_lpSegmentItemInfoMap = NULL;
}

CSegmentItemInfoLoader::~CSegmentItemInfoLoader(void)
{
}

BOOL CSegmentItemInfoLoader::LoadText( CString szFileName, CSegmentItemInfoArray *lpSegmentItemInfoArray, CSegmentItemInfoMap *lpSegmentItemInfoMap )
{
	m_lpSegmentItemInfoArray = lpSegmentItemInfoArray;
	m_lpSegmentItemInfoMap = lpSegmentItemInfoMap;
	return CTextLoader::LoadText( szFileName );
}

void CSegmentItemInfoLoader::OnSplit( CStringArray &SplitedArray )
{
	if( SplitedArray.GetSize() == SEGMENTITEM_TEXT_COLUMN_COUNT && CheckParameter( SplitedArray ) )
	{
		CSegmentItemInfo *lpSegmentItemInfo= NULL;
		m_lpSegmentItemInfoArray->AddWithNew( lpSegmentItemInfo );
		m_lpSegmentItemInfoMap->SetAt( SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_ITEMTAG), lpSegmentItemInfo );
		lpSegmentItemInfo->SetSegmentItemInfo( SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_ITEMTAG),
											   SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_ITEMNAME),
											   SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_DESCRIPTION),
											   _tcstol( SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_DATASIZE),NULL,10),
											   _tcstol( SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_DISPTYPE),NULL,10),
											   SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_COUNTTAG),
											   SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_SEGMENTITEMINFOFILENAME),
											   m_lpSegmentItemInfoArray );

		if( SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_DISPTYPE) == _T("0") )
		{
			//	8階層まで
			if( ++m_nNodeCount < MAX_NODE_COUNT )
			{
				CSegmentItemInfoLoader SegmentItemInfoLoader;
				SegmentItemInfoLoader.LoadText( lpSegmentItemInfo->GetSegmentItemInfoFileName(), lpSegmentItemInfo->GetSegmentItemInfoArray(), m_lpSegmentItemInfoMap );
			}
			m_nNodeCount--;
		}

		return;
	}
}

BOOL CSegmentItemInfoLoader::CheckParameter( CStringArray &SplitedArray )
{
	int nReturnValue = 0;
	TCHAR* endptr = NULL;
	CString szBuffer;

	szBuffer = SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_DATASIZE);
	nReturnValue = _tcstol( szBuffer, &endptr, 10 );
	if( _tcslen(endptr) )
		return FALSE;

	szBuffer = SplitedArray.GetAt(SEGMENTITEM_TEXT_COLUMN_DISPTYPE);
	if( szBuffer.GetLength() != 1 )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("01234") ).GetLength() > 0 )
		return FALSE;
	if( (szBuffer == _T("1") || szBuffer == _T("2")) && nReturnValue < 1 )
		return FALSE;
	if( szBuffer == _T("3") && nReturnValue < 1 && (nReturnValue%2) != 0 )
		return FALSE;
	if( szBuffer == _T("4") && nReturnValue < 1 && (nReturnValue%4) != 0 )
		return FALSE;

	return TRUE;
}
