#ifndef GLIB_ASSERT_H
#define GLIB_ASSERT_H

// Define assert.
namespace glib {
	void _glibassert( const char * expression, const char * file, int line );
}

#if defined (_DEBUG )
#define glibassert(EX) (void)((EX) || (glib::_glibassert (#EX, __FILE__, __LINE__),0));
#else
#define glibassert(EX) (EX)
#endif // _DEBUG

#endif // GLIB_ASSERT_H