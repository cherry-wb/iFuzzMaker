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
#include "FuzzData.h"


CFuzzData::CFuzzData(void)
{
	m_bCheck = TRUE;
	m_lpFealdEntryData = NULL;
	m_lpSegmentItemData = NULL;
	m_lpPatternData = NULL;
}

CFuzzData::~CFuzzData(void)
{
}

CSystemTime &CFuzzData::GetCreateDateTime()
{
	return m_CreateDateTime;
}

void CFuzzData::SetCheck( BOOL bCheck )
{
	m_bCheck = bCheck;
}

BOOL CFuzzData::GetCheck()
{
	return m_bCheck;
}

void CFuzzData::SetFileName( CString szFileName )
{
	m_szFileName = szFileName;
}

CString CFuzzData::GetFileName()
{
	return m_szFileName;
}

void CFuzzData::SetFilePath( CString szFilePath )
{
	m_szFilePath = szFilePath;
}

CString CFuzzData::GetFilePath()
{
	return m_szFilePath;
}

void CFuzzData::SetFuzzDataType( int nFuzzDataType )
{
	m_nFuzzDataType = nFuzzDataType;
}

int CFuzzData::GetFuzzDataType()
{
	return m_nFuzzDataType;
}

void CFuzzData::SetFealdEntryData( CFealdEntryData *lpFealdEntryData )
{
	m_lpFealdEntryData = lpFealdEntryData;
}

CFealdEntryData* CFuzzData::GetFealdEntryData()
{
	return m_lpFealdEntryData;
}

void CFuzzData::SetSegmentItemData( CSegmentItemData *lpSegmentItemData )
{
	m_lpSegmentItemData = lpSegmentItemData;
}

CSegmentItemData* CFuzzData::GetSegmentItemData()
{
	return m_lpSegmentItemData;
}

void CFuzzData::SetPatternData( CPatternData *lpPatternData )
{
	m_lpPatternData = lpPatternData;
}

CPatternData* CFuzzData::GetPatternData()
{
	return m_lpPatternData;
}

void CFuzzData::SetCounter( int nCounter )
{
	m_nCounter = nCounter;
}

int CFuzzData::GetCounter()
{
	return m_nCounter;
}

void CFuzzData::SetErrorMessage( CString szErrorMessage )
{
	m_szErrorMessage = szErrorMessage;
}

CString CFuzzData::GetErrorMessage()
{
	return m_szErrorMessage;
}
