// tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../gamelib/gamelib.h"

// ArrayTests
void ArrayTests() {
	glib::GLibArray< int > myArray;

	myArray.Append( 10 );
	myArray.Append( 2 );
	glibassert( myArray.Count() == 2 );
	glibassert(myArray[0] == 10);
	glibassert(myArray[1] == 2);

	myArray.Pop();
	glibassert(myArray.Count() == 1);
	glibassert(myArray[0] == 10);

	myArray.Pop();
	glibassert(myArray.Count() == 0);

	myArray.Append( 100 );
	myArray.Append( 50 );
	myArray.Append( 20 );
	glibassert(myArray.Count() == 3);

	myArray.Remove(1);
	glibassert(myArray.Count() == 2);
	glibassert(myArray[1] == 20);
}

// Test the string class.
void StringTests() {
	glib::GLibString str;
	glibassert( str.Len() == 0 );

	glib::GLibString construct( "hello world" );
	glibassert( construct.Len() == 11 );
	glibassert( construct == "hello world" );
	glibassert( construct != "hello" );

	//construct += " my name is Rom";
	glibassert(construct == "hello world my name is Rom" );
}

// Main
int _tmain(int argc, _TCHAR* argv[]) {
	ArrayTests();
	StringTests();
	return 0;
}