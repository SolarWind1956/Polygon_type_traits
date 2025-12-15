// 	test_type_properties.cpp
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
	test_type_properties
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void test_type_properties()	{
	cout << color_output::blue 
		<< "-------------- I'm " << __PRETTY_FUNCTION__ << " of Polygon_type_traits"  
		<< color_output::reset 
		<< endl;
	
			int		int_var{11};
	type_properties_tester<decltype(int_var)>();
	
	const	int		cnst_int_var{11};
	type_properties_tester<decltype(cnst_int_var)>();	
	
	int*		int_var_ptr	=	&int_var;
	type_properties_tester<decltype(int_var_ptr)>();
}
