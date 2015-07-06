#include "pch.h"

namespace glib {
	static void InternalLog( const GLibString & str ) {
#ifdef _MSC_VER
		::OutputDebugString( str.c_str() );
#else
	#error Implement Logger for this platform!
#endif
	}

	// Log
	void Log( const GLibString & str ) {
#if defined( _DEBUG )
		InternalLog( str );
#endif
	}

	// Warn
	void Warn( const GLibString & str ) {
		InternalLog( GLibString( "Warning: " ) + str );
	}

	// Error
	void Error( const GLibString & str ) {
		InternalLog( GLibString( "Error: " ) + str );
#ifdef _MSC_VER
		DebugBreak();
#else
	#error Implement Error for this platform!
#endif
	}
}