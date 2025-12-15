// 	test_layout_and_special_members.cpp
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
	layout_and_special_members_tester
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void 	test_layout_and_special_members()	{
		cout << color_output::blue 
		<< "-------------- I'm " << __PRETTY_FUNCTION__ << " of Polygon_type_traits"  
		<< color_output::reset 
		<< endl;
	struct S5a_Triv 		{ S5a_Triv() = default; };
	layout_and_special_members_tester<S5a_Triv>("struct S5a_Triv { S5a_Triv() = default; }");
}
