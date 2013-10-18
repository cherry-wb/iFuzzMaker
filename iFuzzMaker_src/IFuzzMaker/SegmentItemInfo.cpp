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
#include "SegmentItemInfo.h"

CSegmentItemInfo::CSegmentItemInfo(void)
{
	m_lpParentSegmentItemInfoArray = NULL;
}

CSegmentItemInfo::CSegmentItemInfo( CString szItemTag, CString szItemName, CString szDescription, int nDataSize, int nDataType, CString szCountTag, CString szSegmentItemInfoFileName, CSegmentItemInfoArray *lpParentSegmentItemInfoArray )
{
	SetSegmentItemInfo( szItemTag, szItemName, szDescription, nDataSize, nDataType, szCountTag, szSegmentItemInfoFileName, lpParentSegmentItemInfoArray );
}

CSegmentItemInfo::~CSegmentItemInfo(void)
{
}

void CSegmentItemInfo::SetSegmentItemInfo( CString szItemTag, CString szItemName, CString szDescription, int nDataSize, int nDataType, CString szCountTag, CString szSegmentItemInfoFileName, CSegmentItemInfoArray *lpParentSegmentItemInfoArray )
{
	m_szItemTag = szItemTag;
	m_szItemName = szItemName;
	m_szDescription = szDescription;
	m_nDataSize = nDataSize;
	m_nDataType = nDataType;
	m_szCountTag = szCountTag;
	m_szSegmentItemInfoFileName = szSegmentItemInfoFileName;
	m_lpParentSegmentItemInfoArray = lpParentSegmentItemInfoArray;
}

CString CSegmentItemInfo::GetItemTag()
{
	return m_szItemTag;
}

CString CSegmentItemInfo::GetItemName()
{
	return m_szItemName;
}

CString CSegmentItemInfo::GetDescription()
{
	return m_szDescription;
}

int CSegmentItemInfo::GetDataSize()
{
	return m_nDataSize;
}

int CSegmentItemInfo::GetDataType()
{
	return m_nDataType;
}

CString CSegmentItemInfo::GetCountTag()
{
	return m_szCountTag;
}

CString CSegmentItemInfo::GetSegmentItemInfoFileName()
{
	return m_szSegmentItemInfoFileName;
}

CSegmentItemInfoArray* CSegmentItemInfo::GetParentSegmentItemInfoArray()
{
	return m_lpParentSegmentItemInfoArray;
}

CSegmentItemInfoArray* CSegmentItemInfo::GetSegmentItemInfoArray()
{
	return &m_SegmentItemInfoArray;
}
