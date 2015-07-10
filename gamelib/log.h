#ifndef GLIB_LOG_H
#define GLIB_LOG_H

namespace glib {
	// Signal program termination.
	class GlibFatalException {
	};

	void Log( const String & str );			// Debugging log message.
	void Warn( const String & str );		// Warning - simply a different level of the Log function (for filtering primarily)
	void Error( const String & str );		// Fatal - simply a different level of the Log function (for filtering primarily)
}

#endif // GLIB_LOG_H