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
#include "SegmentData.h"
#include "ImageFileDirectoryInfo.h"
#include "TagTypeInfo.h"

class CExifAnalyzer
{
public:
	CExifAnalyzer(void);
	~CExifAnalyzer(void);

	BOOL Analyze( unsigned int nMaxBufferSize, CSegmentData *lpSegmentData, CImageFileDirectoryInfoMap *lpImageFileDirectoryInfoMap, CTagTypeInfoMap *lpTagTypeInfoMap );
	int AnalyzeImageFileDirectory( unsigned char* lpBuffer, unsigned int nOffset, CExifData* lpExifData, CImageFileDirectoryInfo* &lpImageFileDirectoryInfo, unsigned int &nRecursiveCount );

private:
	unsigned int m_nImageFileDirectoryCount;
	unsigned int m_nTiffHeaderOffset;
	unsigned int m_nEndiannessType;
	unsigned int m_nMaxBufferSize;
	unsigned int m_nExifOffset;
	CTagTypeInfoMap *m_lpTagTypeInfoMap;
	CImageFileDirectoryInfoMap *m_lpImageFileDirectoryInfoMap;
	CImageFileDirectoryInfo *m_lpUnknownImageFileDirectoryInfo;
	CImageFileDirectoryInfo *m_lp0thImageFileDirectoryInfo;
	CImageFileDirectoryInfo *m_lp1stImageFileDirectoryInfo;
};

