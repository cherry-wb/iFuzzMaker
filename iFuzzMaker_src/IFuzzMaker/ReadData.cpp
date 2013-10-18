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
#include "ReadData.h"

CReadData::CReadData(void)
{
	Clear();
}

CReadData::~CReadData(void)
{
}

void CReadData::SetDataType( unsigned int nDataType )
{
	m_nDataType = nDataType;
}

void CReadData::SetOffset( unsigned int nOffset )
{
	m_nOffset = nOffset;
}

void CReadData::SetSize( unsigned int nSize )
{
	m_nSize = nSize;
}

void CReadData::SetData( unsigned char *lpData )
{
	m_lpData = lpData;
}

unsigned int CReadData::GetDataType()
{
	return m_nDataType;
}

unsigned int CReadData::GetOffset()
{
	return m_nOffset;
}

unsigned int CReadData::GetSize()
{
	return m_nSize;
}

unsigned char *CReadData::GetData()
{
	return m_lpData;
}

BOOL CReadData::QueryOverflow( unsigned int nMaxSize )
{
	m_bOverflow = nMaxSize < m_nOffset + m_nSize; 
	return m_bOverflow;
}

BOOL CReadData::IsOverflow()
{
	return m_bOverflow;
}

void CReadData::Clear()
{
	m_nDataType = 0;
	m_nOffset = 0;
	m_nSize = 0;
	m_lpData = NULL;
	m_bOverflow = FALSE;
}

