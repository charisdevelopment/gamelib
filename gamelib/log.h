#ifndef GLIB_LOG_H
#define GLIB_LOG_H

namespace glib {
	void Log( const GLibString & str );
	void Warn( const GLibString & str );
	void Error( const GLibString & str );
}

#endif // GLIB_LOG_H