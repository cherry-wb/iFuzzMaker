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
#include "ExifAnalyzer.h"
#include "EndianConverter.h"

CExifAnalyzer::CExifAnalyzer(void)
{
	m_nImageFileDirectoryCount = 0;
	m_nTiffHeaderOffset = 0;
	m_nEndiannessType = CExifData::UNKNOWN_ENDIAN;
	m_nMaxBufferSize = 0;
	m_nExifOffset = 0;
	m_lpTagTypeInfoMap = NULL;
	m_lpImageFileDirectoryInfoMap = NULL;
	m_lpUnknownImageFileDirectoryInfo = NULL;
	m_lp0thImageFileDirectoryInfo = NULL;
	m_lp1stImageFileDirectoryInfo = NULL;
}


CExifAnalyzer::~CExifAnalyzer(void)
{
}

BOOL CExifAnalyzer::Analyze( unsigned int nMaxBufferSize, CSegmentData *lpSegmentData, CImageFileDirectoryInfoMap *lpImageFileDirectoryInfoMap, CTagTypeInfoMap *lpTagTypeInfoMap )
{
	unsigned int nNextIfdOffset = 0;
	unsigned int nOffset = 0;
	unsigned char* lpBuffer = NULL;

	m_nMaxBufferSize = nMaxBufferSize;
	m_nImageFileDirectoryCount = 0;

	lpBuffer = lpSegmentData->GetData();

	//	APP1マーカー
	if( lpBuffer[nOffset] != 0xFF || lpBuffer[nOffset+1] != 0xE1 )
		return FALSE;
	nOffset+=2;

	//	APP1レングス
	int segmentsize = ((lpBuffer[nOffset] << 8) | lpBuffer[nOffset+1]) + 2;
	nOffset+=2;

	if( segmentsize < 10 )
		return FALSE;

	m_nExifOffset = nOffset;
	//	Exif識別コード
	if( memcmp( &lpBuffer[nOffset], "Exif\0\0", 6 ) != 0 )
		return FALSE;
	nOffset+=6;

	//	TIFFヘッダー
	//	バイトオーダー
	m_nTiffHeaderOffset = nOffset;
	if( memcmp( &lpBuffer[nOffset], "MM", 2 ) == 0 )
	{
		m_nEndiannessType = CExifData::BIG_ENDIAN;
	}else if( memcmp( &lpBuffer[nOffset], "II", 2 ) == 0 )
	{
		m_nEndiannessType = CExifData::LITTLE_ENDIAN;
	}else{
		return FALSE;
	}
	nOffset+=2;

	//	マジックナンバー
	switch(m_nEndiannessType)
	{
	case CExifData::BIG_ENDIAN:
		if( lpBuffer[nOffset] != 0x00 || lpBuffer[nOffset+1] != 0x2A )
			return FALSE;
		break;
	case CExifData::LITTLE_ENDIAN:
		if( lpBuffer[nOffset] != 0x2A || lpBuffer[nOffset+1] != 0x00 )
			return FALSE;
		break;
	}
	nOffset+=2;

	CExifData* lpExifData = NULL;
	lpSegmentData->GetExifDataArray()->AddWithNew( lpExifData );


	lpExifData->SetExifMarker( &lpBuffer[m_nExifOffset+0] );
	lpExifData->SetEndianness( &lpBuffer[m_nExifOffset+6] );
	lpExifData->SetMagicNo( &lpBuffer[m_nExifOffset+8] );

	lpExifData->SetSize( lpSegmentData->GetSize() - m_nExifOffset );
	lpExifData->SetOffset( lpSegmentData->GetOffset() + m_nExifOffset );
	lpExifData->SetData( &lpBuffer[m_nExifOffset] );
	lpExifData->SetEndiannessType( m_nEndiannessType );

	m_lpTagTypeInfoMap = lpTagTypeInfoMap;

	m_lpImageFileDirectoryInfoMap = lpImageFileDirectoryInfoMap;
	POSITION pos = m_lpImageFileDirectoryInfoMap->GetStartPosition();
	while(pos)
	{
		CString szKey;
		CImageFileDirectoryInfo* lpImageFileDirectoryInfo = NULL;
		m_lpImageFileDirectoryInfoMap->GetNextAssoc( pos, szKey, lpImageFileDirectoryInfo );
		if( lpImageFileDirectoryInfo->GetOrder() == _T("0") )
			m_lpUnknownImageFileDirectoryInfo = lpImageFileDirectoryInfo;
		if( lpImageFileDirectoryInfo->GetOrder() == _T("1") )
			m_lp0thImageFileDirectoryInfo = lpImageFileDirectoryInfo;
		if( lpImageFileDirectoryInfo->GetOrder() == _T("2") )
			m_lp1stImageFileDirectoryInfo = lpImageFileDirectoryInfo;
	}

	//	IFDオフセット
	switch(m_nEndiannessType)
	{
	case CExifData::BIG_ENDIAN:
		nNextIfdOffset = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], TRUE );
		break;
	case CExifData::LITTLE_ENDIAN:
		nNextIfdOffset = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], FALSE );
		break;
	}
	nOffset+=4;

	nOffset = m_nTiffHeaderOffset + nNextIfdOffset;

	while( nNextIfdOffset )
	{

		CImageFileDirectoryInfo *lpImageFileDirectoryInfo = NULL;
		unsigned int nRecursiveCount = 0;
		nOffset = AnalyzeImageFileDirectory( lpBuffer, nOffset, lpExifData, lpImageFileDirectoryInfo, nRecursiveCount );

		if( nOffset > m_nMaxBufferSize )
			break;

		switch(m_nEndiannessType)
		{
		case CExifData::BIG_ENDIAN:
			nNextIfdOffset = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], TRUE );
			break;
		case CExifData::LITTLE_ENDIAN:
			nNextIfdOffset = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], FALSE );
			break;
		}
		nOffset+=4;
		nOffset = m_nTiffHeaderOffset + nNextIfdOffset;

	}

	return TRUE;
}

