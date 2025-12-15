// 	test_triviality.cpp
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
	trivially type test
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
void test_triviality()	{
	cout << color_output::blue 
		<< "-------------- I'm " << __PRETTY_FUNCTION__ << " of Polygon_type_traits"  
		<< color_output::reset 
		<< endl;
		
	cout << "Type traits interactive mini-tester (C++20)\n\n";

    triviality_tester<S_ok>				(" S_ok           ");
    triviality_tester<S_user_ctor>		(" S_user_ctor    ");
    triviality_tester<S_deleted_ctor>		(" S_deleted_ctor ");
    triviality_tester<S_user_dtor>		(" S_user_dtor    ");
    triviality_tester<S_virtual>			(" S_virtual      ");
    triviality_tester<S_defaulted>		(" S_defaulted    ");

    // 	----- How to add own types:
    cout << "\n To test your own type: ";
	cout << "\n add its definition in main-file above ";
	cout << "\n and call triviality_tester<YourType>(\"YourType\");\n\n";

    // 	Optional: if you want to include your own uploaded header (uncomment and adjust the path)
    // 	#include "path/to/your/header.hpp"
    // 	then call triviality_tester<MyType>("MyType");
}
