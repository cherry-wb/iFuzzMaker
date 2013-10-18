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

#include "AutoDeleteArrayHelper.h"
#include "FileReader.h"
#include "FealdEntryInfo.h"
#include "TagTypeInfo.h"
#include "SegmentItemInfo.h"

class CPatternData
{
public:
	CPatternData(void);
	~CPatternData(void);

	enum
	{
		DATATYPE_TEXT,
		DATATYPE_DEC_8,
		DATATYPE_DEC_16_LITTLE,
		DATATYPE_DEC_16_BIG,
		DATATYPE_DEC_32_LITTLE,
		DATATYPE_DEC_32_BIG,
		DATATYPE_HEX,
		DATATYPE_BIN,
	};

	enum {
		ENDIAN_CONV_NONE,
		ENDIAN_CONV_BIG,
		ENDIAN_CONV_LITTLE,
		ENDIAN_CONV_BOTH,
	};

	enum {
		FUZZAREA_NONE,
		FUZZAREA_TAG,
		FUZZAREA_TYPE,
		FUZZAREA_COUNT,
		FUZZAREA_VALUE,
		FUZZAREA_OFFSET,
		FUZZAREA_SEGMENT,
		FUZZAREA_FILE,
	};

	enum {
		WRITEMODE_REPLACE,
		WRITEMODE_OVERWRITE,
		WRITEMODE_INSERT,
	};

	enum {
		SEARCHFIELD_NONE,
		SEARCHFIELD_TAG,
		SEARCHFIELD_TYPE,
		SEARCHFIELD_SEGMENT,
		SEARCHFIELD_FILE,
	};

	void SetCheck( BOOL bCheck );
	BOOL GetCheck();

	void SetDispName( CString szDispName );
	CString GetDispName();

	void SetDataType( int nDataType );
	int GetDataType();

	void SetValue( CString szValue );
	CString GetValue();

	void SetRepeat( int nRepeat );
	int GetRepeat();

	void SetWriteMode( int nWriteMode );
	int GetWriteMode();

	void SetFuzzArea( int nFuzzArea );
	int GetFuzzArea();

	void SetSearchField( int nSearchField );
	int GetSearchField();

	void SetFieldKey( CString szFieldKey);
	CString GetFieldKey();

	void SetFilePos( int nFilePos );
	int GetFilePos();

	void SetDescription( CString szDescription );
	CString GetDescription();

	void SetBinaryDataArray( CReadBufferArray &BinaryDataArray );
	CReadBufferArray* GetBinaryDataArray();

	void SetFealdEntryInfo( CFealdEntryInfo* lpFealdEntryInfo );
	CFealdEntryInfo* GetFealdEntryInfo();

	void SetTagTypeInfo( CTagTypeInfo* lpTagTypeInfo );
	CTagTypeInfo* GetTagTypeInfo();

	void SetSegmentItemInfo( CSegmentItemInfo* lpSegmentItemInfo );
	CSegmentItemInfo* GetSegmentItemInfo();

protected:
	BOOL m_bCheck;
	CString  m_szDispName;
	int m_nDataType;
	CString m_szValue;
	int m_nRepeat;
	int m_nWriteMode;
	int m_nFuzzArea;
	int m_nSearchField;
	CString m_szFieldKey;

	int m_nFilePos;

	CString m_szDescription;
	CReadBufferArray m_BinaryDataArray;

	CFealdEntryInfo* m_lpFealdEntryInfo;
	CTagTypeInfo* m_lpTagTypeInfo;
	CSegmentItemInfo* m_lpSegmentItemInfo;

};

typedef CAutoDeleteArrayHelper<CPatternData>	CPatternDataArray;
