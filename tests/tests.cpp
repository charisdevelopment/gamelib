// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../gamelib/gamelib.h"

// ListTests
void ListTests() {
	glib::GLibList< int > myList;

	myList.Append( 10 );
	myList.Append( 2 );
	glibassert( myList.Count() == 2 );
	glibassert( myList[0] == 10 );
	glibassert( myList[1] == 2 );

	myList.Pop();
	glibassert( myList.Count() == 1 );
	glibassert( myList[0] == 10 );

	myList.Pop();
	glibassert( myList.Count() == 0 );

	myList.Append( 100 );
	myList.Append( 50 );
	myList.Append( 20 );
	glibassert( myList.Count() == 3 );

	myList.Remove( 1 );
	glibassert( myList.Count() == 2 );
	glibassert( myList[1] == 20 );
}

// StringTests
void StringTests() {
	glib::GLibString str;
	glibassert( str.Len() == 0 );

	glib::GLibString construct( "hello world" );
	glibassert( construct.Len() == 11 );
	glibassert( construct == "hello world" );
	glibassert( construct != "hello" );

	construct += " my name is Rom";
	glibassert(construct == "hello world my name is Rom" );
}

// Main
int _tmain( int argc, _TCHAR* argv[] ) {
	glib::Log( "Starting tests.\n" );

	ListTests();
	StringTests();
	return 0;
}