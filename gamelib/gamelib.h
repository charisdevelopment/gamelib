#ifndef GLIB_H
#define GLIB_H

#include "assert.h"
#include "types.h"
#include "memory.h"
#include "list.h"
#include "string.h"
#include "log.h"

// Memory management
// -----------------
// 1. Need a way to track the heap, and allocations made with new and delete.

// Logging System
// X. Implement crude logging system - to system log.

// Core library functions we need to worry about.
// ----------------------------------------------
// X. Integral types (see: types.h)
// X. String types (see: string.h)
// 3. Container types 
//	a. List
//	b. Map (use stl?)
//	c. Set (use stl?)
// 4. Vector types
// 5. Matrix types
// 6. Basic Math Library (Abs, Sqrt, Trig, etc.)

// Serialization solution
// ----------------------------------------------
// 1. Stream classes

// Threading solution
// ----------------------------------------------
// 1. Threading primitives => wrap/use std::thread internally.

// Job based system.
//------------------
// 1. Create Job System

// Unit testing
//------------------
// 1. Use a Unit Test framework that is cross compatible. For now just use assert.

// Build system.
//---------------
// 1. Determine what build system to use.

#endif // GLIB_H