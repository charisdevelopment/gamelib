#ifndef GLIB_PCH_H
#define GLIB_PCH_H

// WIN32 shenanigans
#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN

#endif // _MSC_VER

#include "stdafx.h"
#include "gamelib.h"

#endif // GLIB_PCH_H