int CExifAnalyzer::AnalyzeImageFileDirectory( unsigned char* lpBuffer, unsigned int nOffset, CExifData* lpExifData, CImageFileDirectoryInfo* &lpImageFileDirectoryInfo, unsigned int &nRecursiveCount )
{

	CImageFileDirectoryData* lpImageFileDirectoryData = NULL;
	lpExifData->GetImageFileDirectoryDataArray()->AddWithNew( lpImageFileDirectoryData );

	lpImageFileDirectoryData->SetData( lpBuffer );
	lpImageFileDirectoryData->SetOffset( lpExifData->GetOffset() + nOffset - m_nExifOffset );
	lpImageFileDirectoryData->SetImageFileDirectoryInfo( lpImageFileDirectoryInfo );

	if( lpImageFileDirectoryData->QueryOverflow( m_nMaxBufferSize ) )
	{
		nOffset += 2;
		return nOffset;
	}


	if( !lpImageFileDirectoryInfo )
	{
		if( m_nImageFileDirectoryCount == 0 && m_lp0thImageFileDirectoryInfo )
		{
			lpImageFileDirectoryData->SetImageFileDirectoryInfo( m_lp0thImageFileDirectoryInfo );
			m_nImageFileDirectoryCount++;
		}else if( m_nImageFileDirectoryCount == 1 && m_lp1stImageFileDirectoryInfo )
		{
			lpImageFileDirectoryData->SetImageFileDirectoryInfo( m_lp1stImageFileDirectoryInfo );
			m_nImageFileDirectoryCount++;
		}else if( m_lpUnknownImageFileDirectoryInfo )
		{
			lpImageFileDirectoryData->SetImageFileDirectoryInfo( m_lpUnknownImageFileDirectoryInfo );
		}
	}
	//	エントリの数
	int nEntryCount = 0;
	switch(m_nEndiannessType)
	{
	case CExifData::BIG_ENDIAN:
		nEntryCount = CEndianConverter::ConvertToShort( &lpBuffer[nOffset], TRUE );
		break;
	case CExifData::LITTLE_ENDIAN:
		nEntryCount = CEndianConverter::ConvertToShort( &lpBuffer[nOffset], FALSE );
		break;
	}
	nOffset+=2;

	lpImageFileDirectoryData->SetEntryCount( nEntryCount );

	int nCnt = 0;
	for( nCnt=0; nCnt<nEntryCount; nCnt++ )
	{
		CFealdEntryData *lpFealdEntryData = NULL;
		lpImageFileDirectoryData->GetFealdEntryDataArray()->AddWithNew( lpFealdEntryData );

		lpFealdEntryData->SetOffset( lpExifData->GetOffset() + nOffset - m_nExifOffset );
		lpFealdEntryData->SetSize( 12 );

		//	タグが領域を超えている
		if( lpFealdEntryData->QueryOverflow( m_nMaxBufferSize ) )
		{
			nOffset += 12;
			continue;
		}

		lpFealdEntryData->SetData( &lpBuffer[nOffset] );

		//	タグ
		int nTag = 0;
		switch(m_nEndiannessType)
		{
		case CExifData::BIG_ENDIAN:
			nTag = CEndianConverter::ConvertToShort( &lpBuffer[nOffset], TRUE );
			break;
		case CExifData::LITTLE_ENDIAN:
			nTag = CEndianConverter::ConvertToShort( &lpBuffer[nOffset], FALSE );
			break;
		}
		nOffset+=2;

		CString szTagId;
		szTagId.Format( _T("%04X"), nTag );

		lpFealdEntryData->SetTagNumber( nTag );
		lpFealdEntryData->SetTagID( szTagId );

		//	タイプ
		int nType = 0;
		switch(m_nEndiannessType)
		{
		case CExifData::BIG_ENDIAN:
			nType = CEndianConverter::ConvertToShort( &lpBuffer[nOffset], TRUE );
			break;
		case CExifData::LITTLE_ENDIAN:
			nType = CEndianConverter::ConvertToShort( &lpBuffer[nOffset], FALSE );
			break;
		}
		nOffset+=2;
		lpFealdEntryData->SetType( nType );

		int nCount = 0;
		switch(m_nEndiannessType)
		{
		case CExifData::BIG_ENDIAN:
			nCount = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], TRUE );
			break;
		case CExifData::LITTLE_ENDIAN:
			nCount = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], FALSE );
			break;
		}
		nOffset+=4;
		lpFealdEntryData->SetCount( nCount );

		int nValueOrOffset = 0;
		switch(m_nEndiannessType)
		{
		case CExifData::BIG_ENDIAN:
			nValueOrOffset = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], TRUE );
			break;
		case CExifData::LITTLE_ENDIAN:
			nValueOrOffset = CEndianConverter::ConvertToInteger( &lpBuffer[nOffset], FALSE );
			break;
		}
		nOffset+=4;
		lpFealdEntryData->SetValueOrOffset( nValueOrOffset );

		CFealdEntryInfo* lpFealdEntryInfo = NULL;

		if( lpImageFileDirectoryInfo )
			lpImageFileDirectoryInfo->GetFealdEntryInfoMap()->Lookup( szTagId, lpFealdEntryInfo );
		if( !lpFealdEntryInfo )
		{
			if( m_nImageFileDirectoryCount == 1 && m_lp0thImageFileDirectoryInfo )
			{
				m_lp0thImageFileDirectoryInfo->GetFealdEntryInfoMap()->Lookup( szTagId, lpFealdEntryInfo );
			}else if( m_nImageFileDirectoryCount == 2 && m_lp1stImageFileDirectoryInfo )
			{
				m_lp1stImageFileDirectoryInfo->GetFealdEntryInfoMap()->Lookup( szTagId, lpFealdEntryInfo );
			}else if( m_lpUnknownImageFileDirectoryInfo )
			{
				m_lpUnknownImageFileDirectoryInfo->GetFealdEntryInfoMap()->Lookup( szTagId, lpFealdEntryInfo );
			}
		}

		if( lpFealdEntryInfo )
		{
			lpFealdEntryData->SetFealdEntryInfo( lpFealdEntryInfo );

			CTagTypeInfo* lpTagTypeInfo = NULL;
			if( m_lpTagTypeInfoMap->Lookup( nType, lpTagTypeInfo ) )
			{
				lpFealdEntryData->SetTagTypeInfo( lpTagTypeInfo );
			}

			if( lpTagTypeInfo )
			{
				CTagData* lpTagData = NULL;
				lpFealdEntryData->GetTagDataArray()->AddWithNew( lpTagData );

				if( nCount * lpTagTypeInfo->GetSize() > 4 )
				{
					lpTagData->SetOffset( lpExifData->GetOffset() + m_nTiffHeaderOffset + nValueOrOffset - m_nExifOffset );
					lpTagData->SetSize( nCount * lpTagTypeInfo->GetSize() );

					//	データが領域を超えている
					if( lpTagData->QueryOverflow( m_nMaxBufferSize ) )
					{
						continue;
					}
					
					lpTagData->SetData( &lpBuffer[m_nTiffHeaderOffset + nValueOrOffset] );
				}else{
					lpTagData->SetOffset( lpFealdEntryData->GetOffset() + 8 );
					lpTagData->SetData( (lpFealdEntryData->GetData()) + 8 );
					lpTagData->SetSize( 4 );
				}
			}
		}

		//	２回以上の入れ子のIFDは無視する
		if( nRecursiveCount < 2 )
		{
			CImageFileDirectoryInfo *lpWorkImageFileDirectoryInfo = NULL;
			if( m_lpImageFileDirectoryInfoMap->Lookup( szTagId, lpWorkImageFileDirectoryInfo ) )
			{
				nRecursiveCount++;
				AnalyzeImageFileDirectory( lpBuffer, m_nTiffHeaderOffset+nValueOrOffset, lpExifData, lpWorkImageFileDirectoryInfo, nRecursiveCount );
				nRecursiveCount--;
			}
		}
	}

	lpImageFileDirectoryInfo = NULL;

	return nOffset;
}
