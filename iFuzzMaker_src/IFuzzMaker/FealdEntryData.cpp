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

//==============================================================================
#include "StdAfx.h"
#include "FealdEntryData.h"


CFealdEntryData::CFealdEntryData(void)
{
	m_lpTagTypeInfo = NULL;
	m_lpFealdEntryInfo = NULL;

	m_bCheck = TRUE;
	m_nTagNumber = 0;
	m_nType = 0;
	m_nCount = 0;
	m_nValueOrOffset = 0;
}

CFealdEntryData::~CFealdEntryData(void)
{
	m_TagDataArray.RemoveAllWithDelete();
}

void CFealdEntryData::SetCheck( BOOL bCheck )
{
	m_bCheck = bCheck;
}

BOOL CFealdEntryData::GetCheck()
{
	return m_bCheck;
}

void CFealdEntryData::SetTagID( CString szTagID )
{
	m_szTagID = szTagID;
}

CString CFealdEntryData::GetTagID()
{
	return m_szTagID;
}

void CFealdEntryData::SetTagNumber( int nTagNumber )
{
	m_nTagNumber = nTagNumber;
}

int CFealdEntryData::GetTagNumber()
{
	return m_nTagNumber;
}

void CFealdEntryData::SetType( int nType )
{
	m_nType = nType;
}

int CFealdEntryData::GetType()
{
	return m_nType;
}

void CFealdEntryData::SetCount( int nCount )
{
	m_nCount = nCount;
}

int CFealdEntryData::GetCount()
{
	return m_nCount;
}

void CFealdEntryData::SetValueOrOffset( int nValueOrOffset )
{
	m_nValueOrOffset = nValueOrOffset;
}

int CFealdEntryData::GetValueOrOffset()
{
	return m_nValueOrOffset;
}

void CFealdEntryData::SetTagTypeInfo( CTagTypeInfo *lpTagTypeInfo )
{
	m_lpTagTypeInfo = lpTagTypeInfo;
}

CTagTypeInfo* CFealdEntryData::GetTagTypeInfo()
{
	return m_lpTagTypeInfo;
}

void CFealdEntryData::SetFealdEntryInfo( CFealdEntryInfo *lpFealdEntryInfo )
{
	m_lpFealdEntryInfo = lpFealdEntryInfo;
}

CFealdEntryInfo* CFealdEntryData::GetFealdEntryInfo()
{
	return m_lpFealdEntryInfo;
}

CTagDataArray* CFealdEntryData::GetTagDataArray()
{
	return &m_TagDataArray;
}

