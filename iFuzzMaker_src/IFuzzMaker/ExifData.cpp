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
#include "ExifData.h"


CExifData::CExifData(void)
{
	m_nEndiannessType = UNKNOWN_ENDIAN;
	ZeroMemory( m_chExifMarker, sizeof(m_chExifMarker) );
	m_nEndianness = 0;
	m_nMagicNo = 0;
}

CExifData::~CExifData(void)
{
	m_ImageFileDirectoryDataArray.RemoveAllWithDelete();
}

void CExifData::SetEndiannessType( int nEndiannessType )
{
	m_nEndiannessType = nEndiannessType;
}

int CExifData::GetEndiannessType()
{
	return m_nEndiannessType;
}

void CExifData::SetExifMarker( unsigned char *lpBuffer )
{
	memcpy_s( m_chExifMarker, 6, lpBuffer, 6 );
}

unsigned char *CExifData::GetExifMarker()
{
	return m_chExifMarker;
}

void CExifData::SetEndianness( unsigned char *lpBuffer )
{
	memcpy_s( &m_nEndianness, 2, lpBuffer, 2 );
}

unsigned short CExifData::GetEndianness()
{
	return m_nEndianness;
}

void CExifData::SetMagicNo( unsigned char *lpBuffer )
{
	memcpy_s( &m_nMagicNo, 2, lpBuffer, 2 );
}

unsigned short CExifData::GetMagicNo()
{
	return m_nMagicNo;
}

CImageFileDirectoryDataArray* CExifData::GetImageFileDirectoryDataArray()
{
	return &m_ImageFileDirectoryDataArray;
}

