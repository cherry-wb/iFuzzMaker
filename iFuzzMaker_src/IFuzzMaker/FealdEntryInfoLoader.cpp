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
#include "FealdEntryInfoLoader.h"


CFealdEntryInfoLoader::CFealdEntryInfoLoader(void)
{
}

CFealdEntryInfoLoader::~CFealdEntryInfoLoader(void)
{
}

BOOL CFealdEntryInfoLoader::LoadText( CString szFileName, CFealdEntryInfoMap *lpFealdEntryInfoMap )
{
	m_lpFealdEntryInfoMap = lpFealdEntryInfoMap;
	return CTextLoader::LoadText( szFileName );
}

void CFealdEntryInfoLoader::OnSplit( CStringArray &SplitedArray )
{
	CString szCount;
	CString szDefault;
	CString szValues;
	CString szDiscription;
	if( SplitedArray.GetSize() == FEALDENTRY_TEXT_COLUMN_TOTAL_COUNT && CheckParameter( SplitedArray ) )
	{
		szCount = SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_COUNT);
		szDefault = SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_DEFAULT);
		szValues = SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_VALUES);
		szDiscription = SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_DISCRIPTION);

		szCount.Replace( _T("\\n"), _T("\r\n") );
		szDefault.Replace( _T("\\n"), _T("\r\n") );
		szValues.Replace( _T("\\n"), _T("\r\n") );
		szDiscription.Replace( _T("\\n"), _T("\r\n") );

		CFealdEntryInfo *lpFealdEntryInfo = m_lpFealdEntryInfoMap->SetAtWithNew( SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_TAGID) );
		lpFealdEntryInfo->SetFealdEntryInfo( SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_TAGID),
											 SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_TAGNUMBER),
											 SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_TAGNAME),
											 SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_DISPNAME),
											 SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_TYPE),
											 szCount,
											 szDefault,
											 szValues,
											 szDiscription );
	}
}

BOOL CFealdEntryInfoLoader::CheckParameter( CStringArray &SplitedArray )
{
	CString szBuffer;

	szBuffer = SplitedArray.GetAt(FEALDENTRY_TEXT_COLUMN_TAGID);
	if( szBuffer.GetLength() != 4 )
		return FALSE;
	if( szBuffer.SpanExcluding( _T("0123456789ABCDEFabcdef") ).GetLength() > 0 )
		return FALSE;

	return TRUE;
}
