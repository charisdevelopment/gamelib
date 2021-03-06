#ifndef GLIB_STRING_H
#define GLIB_STRING_H

#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "types.h"

namespace glib {
	/* 
		TODO: 
		X. Assignment operator.
		X. Copy constructor
		3. += operator, + operator between char *, GLibString
		4. Conversion from int / char / float / bool
	*/

	// glib::String
	class String {
	public:
		//========================================================
		String() : m_str( nullptr ), m_len(0) {}

		//========================================================
		String( const char * s ) {
			m_len = static_cast< int >( strlen( s ) );
			m_str = new char[ m_len + 1 ];
#ifndef _MSC_VER
			strcpy( m_str, s );
#else
			strcpy_s( m_str, m_len + 1, s );
#endif
		}

		//========================================================
		String( const char c ) {
			m_len = 1;
			m_str = new char[ m_len + 1 ];
			m_str[ 0 ] = c;
		}

		//========================================================
		String( const int i ) {
			char buffer[ 32 ];
#ifndef _MSC_VER
			_itoa( i, buffer, 10 );
#else
			_itoa_s( i, buffer, 32, 10 );
#endif
			_AssignFromCStr( buffer );
		}

		//========================================================
		String( const float f ) {
			// TODO: Implement.
			glibAssert( false );
		}

		//========================================================
		String( const String & other ) : String( other.c_str() ) {}

		//========================================================
		~String() {
			delete[] m_str;
		}

		//========================================================
		// operator +
		String & operator + ( const String & str ) {
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
		void operator = ( const String & str ) {
			// optimize against heap fragmentation when possible.
			// otherwise, 
			if ( m_len < str.m_len ) {
				delete[] m_str;

				m_len = str.m_len;
				m_str = new char[ str.m_len + 1 ];
			}

#if defined (_MSC_VER)
			strcpy_s( m_str, m_len + 1, str.m_str );
#else
			strcpy( m_str, str.m_str );
#endif
		}

		//========================================================
		void operator = ( const char * cstr ) {
			int len = static_cast< int >( strlen( cstr ) );

			if ( m_len < len ) {
				delete[] m_str;

				m_len = len;
				m_str = new char[ m_len + 1 ];
			}

#if defined (_MSC_VER)
			strcpy_s( m_str, m_len + 1, cstr );
#else
			strcpy( m_str, cstr );
#endif
		}

		//========================================================
		inline bool operator == (const String & str) {
			return strcmp( m_str, str.c_str() ) == 0;
		}

		//========================================================
		inline bool operator != (const String & str) {
			return strcmp( m_str, str.c_str() ) != 0;
		}

		//========================================================
		inline int Len() const { return m_len; }

		//========================================================
		inline const char * c_str() const { return m_str; }

		//========================================================
		inline char operator[] (const int index) {
			glibAssert( index >= 0 && index < Len() );
			return m_str[ index ];
		}

		//========================================================
		inline String & operator += ( const String & rhs ) {
			return ( *this + rhs );
		}

	private:
		char * m_str;
		int m_len;

		//========================================================
		// know what you are doing before calling this function! Doesn't clean up the internal array.
		void _AssignFromCStr(const char * str) {
			m_len = static_cast< int >( strlen( str ) );
			m_str = new char[ m_len + 1 ];
#if defined( _MSC_VER )
			strcpy_s( m_str, m_len + 1, str );
#else
			strcpy( m_str, str );
#endif
		}
	};

}	// namespace glib

#endif // GLIB_STRING_H