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

#pragma once
#include "ReadData.h"
#include "AutoDeleteArrayHelper.h"
#include "SegmentItemInfo.h"

class CSegmentItemData : public CReadData
{
public:
	CSegmentItemData(void);
	~CSegmentItemData(void);

	enum{
		ITEM_TYPE_FILE,		//	0:�\����`�t�@�C��
		ITEM_TYPE_BYTE,		//	1:8�r�b�g�̐��l�^(BYTE)
		ITEM_TYPE_ASCII,	//	2:8�r�b�g�̃L�����N�^�^(ASCII)
		ITEM_TYPE_SHORT,	//	3:16�r�b�g�̐��l�^(SHORT)
		ITEM_TYPE_LONG,		//	4:32�r�b�g�̐��l�^(LONG)
	};

	void SetCheck( BOOL bCheck );
	BOOL GetCheck();

	void SetSegmentItemInfo( CSegmentItemInfo *lpSegmentItemInfo );
	CSegmentItemInfo *GetSegmentItemInfo();

	void SetMarkerName( CString szMarkerName );
	CString GetMarkerName();

	void SetItemName( CString szItemName );
	CString GetItemName();

protected:
	CSegmentItemInfo *m_lpSegmentItemInfo;
	CString m_szMarkerName;
	CString m_szItemName;
	BOOL m_bCheck;

};

typedef CAutoDeleteArrayHelper<CSegmentItemData>	CSegmentItemDataArray;