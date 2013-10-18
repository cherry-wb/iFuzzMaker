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
#include "PatternData.h"


CPatternData::CPatternData(void)
{
	m_bCheck = TRUE;
	m_nDataType = 0;
	m_nRepeat = 0;
	m_nWriteMode = 0;
	m_nFuzzArea = 0;
	m_nSearchField = 0;
	m_nFilePos = 0;
	m_lpFealdEntryInfo = NULL;
	m_lpTagTypeInfo = NULL;
	m_lpSegmentItemInfo = NULL;
}


CPatternData::~CPatternData(void)
{
}

void CPatternData::SetCheck( BOOL bCheck )
{
	m_bCheck = bCheck;
}

BOOL CPatternData::GetCheck()
{
	return m_bCheck;
}

void CPatternData::SetDispName( CString szDispName )
{
	m_szDispName = szDispName;
}

CString CPatternData::GetDispName()
{
	return m_szDispName;
}

void CPatternData::SetDataType( int nDataType )
{
	m_nDataType = nDataType;
}

int CPatternData::GetDataType()
{
	return m_nDataType;
}

void CPatternData::SetValue( CString szValue )
{
	m_szValue = szValue;
}

CString CPatternData::GetValue()
{
	return m_szValue;
}

void CPatternData::SetRepeat( int nRepeat )
{
	m_nRepeat = nRepeat;
}

int CPatternData::GetRepeat()
{
	return m_nRepeat;
}

void CPatternData::SetWriteMode( int nWriteMode )
{
	m_nWriteMode = nWriteMode;
}

int CPatternData::GetWriteMode()
{
	return m_nWriteMode;
}

void CPatternData::SetFuzzArea( int nFuzzArea )
{
	m_nFuzzArea = nFuzzArea;
}

int CPatternData::GetFuzzArea()
{
	return m_nFuzzArea;
}

void CPatternData::SetSearchField( int nSearchField )
{
	m_nSearchField = nSearchField;
}

int CPatternData::GetSearchField()
{
	return m_nSearchField;
}

void CPatternData::SetFieldKey( CString szFieldKey )
{
	m_szFieldKey = szFieldKey;
}

CString CPatternData::GetFieldKey()
{
	return m_szFieldKey;
}

void CPatternData::SetFilePos( int szFilePos )
{
	m_nFilePos = szFilePos;
}

int CPatternData::GetFilePos()
{
	return m_nFilePos;
}

void CPatternData::SetDescription( CString szDescription )
{
	m_szDescription = szDescription;
}

CString CPatternData::GetDescription()
{
	return m_szDescription;
}

void CPatternData::SetBinaryDataArray( CReadBufferArray &BinaryDataArray )
{
	m_BinaryDataArray.Copy( BinaryDataArray );
}

CReadBufferArray* CPatternData::GetBinaryDataArray()
{
	return &m_BinaryDataArray;
}


void CPatternData::SetFealdEntryInfo( CFealdEntryInfo* lpFealdEntryInfo )
{
	m_lpFealdEntryInfo = lpFealdEntryInfo;
}

CFealdEntryInfo* CPatternData::GetFealdEntryInfo()
{
	return m_lpFealdEntryInfo;
}

void CPatternData::SetTagTypeInfo( CTagTypeInfo* lpTagTypeInfo )
{
	m_lpTagTypeInfo = lpTagTypeInfo;
}

CTagTypeInfo* CPatternData::GetTagTypeInfo()
{
	return m_lpTagTypeInfo;
}

void CPatternData::SetSegmentItemInfo( CSegmentItemInfo* lpSegmentItemInfo )
{
	m_lpSegmentItemInfo = lpSegmentItemInfo;
}

CSegmentItemInfo* CPatternData::GetSegmentItemInfo()
{
	return m_lpSegmentItemInfo;
}
