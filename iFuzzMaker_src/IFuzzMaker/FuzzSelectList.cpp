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

// FuzzSelectList.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "FuzzSelectList.h"

// CFuzzSelectList
IMPLEMENT_DYNAMIC(CFuzzSelectList, CGroupListCtrl)

CFuzzSelectList::CFuzzSelectList()
{
	m_lpUserDatas = NULL;
}

CFuzzSelectList::~CFuzzSelectList()
{
}


BEGIN_MESSAGE_MAP(CFuzzSelectList, CGroupListCtrl)
END_MESSAGE_MAP()


// CFuzzSelectList ���b�Z�[�W �n���h���[
BOOL CFuzzSelectList::InitCtrl()
{
	CGroupListCtrl::InitCtrl();

	InsertColumn( COL_TAGID, _T("�^�O/�}�[�J�["), LVCFMT_LEFT, 100 );
	InsertColumn( COL_TAGNAME, _T("�^�O��/�Z�O�����g�v�f"), LVCFMT_LEFT, 150 );
	InsertColumn( COL_WRITEMODE, _T("�������[�h"), LVCFMT_LEFT, 80 );
	InsertColumn( COL_FUZZAREA, _T("�ύX�ӏ�"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_FUZZDISPNAME, _T("���[����"), LVCFMT_LEFT, 150 );
	InsertColumn( COL_FUZZDESCRIPTION, _T("����"), LVCFMT_LEFT, 250 );

	return TRUE;
}

BOOL CFuzzSelectList::SetListData( CUserDatas *lpUserDatas, int nGroupMode )
{
	int nItem = 0;
	CString szBuffer;

	m_lpUserDatas = lpUserDatas;
	EnableItemChangedEvent( FALSE );
	SetRedraw( FALSE );
	m_lpUserDatas->SetCheckedFuzzDataCount( 0 );
	for( int nFuzzData=0; nFuzzData<lpUserDatas->GetFuzzDataArray().GetSize(); nFuzzData++ )
	{
		CFuzzData* lpFuzzData = lpUserDatas->GetFuzzDataArray().GetAt( nFuzzData );
		
		InsertItem( nItem, _T(""), 0, 0 );
		SetCheck( nItem, TRUE );
		SetItemData( nItem, (DWORD_PTR)lpFuzzData );

		switch(lpFuzzData->GetFuzzDataType())
		{
		case CFuzzData::FUZZDATA_TYPE_FIELDENTRY:
			SetItemText( nItem, COL_TAGID, lpFuzzData->GetFealdEntryData()->GetTagID() );
			if( lpFuzzData->GetFealdEntryData()->GetFealdEntryInfo() )
				szBuffer = lpFuzzData->GetFealdEntryData()->GetFealdEntryInfo()->GetTagName();
			else
				szBuffer = _T("Unknown");
			break;
		case CFuzzData::FUZZDATA_TYPE_SEGMENT:
			SetItemText( nItem, COL_TAGID, lpFuzzData->GetSegmentItemData()->GetMarkerName() );
			if( lpFuzzData->GetSegmentItemData()->GetSegmentItemInfo() )
				szBuffer = lpFuzzData->GetSegmentItemData()->GetSegmentItemInfo()->GetItemName();
			else
				szBuffer = _T("Unknown");
			break;
		case CFuzzData::FUZZDATA_TYPE_FILE:
			SetItemText( nItem, COL_TAGID, _T("File") );
			if( lpFuzzData->GetPatternData()->GetFieldKey()==_T("-1") )
				szBuffer.Format( _T("- �t�@�C������") );
			else
				szBuffer.Format( _T("%s Byte -"), lpFuzzData->GetPatternData()->GetFieldKey() );
			break;
		}
		SetItemText( nItem, COL_TAGNAME, szBuffer );

		switch(lpFuzzData->GetPatternData()->GetWriteMode())
		{
		case CPatternData::WRITEMODE_REPLACE:
			szBuffer = _T("�u��");
			break;
		case CPatternData::WRITEMODE_OVERWRITE:
			szBuffer = _T("�㏑");
			break;
		case CPatternData::WRITEMODE_INSERT:
			szBuffer = _T("�}��");
			break;
		}
		SetItemText( nItem, COL_WRITEMODE, szBuffer );

		switch(lpFuzzData->GetPatternData()->GetFuzzArea())
		{
		case CPatternData::FUZZAREA_TAG:
			szBuffer = _T("�^�O");
			break;
		case CPatternData::FUZZAREA_TYPE:
			szBuffer = _T("�^�C�v");
			break;
		case CPatternData::FUZZAREA_COUNT:
			szBuffer = _T("�J�E���g");
			break;
		case CPatternData::FUZZAREA_VALUE:
			szBuffer = _T("�l");
			break;
		case CPatternData::FUZZAREA_OFFSET:
			szBuffer = _T("�I�t�Z�b�g");
			break;
		case CPatternData::FUZZAREA_SEGMENT:
			szBuffer = _T("�Z�O�����g�v�f");
			break;
		case CPatternData::FUZZAREA_FILE:
			szBuffer = _T("�t�@�C���ʒu�w��");
			break;
		}
		SetItemText( nItem, COL_FUZZAREA, szBuffer );

		SetItemText( nItem, COL_FUZZDISPNAME, lpFuzzData->GetPatternData()->GetDispName() );

		SetItemText( nItem, COL_FUZZDESCRIPTION, lpFuzzData->GetPatternData()->GetDescription() );

		nItem++;
	}
	SetRedraw( TRUE );
	EnableItemChangedEvent( TRUE );
	SetSelectedItem( 0 );

	return TRUE;
}

void CFuzzSelectList::OnCheckItem( int nItem, BOOL bCheck )
{
	CFuzzData* lpFuzzData = (CFuzzData*)GetItemData( nItem );
	if( lpFuzzData )
		lpFuzzData->SetCheck( bCheck );
	if( m_lpUserDatas )
		m_lpUserDatas->SetCheckedFuzzDataCount( m_lpUserDatas->GetCheckedFuzzDataCount() + (bCheck?1:-1) );
}

