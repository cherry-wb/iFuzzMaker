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
#include "PatternInfoLoader.h"


CPatternInfoLoader::CPatternInfoLoader(void)
{
}


CPatternInfoLoader::~CPatternInfoLoader(void)
{
}

BOOL CPatternInfoLoader::LoadText( CString szFileName, CPatternInfoArray *lpPatternInfoArray )
{
	m_lpPatternInfoArray = lpPatternInfoArray;
	return CTextLoader::LoadText( szFileName );
}

void CPatternInfoLoader::OnSplit( CStringArray &SplitedArray )
{
	if( SplitedArray.GetSize() == FUZZINFO_TEXT_COLUMN_TOTAL_COUNT && CheckParameter( SplitedArray ) )
	{
		if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DISPFLG)==_T("1") )
		{

			TCHAR* endptr = NULL;

			int nDataType = _tcstol( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE), &endptr, 10 );
			int nRepeat = _tcstol( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_REPEAT), &endptr, 10 );
			int nWriteMode = _tcstol( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_WRITEMODE), &endptr, 10 );
			int nFuzzarea = _tcstol( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA), &endptr, 10 );
			int nSearchField = _tcstol( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD), &endptr, 10 );

			CPatternInfo* lpPatternInfo = NULL;
			m_lpPatternInfoArray->AddWithNew( lpPatternInfo );
			lpPatternInfo->SetPatternInfo( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DISPFLG)==_T("1"),
									 SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SELECTFLG)==_T("1"),
									 SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DISPNAME),
									 nDataType,
									 SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_VALUE),
									 nRepeat,
									 nWriteMode,
									 nFuzzarea,
									 nSearchField,
									 SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FIELDKEY),
									 SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DESCRIPTION),
									 SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_VALUE) );
		}
	}
}

BOOL CPatternInfoLoader::CheckParameter( CStringArray &SplitedArray )
{
	CString szBuffer;

	szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DISPFLG);
	if( szBuffer.GetLength() != 1 )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("01") ).GetLength() > 0 )
		return FALSE;

	szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SELECTFLG);
	if( szBuffer.GetLength() != 1 )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("01") ).GetLength() > 0 )
		return FALSE;

	szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE);
	if( szBuffer.GetLength() != 1 )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("01234567") ).GetLength() > 0 )
		return FALSE;

	szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_REPEAT);
	if( szBuffer.SpanExcluding( _T("0123456789n") ).GetLength() > 0 )
		return FALSE;

	szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_WRITEMODE);
	if( szBuffer.SpanExcluding( _T("012") ).GetLength() > 0 )
		return FALSE;

	szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA);
	if( szBuffer.GetLength() != 1 )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("1234567") ).GetLength() > 0 )
		return FALSE;

	if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("1") ||
		SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("2") ||
		SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("3") ||
		SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("4") ||
		SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("5") )
	{
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD);
		if( szBuffer.GetLength() != 1 )
			return FALSE;
		if( szBuffer.SpanExcluding( _T("012") ).GetLength() > 0 )
			return FALSE;
	}else if(SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("6"))
	{
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD);
		if( szBuffer.GetLength() != 1 )
			return FALSE;
		if( szBuffer.SpanExcluding( _T("03") ).GetLength() > 0 )
			return FALSE;
	}else if(SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FUZZAREA) == _T("7"))
	{
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_REPEAT);
		if( szBuffer == _T("0") )
			return FALSE;
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD);
		if( szBuffer.GetLength() != 1 )
			return FALSE;
		if( szBuffer != _T("4") )
			return FALSE;
	}

	if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD) == _T("1") )
	{
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FIELDKEY);
		if( szBuffer.SpanExcluding( _T("-0123456789") ).GetLength() > 0 )
			return FALSE;
	}else if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD) == _T("2") )
	{
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FIELDKEY);
		if( szBuffer.SpanExcluding( _T("0123456789abcdefgABCDEFG") ).GetLength() > 0 )
			return FALSE;
	}else if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD) == _T("3") )
	{
	}else if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_SEARCHFIELD) == _T("4") )
	{
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_FIELDKEY);
		if( szBuffer != _T("-1") && szBuffer.SpanExcluding( _T("0123456789") ).GetLength() > 0 )
			return FALSE;
	}

	if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("0") )
	{
		//	0:テキスト
	}else if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("1") ||
			  SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("2") ||
			  SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("3") ||
			  SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("4") ||
			  SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("5") )
	{
		//	1:10進
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_VALUE);
		if( szBuffer.SpanExcluding( _T("-0123456789") ).GetLength() > 0 )
			return FALSE;
	}else if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("6") )
	{
		//	2:16進
		szBuffer = SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_VALUE);
		if( szBuffer.SpanExcluding( _T("0123456789abcdefgABCDEFG") ).GetLength() > 0 )
			return FALSE;
	}else if( SplitedArray.GetAt(FUZZINFO_TEXT_COLUMN_DATATYPE) == _T("7") )
	{
		//	3:ファイル(バイナリ)
	}
	return TRUE;
}
