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
#include "PatternInfo.h"


CPatternInfo::CPatternInfo(void)
{
	m_bDispFlag = FALSE;
	m_bSelectFlag = FALSE;
	m_nDataType = 0;
	m_nRepeat = 0;
	m_nWriteMode = 0;
	m_nFuzzArea = 0;
	m_nSearchField = 0;
}


CPatternInfo::~CPatternInfo(void)
{
}


void CPatternInfo::SetPatternInfo( BOOL bDispFlag, BOOL bSelectFlag, CString szDispName, int nDataType, CString szValue, int nRepeat, int nWriteMode, int nFuzzArea, int nSearchField, CString szFieldKey, CString szDescription, CString szFileName )
{
	m_bDispFlag = bDispFlag;
	m_bSelectFlag = bSelectFlag;
	m_szDispName = szDispName;
	m_nDataType = nDataType;
	m_szValue = szValue;
	m_nRepeat = nRepeat;
	m_nWriteMode = nWriteMode;
	m_nFuzzArea = nFuzzArea;
	m_nSearchField = nSearchField;
	m_szFieldKey = szFieldKey;
	m_szDescription = szDescription;
	m_szFileName = szFileName;
}

void CPatternInfo::SetDispFlag( BOOL bDispFlag )
{
	m_bDispFlag = bDispFlag;
}

BOOL CPatternInfo::GetDispFlag()
{
	return m_bDispFlag;
}

void CPatternInfo::SetSelectFlag( BOOL bSelectFlag )
{
	m_bSelectFlag = bSelectFlag;
}

BOOL CPatternInfo::GetSelectFlag()
{
	return m_bSelectFlag;
}

void CPatternInfo::SetDispName( CString szDispName )
{
	m_szDispName = szDispName;
}

CString CPatternInfo::GetDispName()
{
	return m_szDispName;
}

void CPatternInfo::SetDataType( int nDataType )
{
	m_nDataType = nDataType;
}

int CPatternInfo::GetDataType()
{
	return m_nDataType;
}

void CPatternInfo::SetValue( CString szValue )
{
	m_szValue = szValue;
}

CString CPatternInfo::GetValue()
{
	return m_szValue;
}

void CPatternInfo::SetRepeat( int nRepeat )
{
	m_nRepeat = nRepeat;
}

int CPatternInfo::GetRepeat()
{
	return m_nRepeat;
}

void CPatternInfo::SetWriteMode( int nWriteMode )
{
	m_nWriteMode = nWriteMode;
}

int CPatternInfo::GetWriteMode()
{
	return m_nWriteMode;
}

void CPatternInfo::SetFuzzArea( int nFuzzArea )
{
	m_nFuzzArea = nFuzzArea;
}

int CPatternInfo::GetFuzzArea()
{
	return m_nFuzzArea;
}

void CPatternInfo::SetSearchField( int nSearchField )
{
	m_nSearchField = nSearchField;
}

int CPatternInfo::GetSearchField()
{
	return m_nSearchField;
}

void CPatternInfo::SetFieldKey( CString szFieldKey)
{
	m_szFieldKey = szFieldKey;
}

CString CPatternInfo::GetFieldKey()
{
	return m_szFieldKey;
}

void CPatternInfo::SetDescription( CString szDescription )
{
	m_szDescription = szDescription;
}

CString CPatternInfo::GetDescription()
{
	return m_szDescription;
}

void CPatternInfo::SetFileName( CString szFileName )
{
	m_szFileName = szFileName;
}

CString CPatternInfo::GetFileName()
{
	return m_szFileName;
}
