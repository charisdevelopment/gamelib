#ifndef GLIB_STRING_H
#define GLIB_STRING_H

#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "types.h"

namespace glib {
	/* 
		TODO: 
		1. Assignment operator.
		X. Copy constructor
		3. += operator, + operator between char *, GLibString
		4. Conversion from int / char / float / bool
	*/

	// GlibString
	class GLibString {
	public:
		//========================================================
		GLibString() : m_str(nullptr), m_len(0) {}

		//========================================================
		GLibString( const char * s ) {
			m_len = strlen( s );
			m_str = new char[ m_len + 1 ];
#ifndef _MSC_VER
			strcpy( m_str, s );
#else
			strcpy_s( m_str, m_len + 1, s );
#endif
		}

		//========================================================
		GLibString( const char c ) {
			m_len = 1;
			m_str = new char[ m_len + 1 ];
			m_str[ 0 ] = c;
		}

		//========================================================
		GLibString( const int i ) {
			char buffer[ 32 ];
#ifndef _MSC_VER
			_itoa( i, buffer, 10 );
#else
			_itoa_s( i, buffer, 32, 10 );
#endif
			_AssignFromCStr( buffer );
		}

		//========================================================
		GLibString( const GLibString & other ) : GLibString( other.c_str() ) {}

		//========================================================
		~GLibString() {
			delete[] m_str;
		}

		//========================================================
		// operator +
		GLibString & operator + ( const GLibString & str ) {
			int newLen = Len() + str.Len();
			char * newStr = new char[ newLen + 1 ];
#if defined (_MSC_VER )
			strcpy_s( newStr, newLen + 1, m_str );
			strcat_s( newStr, newLen + 1, str.c_str() );
#else
			strcpy( newStr, m_str );
			strcat( newStr, str.c_str() );
#endif
			delete[] m_str;

			m_str = newStr;
			m_len = newLen;
			return *this;
		}

		//========================================================
		bool operator == (const GLibString & str) {
			return strcmp( m_str, str.c_str() ) == 0;
		}

		//========================================================
		bool operator != (const GLibString & str) {
			return strcmp( m_str, str.c_str() ) != 0;
		}

		//========================================================
		int Len() const { return m_len; }

		//========================================================
		const char * c_str() const { return m_str; }

		//========================================================
		char operator[] (const int index) {
			glibassert( index >= 0 && index < Len() );
			return m_str[ index ];
		}

	private:
		char * m_str;
		int m_len;

		//========================================================
		// know what you are doing before calling this function! Doesn't clean up the internal array.
		void _AssignFromCStr(const char * str) {
			m_len = strlen( str );
			m_str = new char[ m_len + 1 ];
#if defined( _MSC_VER )
			strcpy_s( m_str, m_len + 1, str );
#else
			strcpy( m_str, str );
#endif
		}
	};

	//inline GLibString & operator += ( GLibString & lhs, const GLibString & rhs ) {
	//	return lhs + rhs;
	//}

}	// namespace glib

#endif // GLIB_STRING_H