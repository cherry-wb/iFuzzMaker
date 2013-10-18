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

// CreateLogList.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "CreateLogList.h"

// CCreateLogList
IMPLEMENT_DYNAMIC(CCreateLogList, CGroupListCtrl)

CCreateLogList::CCreateLogList()
{

}

CCreateLogList::~CCreateLogList()
{
}


BEGIN_MESSAGE_MAP(CCreateLogList, CGroupListCtrl)
END_MESSAGE_MAP()


// CCreateLogList ���b�Z�[�W �n���h���[
BOOL CCreateLogList::InitCtrl()
{
	CGroupListCtrl::InitCtrl();
	SetExtendedStyle(GetExtendedStyle() & ~LVS_EX_CHECKBOXES );

	InsertColumn( COL_ICON, _T(""), LVCFMT_LEFT, 20 );
	InsertColumn( COL_DATETIME, _T("����"), LVCFMT_LEFT, 140 );
	InsertColumn( COL_STATUS, _T("���"), LVCFMT_LEFT, 80 );
	InsertColumn( COL_TAG, _T("�^�O/�}�[�J�["), LVCFMT_LEFT, 100 );
	InsertColumn( COL_PATTERN, _T("���[����"), LVCFMT_LEFT, 200 );
	InsertColumn( COL_FILENAME, _T("�t�@�C����"), LVCFMT_LEFT, 180 );

	m_ImageList.Create(16, 16, ILC_COLOR24|ILC_MASK, 0, 0);
	CBitmap bmp;
    bmp.LoadBitmap( IDB_FUZZ_CREATE_BITMAP );
    m_ImageList.Add( &bmp, RGB(255, 0, 255) );
	SetImageList( &m_ImageList, LVSIL_SMALL );

	return TRUE;
}
