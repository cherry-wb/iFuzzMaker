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
#include "UserDatas.h"


CUserDatas::CUserDatas(void)
{
	m_nCheckedFealdEntryDataCount = 0;
	m_nCheckedSegmentItemDataCount = 0;
	m_nCheckedPatternDataCount = 0;
	m_nCheckedFuzzDataCount = 0;
	m_bFuzzCreateing = FALSE;
}

CUserDatas::~CUserDatas(void)
{
}

CReadBufferArray& CUserDatas::GetReadBufferArray()
{
	return m_ReadBufferArray;
}

CSegmentDataArray& CUserDatas::GetSegmentDataArray()
{
	return m_SegmentDataArray;
}

CPatternGroupDataArray& CUserDatas::GetPatternGroupDataArray()
{
	return m_PatternGroupDataArray;
}

CFuzzDataArray& CUserDatas::GetFuzzDataArray()
{
	return m_FuzzDataArray;
}

CSystemTime& CUserDatas::GetCreateFuzzTime()
{
	return m_CreateFuzzTime;
}

void CUserDatas::SetJpegFileName( CString szJpegFileName )
{
	m_szJpegFileName = szJpegFileName;
}

CString CUserDatas::GetJpegFileName()
{
	return m_szJpegFileName;
}

void CUserDatas::SetOutputFolder( CString szOutputFolder )
{
	m_szOutputFolder = szOutputFolder;
}

CString CUserDatas::GetOutputFolder()
{
	return m_szOutputFolder;
}

void CUserDatas::SetCheckedFealdEntryDataCount( int nCheckedFealdEntryDataCount )
{
	m_nCheckedFealdEntryDataCount = nCheckedFealdEntryDataCount;
}

int CUserDatas::GetCheckedFealdEntryDataCount()
{
	return m_nCheckedFealdEntryDataCount;
}

void CUserDatas::SetCheckedSegmentItemDataCount( int nCheckedSegmentItemDataCount )
{
	m_nCheckedSegmentItemDataCount = nCheckedSegmentItemDataCount;
}

int CUserDatas::GetCheckedSegmentItemDataCount()
{
	return m_nCheckedSegmentItemDataCount;
}

void CUserDatas::SetCheckedPatternDataCount( int nCheckedPatternDataCount )
{
	m_nCheckedPatternDataCount = nCheckedPatternDataCount;
}

int CUserDatas::GetCheckedPatternDataCount()
{
	return m_nCheckedPatternDataCount;
}

void CUserDatas::SetCheckedFuzzDataCount( int nCheckedFuzzDataCount )
{
	m_nCheckedFuzzDataCount = nCheckedFuzzDataCount;
}

int CUserDatas::GetCheckedFuzzDataCount()
{
	return m_nCheckedFuzzDataCount;
}

void CUserDatas::SetGroupFileName( CString szGroupFileName )
{
	m_szGroupFileName = szGroupFileName;
}

CString CUserDatas::GetGroupFileName()
{
	return m_szGroupFileName;
}

void CUserDatas::SetDiscription( CString szDiscription )
{
	m_szDiscription = szDiscription;
}

CString CUserDatas::GetDiscription()
{
	return m_szDiscription;
}

void CUserDatas::SetFuzzCreateing( BOOL bFuzzCreateing )
{
	m_bFuzzCreateing = bFuzzCreateing;
}

BOOL CUserDatas::GetFuzzCreateing()
{
	return m_bFuzzCreateing;
}

void CUserDatas::Clear()
{
	m_szJpegFileName = _T("");
	m_szGroupFileName = _T("");

	m_ReadBufferArray.RemoveAll();

	m_SegmentDataArray.RemoveAllWithDelete();
	m_PatternGroupDataArray.RemoveAllWithDelete();
	m_FuzzDataArray.RemoveAllWithDelete();

	m_nCheckedFealdEntryDataCount = 0;
	m_nCheckedSegmentItemDataCount = 0;
	m_nCheckedPatternDataCount = 0;
	m_nCheckedFuzzDataCount = 0;
}
