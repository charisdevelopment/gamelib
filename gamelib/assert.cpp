#include "pch.h"

namespace glib {
	void _glibAssert(const char * expression, const char * file, int line) {
		glib::Log( String( "ASSERTION FAILURE: " ) + expression + " " + file + " " + line );
		DebugBreak();
	}
}