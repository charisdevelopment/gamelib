#include "pch.h"

namespace glib {
	void _glibassert(const char * expression, const char * file, int line) {
		glib::Log( GLibString( "ASSERTION FAILURE: " ) + expression + " " + file + " " + line );
		DebugBreak();
	}
}