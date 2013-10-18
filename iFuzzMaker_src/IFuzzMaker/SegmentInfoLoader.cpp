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
#include "SegmentInfoLoader.h"


CSegmentInfoLoader::CSegmentInfoLoader()
{
}


CSegmentInfoLoader::~CSegmentInfoLoader()
{
}

BOOL CSegmentInfoLoader::LoadText( CString szFileName, CSegmentInfoMap *lpSegmentInfoMap )
{
	m_lpSegmentInfoMap = lpSegmentInfoMap;
	return CTextLoader::LoadText( szFileName );
}

void CSegmentInfoLoader::OnSplit( CStringArray &SplitedArray )
{
	if( SplitedArray.GetSize() == SEGMENT_TEXT_COLUMN_COUNT && CheckParameter( SplitedArray ) )
	{
		CSegmentInfo *lpSegmentInfo = m_lpSegmentInfoMap->SetAtWithNew( SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_MARKER) );
		lpSegmentInfo->SetSegmentInfo( SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_MARKER),
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_MARKERNAME),
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_SEGMENTNAME),
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_DESCRIPTION),
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_HASLENGTHFEELD)=="1"?TRUE:FALSE,
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_NEXTSEGMENTIMAGE)=="1"?TRUE:FALSE,
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_ANALYSISFLAG)=="1"?TRUE:FALSE,
									   SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_SEGMENTITEMINFOFILENAME) );
		return;
	}
}

BOOL CSegmentInfoLoader::CheckParameter( CStringArray &SplitedArray )
{
	CString szBuffer;

	szBuffer = SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_MARKER);
	if( szBuffer.GetLength() != 4 )
		return FALSE;
	if( szBuffer.Left( 2 ) != _T("FF") )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("0123456789ABCDEFabcdef") ).GetLength() > 0 )
		return FALSE;

	szBuffer = SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_HASLENGTHFEELD);
	if( szBuffer != _T("0") && szBuffer != _T("1") )
		return FALSE;

	szBuffer = SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_NEXTSEGMENTIMAGE);
	if( szBuffer != _T("0") && szBuffer != _T("1") )
		return FALSE;

	szBuffer = SplitedArray.GetAt(SEGMENT_TEXT_COLUMN_ANALYSISFLAG);
	if( szBuffer != _T("0") && szBuffer != _T("1") )
		return FALSE;

	return TRUE;
}
