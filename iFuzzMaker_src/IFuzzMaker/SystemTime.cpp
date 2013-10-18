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

#include "StdAfx.h"
#include "SystemTime.h"

CSystemTime::CSystemTime()
{
	Empty();
}

CSystemTime::CSystemTime( const CSystemTime& source )
{
	Copy( source );
}

CSystemTime::CSystemTime( const CFileTime& source )
{
	Copy( source );
}

CSystemTime::CSystemTime( const CTime& source )
{
	Copy( source );
}

CSystemTime::CSystemTime( const COleDateTime& source )
{
	Copy( source );
}

CSystemTime::CSystemTime( const SYSTEMTIME * source )
{
	Copy( source );
}

CSystemTime::CSystemTime( const TIME_OF_DAY_INFO * source )
{
	Copy( source );
}

CSystemTime::~CSystemTime()
{
	Empty();
}

LONG CSystemTime::Compare( const CSystemTime& source ) const
{
	if ( wYear < source.wYear )
	{
		return( (-1) );
	}

	if ( wYear > source.wYear ) 
	{
		return( 1 );
	}

	if ( wMonth < source.wMonth )
	{
		return( (-1) );
	}

	if ( wMonth > source.wMonth ) 
	{
		return( 1 );
	}

	if ( wDay < source.wDay )
	{
		return( (-1) );
	}

	if ( wDay > source.wDay ) 
	{
		return( 1 );
	}

	if ( wHour < source.wHour )
	{
		return( (-1) );
	}

	if ( wHour > source.wHour ) 
	{
		return( 1 );
	}

	if ( wMinute < source.wMinute )
	{
		return( (-1) );
	}

	if ( wMinute > source.wMinute ) 
	{
		return( 1 );
	}

	if ( wSecond < source.wSecond )
	{
		return( (-1) );
	}

	if ( wSecond > source.wSecond ) 
	{
		return( 1 );
	}

	if ( wMilliseconds < source.wMilliseconds )
	{
		return( (-1) );
	}

	if ( wMilliseconds > source.wMilliseconds ) 
	{
		return( 1 );
	}

	return( 0 );
}

void CSystemTime::Copy( const CSystemTime& source )
{
	Copy( (const SYSTEMTIME *) &source );
}

void CSystemTime::Copy( const SYSTEMTIME * source )
{
	ASSERT( source != NULL );

	if ( source == (const SYSTEMTIME *) NULL )
	{
		Empty();
		return;
	}

	try
	{
		wYear         = source->wYear;
		wMonth        = source->wMonth;
		wDay          = source->wDay;
		wDayOfWeek    = source->wDayOfWeek;
		wHour         = source->wHour;
		wMinute       = source->wMinute;
		wSecond       = source->wSecond;
		wMilliseconds = source->wMilliseconds;
	}
	catch( ... )
	{
		Empty();
	}
}

void CSystemTime::Copy( const CFileTime& source )
{
	Copy( (const FILETIME *) &source );
}

void CSystemTime::Copy( const FILETIME * source )
{
	ASSERT( source != NULL );

	if ( source == (const FILETIME *) NULL )
	{
		Empty();
		return;
	}

	try
	{
		SYSTEMTIME system_time;

		if ( ::FileTimeToSystemTime( source, &system_time ) != FALSE )
		{
			Copy( &system_time );
		}
		else
		{
			Empty();
		}
	}
	catch( ... )
	{
		Empty();
	}
}

void CSystemTime::Copy( const CTime& source )
{
	wYear         = (WORD) source.GetYear();
	wMonth        = (WORD) source.GetMonth();
	wDay          = (WORD) source.GetDay();
	wDayOfWeek    = (WORD) source.GetDayOfWeek();
	wHour         = (WORD) source.GetHour();
	wMinute       = (WORD) source.GetMinute();
	wSecond       = (WORD) source.GetSecond();
	wMilliseconds = 0;
}

void CSystemTime::Copy( const COleDateTime& source )
{
	if ( source.GetStatus() != COleDateTime::valid )
	{
		Empty();
		return;
	}

	wYear         = (WORD) source.GetYear();
	wMonth        = (WORD) source.GetMonth();
	wDay          = (WORD) source.GetDay();
	wDayOfWeek    = (WORD) source.GetDayOfWeek();
	wHour         = (WORD) source.GetHour();
	wMinute       = (WORD) source.GetMinute();
	wSecond       = (WORD) source.GetSecond();
	wMilliseconds = 0;
}

void CSystemTime::Copy( const TIME_OF_DAY_INFO * source )
{
	ASSERT( source != NULL );

	if ( source == (const TIME_OF_DAY_INFO *) NULL )
	{
		Empty();
		return;
	}

	try
	{
		wHour         = (WORD) source->tod_hours;
		wMinute       = (WORD) source->tod_mins;
		wSecond       = (WORD) source->tod_secs;
		wDay          = (WORD) source->tod_day;
		wMonth        = (WORD) source->tod_month;
		wYear         = (WORD) source->tod_year;
		wMilliseconds = (WORD) ( source->tod_hunds * 10 );
	}
	catch( ... )
	{
		Empty();
	}
}

void CSystemTime::CopyTo( COleDateTime& destination ) const
{
	destination = COleDateTime( wYear, wMonth, wDay, wHour, wMinute, wSecond );
}

void CSystemTime::CopyTo( CTime& destination ) const
{
	destination = CTime( wYear, wMonth, wDay, wHour, wMinute, wSecond );
}

void CSystemTime::Empty( void )
{
	wYear         = 0;
	wMonth        = 0;
	wDay          = 0;
	wDayOfWeek    = 0;
	wHour         = 0;
	wMinute       = 0;
	wSecond       = 0;
	wMilliseconds = 0;
}

void CSystemTime::Get( void )
{
	Copy( GetTheCurrentTime() );
}

CSystemTime CSystemTime::GetTheCurrentTime( void )
{
	SYSTEMTIME system_time;

	::GetLocalTime( &system_time );

	return( CSystemTime( &system_time ) );
}

CSystemTime& CSystemTime::operator = ( const CSystemTime& source )
{
	Copy( source );
	return( *this );
}

CSystemTime& CSystemTime::operator = ( const CFileTime& source )
{
	Copy( source );
	return( *this );
}

CSystemTime& CSystemTime::operator = ( const CTime& source )
{
	Copy( source );
	return( *this );
}

CSystemTime& CSystemTime::operator = ( const COleDateTime& source )
{
	Copy( source );
	return( *this );
}

BOOL CSystemTime::operator == ( const CSystemTime& source ) const
{
	if ( Compare( source ) == 0 )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}

BOOL CSystemTime::operator > ( const CSystemTime& source ) const
{
	if ( Compare( source ) > 0 )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}

BOOL CSystemTime::operator < ( const CSystemTime& source ) const
{
	if ( Compare( source ) < 0 )
	{
		return( TRUE );
	}
	else
	{
		return( FALSE );
	}
}