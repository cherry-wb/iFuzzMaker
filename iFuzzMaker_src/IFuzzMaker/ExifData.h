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

#pragma once
#include "ReadData.h"
#include "ImageFileDirectoryData.h"
#include "AutoDeleteArrayHelper.h"

class CExifData : public CReadData
{
public:
	CExifData(void);
	~CExifData(void);

	enum
	{
		UNKNOWN_ENDIAN,
		BIG_ENDIAN,
		LITTLE_ENDIAN
	};

	void SetEndiannessType( int nEndiannessType );
	int GetEndiannessType();

	void SetExifMarker( unsigned char *lpBuffer );
	unsigned char *GetExifMarker();

	void SetEndianness( unsigned char *lpBuffer );
	unsigned short GetEndianness();

	void SetMagicNo( unsigned char *lpBuffer );
	unsigned short GetMagicNo();

	CImageFileDirectoryDataArray* GetImageFileDirectoryDataArray();

protected:
	CImageFileDirectoryDataArray m_ImageFileDirectoryDataArray;

	int m_nEndiannessType;

	//	Exif識別コード
	unsigned char m_chExifMarker[6];
	//CString m_szExifMarker;
	//	エンディアン
	unsigned short m_nEndianness;
	//CString m_szEndianness;
	//	マジックナンバー
	unsigned short m_nMagicNo;
	//CString m_szEndianness;


};

typedef CAutoDeleteArrayHelper<CExifData>	CExifDataArray;