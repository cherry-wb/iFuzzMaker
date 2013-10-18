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


// PatternSelectList.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "PatternSelectList.h"
#include "AppMessage.h"

// CPatternSelectList
IMPLEMENT_DYNAMIC(CPatternSelectList, CGroupListCtrl)

CPatternSelectList::CPatternSelectList()
{
	m_lpUserDatas = NULL;
}

CPatternSelectList::~CPatternSelectList()
{
}

BEGIN_MESSAGE_MAP(CPatternSelectList, CGroupListCtrl)
END_MESSAGE_MAP()


// CPatternSelectList ���b�Z�[�W �n���h���[
BOOL CPatternSelectList::InitCtrl()
{
	CGroupListCtrl::InitCtrl();

	InsertColumn( COL_DISPNAME, _T("���[����"), LVCFMT_LEFT, 150 );
	InsertColumn( COL_DATATYPE, _T("�f�[�^�`��"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_VALUE, _T("�l"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_REPEAT, _T("�J�Ԃ���"), LVCFMT_RIGHT, 60 );
	InsertColumn( COL_WRITEMODE, _T("�������[�h"), LVCFMT_LEFT, 70 );
	InsertColumn( COL_FUZZAREA, _T("�ύX�ӏ�"), LVCFMT_LEFT, 80 );
	InsertColumn( COL_SEARCHFIELD, _T("�ύX�ӏ��w��"), LVCFMT_LEFT, 90 );
	InsertColumn( COL_FIELDKEY, _T("�ΏەύX�ӏ�"), LVCFMT_LEFT, 100 );
	InsertColumn( COL_DESCRIPTION, _T("����"), LVCFMT_LEFT, 200 );

	return TRUE;
}

BOOL CPatternSelectList::SetListData( CUserDatas *lpUserDatas )
{
	int nGroup = 0;
	int nItem = 0;
	CString szBuffer;

	m_lpUserDatas = lpUserDatas;

	ClearList();
	EnableGroupView( TRUE );
	m_lpUserDatas->SetCheckedPatternDataCount( 0 );
	for( int nPatternGroupData=0; nPatternGroupData<lpUserDatas->GetPatternGroupDataArray().GetSize(); nPatternGroupData++ )
	{
		CPatternGroupData* lpPatternGroupData = lpUserDatas->GetPatternGroupDataArray().GetAt(nPatternGroupData);
		nGroup = InsertGroup( nPatternGroupData, lpPatternGroupData->GetDispName() );

		for( int nPatternData=0; nPatternData<lpPatternGroupData->GetPatternDataArray()->GetSize(); nPatternData++ )
		{
			CPatternData* lpPatternData = lpPatternGroupData->GetPatternDataArray()->GetAt(nPatternData);
			InsertItem( nItem, lpPatternData->GetDispName(), 0, nGroup );

			SetItemData( nItem, (DWORD_PTR)lpPatternData );

			SetCheck( nItem, lpPatternData->GetCheck() );

			switch(lpPatternData->GetDataType())
			{
			case CPatternData::DATATYPE_TEXT:
				szBuffer = _T("�e�L�X�g");
				break;
			case CPatternData::DATATYPE_DEC_8:
				szBuffer = _T("10�i��(8)");
				break;
			case CPatternData::DATATYPE_DEC_16_LITTLE:
				szBuffer = _T("10�i��(16II)");
				break;
			case CPatternData::DATATYPE_DEC_16_BIG:
				szBuffer = _T("10�i��(16MM)");
				break;
			case CPatternData::DATATYPE_DEC_32_LITTLE:
				szBuffer = _T("10�i��(32II)");
				break;
			case CPatternData::DATATYPE_DEC_32_BIG:
				szBuffer = _T("10�i��(32MM)");
				break;
			case CPatternData::DATATYPE_HEX:
				szBuffer = _T("16�i��");
				break;
			case CPatternData::DATATYPE_BIN:
				szBuffer = _T("�t�@�C��(�o�C�i��)");
				break;
			default:
				szBuffer = _T("�s��");
			}
			SetItemText( nItem, COL_DATATYPE, szBuffer );

			CString szWork;
			szBuffer = _T("");
			switch(lpPatternData->GetDataType())
			{
			case CPatternData::DATATYPE_TEXT:
				szBuffer = lpPatternData->GetValue();
				break;
			case CPatternData::DATATYPE_DEC_8:
			case CPatternData::DATATYPE_DEC_16_LITTLE:
			case CPatternData::DATATYPE_DEC_16_BIG:
			case CPatternData::DATATYPE_DEC_32_LITTLE:
			case CPatternData::DATATYPE_DEC_32_BIG:
				szBuffer = lpPatternData->GetValue();
				break;
			case CPatternData::DATATYPE_HEX:
				szBuffer = lpPatternData->GetValue();
				break;
			case CPatternData::DATATYPE_BIN:
				for( int nReadCnt=0; nReadCnt<lpPatternData->GetBinaryDataArray()->GetSize(); nReadCnt++ )
				{
					szWork.Format( _T("%02X "), lpPatternData->GetBinaryDataArray()->GetAt(nReadCnt) );
					szBuffer += szWork;
				}
				break;
			default:
				szBuffer = _T("");
			}
			SetItemText( nItem, COL_VALUE, szBuffer );

			if( lpPatternData->GetRepeat() == 0 )
				szBuffer = _T("n");
			else
				szBuffer.Format( _T("%d"), lpPatternData->GetRepeat() );
			SetItemText( nItem, COL_REPEAT, szBuffer );

			switch( lpPatternData->GetWriteMode() )
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

			switch(lpPatternData->GetFuzzArea())
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
				szBuffer = _T("�t�@�C���w��ʒu");
				break;
			}
			SetItemText( nItem, COL_FUZZAREA, szBuffer );

			switch(lpPatternData->GetSearchField())
			{
			case CPatternData::SEARCHFIELD_NONE:
				szBuffer = _T("�Ȃ�");
				break;
			case CPatternData::SEARCHFIELD_TAG:
				szBuffer = _T("�^�O");
				break;
			case CPatternData::SEARCHFIELD_TYPE:
				szBuffer = _T("�^�C�v");
				break;
			case CPatternData::SEARCHFIELD_SEGMENT:
				szBuffer = _T("�v�f");
				break;
			case CPatternData::SEARCHFIELD_FILE:
				szBuffer = _T("�t�@�C���ʒu");
				break;
			}
			SetItemText( nItem, COL_SEARCHFIELD, szBuffer );

			if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_NONE )
				szBuffer = _T("");
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TAG && lpPatternData->GetFealdEntryInfo() )
				szBuffer.Format( _T("%s : %s"), lpPatternData->GetFieldKey(), lpPatternData->GetFealdEntryInfo()->GetTagName() );
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TYPE && lpPatternData->GetTagTypeInfo() )
				szBuffer.Format( _T("%s : %s"), lpPatternData->GetFieldKey(), lpPatternData->GetTagTypeInfo()->GetTagTypeName() );
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_SEGMENT && lpPatternData->GetSegmentItemInfo() )
				szBuffer = lpPatternData->GetSegmentItemInfo()->GetItemName();
			else if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_FILE )
				szBuffer.Format( _T("%s"), lpPatternData->GetFieldKey()==_T("-1")?_T("�t�@�C������"):lpPatternData->GetFieldKey() );
			else
				szBuffer.Format( _T("%s : Unknown"), lpPatternData->GetFieldKey() );
			SetItemText( nItem, COL_FIELDKEY, szBuffer );
			SetItemText( nItem, COL_DESCRIPTION, lpPatternData->GetDescription() );
			nItem++;
		}
	}

	return TRUE;
}

void CPatternSelectList::OnCheckItem( int nItem, BOOL bCheck )
{
	CPatternData *lpPatternData = (CPatternData*)GetItemData( nItem );
	if( lpPatternData )
		lpPatternData->SetCheck( bCheck );
	if( m_lpUserDatas )
		m_lpUserDatas->SetCheckedPatternDataCount( m_lpUserDatas->GetCheckedPatternDataCount() + (bCheck?1:-1) );
}
