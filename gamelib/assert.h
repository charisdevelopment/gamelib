#ifndef GLIB_ASSERT_H
#define GLIB_ASSERT_H

// Define assert.
namespace glib {
	void _glibAssert( const char * expression, const char * file, int line );
}

#if defined (_DEBUG )
#define glibAssert(EX) (void)((EX) || (glib::_glibAssert (#EX, __FILE__, __LINE__),0));
#else
#define glibAssert(EX) (EX)
#endif // _DEBUG

#endif // GLIB_ASSERT_H