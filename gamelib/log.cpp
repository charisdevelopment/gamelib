#include "pch.h"

namespace glib {
	//-----------------------------------------------------
	// InternalLog
	//-----------------------------------------------------
	static void InternalLog( const String & str ) {
#ifdef _MSC_VER
		::OutputDebugString( str.c_str() );
#else
	#error Implement Logger for this platform!
#endif
	}

	//-----------------------------------------------------
	// Log
	//-----------------------------------------------------
	void Log( const String & str ) {
#if defined( _DEBUG )
		InternalLog( str );
#endif
	}

	//-----------------------------------------------------
	// Warn
	//-----------------------------------------------------
	void Warn( const String & str ) {
		InternalLog( String( "Warning: " ) + str );
	}

	//-----------------------------------------------------
	// Error
	//-----------------------------------------------------
	void Error( const String & str ) {
		InternalLog( String( "Error: " ) + str );
#ifdef _MSC_VER
		// DebugBreak();
#else
#error Implement Error for this platform!
#endif

		// TODO: Make errors halt!
	}
}