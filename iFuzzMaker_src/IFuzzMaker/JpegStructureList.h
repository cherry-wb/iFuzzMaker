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
#include "ColumnTreeCtrl.h"
#include "UserDatas.h"

// CJpegStructureList
class CJpegStructureList : public CColumnTreeCtrl
{
	DECLARE_DYNAMIC(CJpegStructureList)

public:
	CJpegStructureList();
	virtual ~CJpegStructureList();

	enum
	{
		ICON_SEGMENT,
		ICON_IFD,
		ICON_FEALDENTRY,
		ICON_UNKNOWN_SEGMENT,
		ICON_UNKNOWN_IFD,
		ICON_UNKNOWN_FEALDENTRY,
		ICON_IMAGE,
	};

	enum
	{
		COL_NAME,
		COL_OFFSET,
		COL_SIZE,
		COL_MARKER,
		COL_DESCRIPTION,
	};

	BOOL InitCtrl();
	BOOL SetListData( CUserDatas *lpUserDatas );
	BOOL ClearList();

protected:
	DECLARE_MESSAGE_MAP()

	CImageList m_ImageList;
	CFont m_GothicFont;

	virtual COLORREF OnGetCellTextColor( HTREEITEM hItem, int nColumn );
	virtual CFont* OnGetCellFont( HTREEITEM hItem, int nColumn );

};
