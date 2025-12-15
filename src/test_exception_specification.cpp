// 	test_exception_specification.cpp
/*
	
*/
#include <iostream>
using std::cout; using std::endl;
#include <type_traits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "..\include\umbrella_header.hpp"

using namespace	chat_gpt_seh;
/*
	*********************************************************************************************************************
	exception specification type test
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
// ---------- Add / modify test-types below ---------------
struct S_ok 				{ int a; double b; };           			// 	trivial, standard-layout, pod
struct S_user_ctor 		{ S_user_ctor() {} int a; }; 			// 	non-trivial: user-provided ctor
struct S_deleted_ctor 	{ S_deleted_ctor() = delete; int x; }; 	// 	trivial per standard (deleted ctor is not user-provided)
struct S_user_dtor 		{ ~S_user_dtor() {} int a; }; 			// 	non-trivial: user dtor
struct S_virtual 		{ virtual void f(){} int a; }; 			// 	non-trivial, not standard-layout

// 	example with `defaulted ctor` (still trivial if defaulted and not user-provided)
struct S_defaulted { S_defaulted() = default; int a; };

// 	generic wrapper to print type by name (we pass string manually)
void test_exception_specification()	{
	cout << color_output::blue 
		<< "-------------- I'm " << __PRETTY_FUNCTION__ << " of Polygon_type_traits"  
		<< color_output::reset 
		<< endl;
		
	cout << "Type traits interactive mini-tester (C++20)\n\n";

    is_nothrow_tester<S_ok>				(" S_ok           ");
    is_nothrow_tester<S_user_ctor>		(" S_user_ctor    ");
    is_nothrow_tester<S_deleted_ctor>		(" S_deleted_ctor ");
    is_nothrow_tester<S_user_dtor>		(" S_user_dtor    ");
    is_nothrow_tester<S_virtual>			(" S_virtual      ");
    is_nothrow_tester<S_defaulted>		(" S_defaulted    ");
}
