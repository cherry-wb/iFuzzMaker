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

#include "FileReader.h"
#include "SegmentData.h"
#include "PatternGroupData.h"
#include "FuzzData.h"
#include "SystemTime.h"

class CUserDatas
{
public:
	CUserDatas(void);
	~CUserDatas(void);

	CReadBufferArray& GetReadBufferArray();
	CSegmentDataArray& GetSegmentDataArray();
	CPatternGroupDataArray& GetPatternGroupDataArray();
	CFuzzDataArray& GetFuzzDataArray();
	CSystemTime& GetCreateFuzzTime();

	void SetCheckedFealdEntryDataCount( int nCheckedFealdEntryDataCount );
	int GetCheckedFealdEntryDataCount();

	void SetCheckedSegmentItemDataCount( int nCheckedSegmentItemDataCount );
	int GetCheckedSegmentItemDataCount();

	void SetCheckedPatternDataCount( int nCheckedPatternDataCount );
	int GetCheckedPatternDataCount();

	void SetCheckedFuzzDataCount( int nCheckedFuzzDataCount );
	int GetCheckedFuzzDataCount();

	void SetJpegFileName( CString szJpegFileName );
	CString GetJpegFileName();

	void SetGroupFileName( CString szGroupFileName );
	CString GetGroupFileName();

	void SetOutputFolder( CString szOutputFolder );
	CString GetOutputFolder();

	void SetDiscription( CString szDiscription );
	CString GetDiscription();

	void SetFuzzCreateing( BOOL bFuzzCreateing );
	BOOL GetFuzzCreateing();
	

	void Clear();

public:
	CString m_szJpegFileName;
	CString m_szGroupFileName;
	CString m_szOutputFolder;
	CString m_szDiscription;

	CReadBufferArray m_ReadBufferArray;
	CSegmentDataArray m_SegmentDataArray;
	CPatternGroupDataArray m_PatternGroupDataArray;
	CFuzzDataArray m_FuzzDataArray;
	CSystemTime m_CreateFuzzTime;

	int m_nCheckedFealdEntryDataCount;
	int m_nCheckedSegmentItemDataCount;
	int m_nCheckedPatternDataCount;
	int m_nCheckedFuzzDataCount;

	BOOL m_bFuzzCreateing;
};

