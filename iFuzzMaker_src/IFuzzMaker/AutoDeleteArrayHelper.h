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
#include "afxtempl.h"

template <class ARG_TYPE>
class CAutoDeleteArrayHelper : public CArray<ARG_TYPE*, ARG_TYPE*>
{
public:

	CAutoDeleteArrayHelper(void)
	{
		m_bIsAutoDelete = TRUE;
	}

	~CAutoDeleteArrayHelper(void)
	{
		if( m_bIsAutoDelete )
			RemoveAllWithDelete();
	}

	void SetAutoDelete( BOOL bIsAutoDelete )
	{
		m_bIsAutoDelete = bIsAutoDelete;
	}

	BOOL IsAutoDelete()
	{
		return m_bIsAutoDelete;
	}

	INT_PTR AddWithNew( ARG_TYPE* &lpElement )
	{
		if( m_bIsAutoDelete )
			lpElement = new ARG_TYPE();
		return CArray<ARG_TYPE*, ARG_TYPE*>::Add( lpElement );
	}

	void InsertAtWithNew( INT_PTR nIndex, ARG_TYPE* &lpElement, INT_PTR nCount = 1 )
	{
		if( m_bIsAutoDelete )
			lpElement = new ARG_TYPE();
		CArray<ARG_TYPE*, ARG_TYPE*>::InsertAtWithNew( nIndex, lpElement, nCount );
	}

	void InsertAtWithNew( INT_PTR nStartIndex, ARG_TYPE* &lpElement )
	{
		if( m_bIsAutoDelete )
			lpElement = new ARG_TYPE();
		CArray<ARG_TYPE*, ARG_TYPE*>::InsertAtWithNew( nStartIndex, lpElement );
	}

	void RemoveAtWithDelete( INT_PTR nIndex, INT_PTR nCount = 1 )
	{
		int nCnt = 0;
		ARG_TYPE* lpElement = NULL;
		for( nCnt=nIndex; nCnt<nIndex+nCount; nCnt++ )
		{
			lpElement = CArray<ARG_TYPE*, ARG_TYPE*>::GetAt( nCnt );
			if( m_bIsAutoDelete && lpElement )
				delete lpElement;
		}
		CArray<ARG_TYPE*, ARG_TYPE*>::RemoveAt( nIndex, nCount );
	}

	void RemoveAllWithDelete()
	{
		if( m_bIsAutoDelete )
			RemoveAtWithDelete( 0, CArray<ARG_TYPE*, ARG_TYPE*>::GetSize() );
		RemoveAll();
	}

	int Find( ARG_TYPE* lpElement )
	{
		int nCnt = 0;
		for( nCnt=0; nCnt<CArray<ARG_TYPE*, ARG_TYPE*>::GetCount(); nCnt++ )
		{
			if( CArray<ARG_TYPE*, ARG_TYPE*>::GetAt( nCnt ) == lpElement )
				return nCnt;
		}
		return -1;
	}

protected:
	BOOL m_bIsAutoDelete;

};

