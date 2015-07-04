#include "pch.h"

namespace glib {
	void Log( const GLibString & str ) {
#ifdef _MSC_VER
		::OutputDebugString( str.c_str() );
#else
		#error Implement Logger for this platform!
#endif
	}
}