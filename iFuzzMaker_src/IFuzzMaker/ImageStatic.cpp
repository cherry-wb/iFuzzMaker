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

// ImageStatic.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "ImageStatic.h"

// CImageStatic
IMPLEMENT_DYNAMIC(CImageStatic, CStatic)

CImageStatic::CImageStatic()
{

}

CImageStatic::~CImageStatic()
{
}

BEGIN_MESSAGE_MAP(CImageStatic, CStatic)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CImageStatic ���b�Z�[�W �n���h���[
void CImageStatic::SetBitmap( int nID, COLORREF bkColor )
{
	m_Bitmap.LoadBitmap(nID);
	m_BkColor = bkColor;
}

BOOL CImageStatic::OnEraseBkgnd( CDC* pDC )
{
	CRect rectClient;
	GetClientRect(rectClient);
	pDC->FillRect( rectClient, &afxGlobalData.brBarFace );

	return TRUE;
}

void CImageStatic::OnPaint()
{
	CPaintDC dc(this);

	BITMAP bmp;
	m_Bitmap.GetBitmap(&bmp);

	CDC cDC;
	cDC.CreateCompatibleDC( &dc );
	CBitmap *pOldBitmap = cDC.SelectObject(&m_Bitmap);

	dc.TransparentBlt(0, 0, bmp.bmWidth, bmp.bmHeight,
			&cDC, 0, 0, bmp.bmWidth, bmp.bmHeight, m_BkColor );
		
	if (pOldBitmap) {
		cDC.SelectObject(pOldBitmap);
	}
}
