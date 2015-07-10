// Validation tests for the gamelib library. 
// Ideally these should be implemented in some sort of testing framework. For now however, they are implemented via assertions and exception handling.

#include "stdafx.h"
#include "../gamelib/gamelib.h"

// ListTests
void ListTests() {
	glib::List< int > myList;

	myList.Append( 10 );
	myList.Append( 2 );
	glibAssert( myList.Count() == 2 );
	glibAssert( myList[0] == 10 );
	glibAssert( myList[1] == 2 );

	myList.Pop();
	glibAssert( myList.Count() == 1 );
	glibAssert( myList[0] == 10 );

	myList.Pop();
	glibAssert( myList.Count() == 0 );

	myList.Append( 100 );
	myList.Append( 50 );
	myList.Append( 20 );
	glibAssert( myList.Count() == 3 );

	myList.Remove( 1 );
	glibAssert( myList.Count() == 2 );
	glibAssert( myList[1] == 20 );

	glib::List< int > myCopiedList( myList );
	glibAssert( myCopiedList.Count() == 2 );
	glibAssert( myCopiedList[ 1 ] == 20 );

	// Test static lists.
	glib::StaticList< int, 2 > staticList;
	staticList.Append( 100 );
	staticList.Append( 50 );

	glibAssert( staticList.Count() == 2 );
	bool staticListGrowException = false;
	try {
		staticList.Append( 100 );
	} catch ( const glib::InvalidListOperationException & e ) {
		staticListGrowException = true;
		glibAssert( e.GetClass() == glib::InvalidListOperationException::ExceptionClass::E_CANNOT_RESIZE_STATIC_LIST );
	}

	glibAssert( staticListGrowException == true );
}

// StringTests
void StringTests() {
	glib::String str;
	glibAssert( str.Len() == 0 );

	glib::String construct( "hello world" );
	glibAssert( construct.Len() == 11 );
	glibAssert( construct == "hello world" );
	glibAssert( construct != "hello" );

	construct += " my name is Rom";
	glibAssert(construct == "hello world my name is Rom" );

	construct = "from a cstr";
	glibAssert( construct == "from a cstr" );

	construct = glib::String( "123456789101112131415161718192021222324252627" );
	glibAssert( construct == "123456789101112131415161718192021222324252627" );
}

// Main
int _tmain( int argc, _TCHAR* argv[] ) {
	glib::Log( "Starting tests.\n" );

	try {
		ListTests();
		StringTests();
	} catch ( ... ) {
		// Some exception trickled up all the way up here. Note this and bail.
		glib::Error( "Unhandled exception!\n" );
	}

	return 0;
}