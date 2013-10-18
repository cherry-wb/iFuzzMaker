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
#include "FealdEntryData.h"
#include "SegmentItemData.h"
#include "PatternData.h"
#include "SystemTime.h"

class CFuzzData
{
public:
	CFuzzData(void);
	~CFuzzData(void);

	CSystemTime &GetCreateDateTime();

	enum
	{
		FUZZDATA_TYPE_FIELDENTRY,
		FUZZDATA_TYPE_SEGMENT,
		FUZZDATA_TYPE_FILE,
		FUZZDATA_TYPE_COUNT,
	};

	void SetCheck( BOOL bCheck );
	BOOL GetCheck();

	void SetFileName( CString szFileName );
	CString GetFileName();

	void SetFilePath( CString szFilePath );
	CString GetFilePath();

	void SetFuzzDataType( int nFuzzDataType );
	int GetFuzzDataType();

	void SetFealdEntryData( CFealdEntryData *lpFealdEntryData );
	CFealdEntryData* GetFealdEntryData();

	void SetSegmentItemData( CSegmentItemData *lpSegmentItemData );
	CSegmentItemData* GetSegmentItemData();

	void SetPatternData( CPatternData *lpPatternData );
	CPatternData* GetPatternData();

	void SetCounter( int nCounter );
	int GetCounter();

	void SetErrorMessage( CString szErrorMessage );
	CString GetErrorMessage();

protected:
	BOOL m_bCheck;
	CString m_szFileName;
	CString m_szFilePath;

	int m_nFuzzDataType;

	CFealdEntryData *m_lpFealdEntryData;
	CSegmentItemData *m_lpSegmentItemData;
	CPatternData* m_lpPatternData;

	CSystemTime m_CreateDateTime;
	int m_nCounter;
	CString m_szErrorMessage;

};

typedef CAutoDeleteArrayHelper<CFuzzData>	CFuzzDataArray;