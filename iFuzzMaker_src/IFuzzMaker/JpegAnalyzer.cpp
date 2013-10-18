//================================================================================
//  �Ɨ��s���@�l��񏈗����i�@�\ (IPA)
//  - Information-technology Promotion Agency, Japan -
//
//                                                    �Ɨ��s���@�l��񏈗����i�@�\
//                                                   �Z�p�{�� �Z�L�����e�B�Z���^�[
//                                                ���Z�L�����e�B�Z�p���{���g���[
//
//      -- JPEG �e�X�g�x���c�[�� iFuzzMaker  --
//                                                                Date�F2013/07/30
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
#include "JpegAnalyzer.h"

CJpegAnalyzer::CJpegAnalyzer(void)
{
}


CJpegAnalyzer::~CJpegAnalyzer(void)
{
}

BOOL CJpegAnalyzer::Analyze( CReadBufferArray &ReadBufferArray, CSegmentInfoMap &SegmentInfoMap, CSegmentDataArray &SegmentDataArray )
{
	int nOffset = 0;
	int nMaxBufferSize = ReadBufferArray.GetSize();
	unsigned char *lpBuffer = ReadBufferArray.GetData();
	CString szKey;
	CSegmentInfo *lpSegmentInfo = NULL;
	CSegmentData *lpSegmentData = NULL;
	BOOL bNextSegmentImage = FALSE;

	SegmentDataArray.RemoveAllWithDelete();

	while( nOffset < nMaxBufferSize )
	{
		lpSegmentInfo = NULL;
		lpSegmentData = NULL;

		SegmentDataArray.AddWithNew( lpSegmentData );
		lpSegmentData->SetOffset( nOffset );
		lpSegmentData->SetData( &lpBuffer[nOffset] );

		//	�}�[�J�[����
		if( lpBuffer[nOffset] == 0xFF && nOffset+1 < nMaxBufferSize )
		{
			szKey.Format( _T("%02X%02X"), lpBuffer[nOffset], lpBuffer[nOffset+1] );
			nOffset += 2;
			//	�o�^����Ă���Z�O�����g��
			if( SegmentInfoMap.Lookup( szKey, lpSegmentInfo ) )
			{
				lpSegmentData->SetDataType( CSegmentData::DATATYPE_MARKER );
				lpSegmentData->SetSegmentInfo( lpSegmentInfo );

				//	�����O�X�w�肪����Z�O�����g��
				if( lpSegmentInfo->HasLengthFeeld() )
				{
					if( nOffset+2 >= nMaxBufferSize )
						break;
					nOffset += (lpBuffer[nOffset] << 8) | lpBuffer[nOffset+1];
				}

				bNextSegmentImage = lpSegmentInfo->IsNextSegmentImage();

			}
		}else{
			if( bNextSegmentImage )
			{
				lpSegmentData->SetDataType( CSegmentData::DATATYPE_IMAGE );
			}
			bNextSegmentImage = FALSE;
		}
		if( !lpSegmentInfo )
		{
			while( nOffset < nMaxBufferSize )
			{
				nOffset++;
				if( lpBuffer[nOffset] == 0xFF )
				{
					if( nOffset+1 < nMaxBufferSize )
					{
						szKey.Format( _T("%02X%02X"), lpBuffer[nOffset], lpBuffer[nOffset+1] );
						if( SegmentInfoMap.Lookup( szKey, lpSegmentInfo ) )
						{
							break;
						}
					}
				}
			}
		}
		lpSegmentData->SetSize( nOffset - lpSegmentData->GetOffset() );
	}
	if( lpSegmentData )
	{
		if( lpSegmentData->GetSize() == 0 )
			lpSegmentData->SetSize( nMaxBufferSize - lpSegmentData->GetOffset() );
	}

	return TRUE;
}
