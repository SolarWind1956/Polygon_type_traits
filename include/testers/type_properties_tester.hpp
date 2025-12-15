// 	type_properties_tester.hpp
#ifndef INCLUDE_GUARDS_type_properties_tester_HPP
#define INCLUDE_GUARDS_type_properties_tester_HPP
/*
	
*/
#include <iostream>
using std::cout; using std::endl;
#include <type_traits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "../color_output.hpp"
#include "type_names_tester.hpp"

namespace	chat_gpt_seh
{
/*
	*********************************************************************************************************************
	test_type_properties
	-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
template <typename T>
void type_properties_tester()	{
	cout << bright_white << "-------------- I'm " << __PRETTY_FUNCTION__ << reset << endl;
	
	cout << blue << "\n=== Тест свойств типа: " << bright_magenta << type_names_tester<T>() << " ===\n" << reset << endl;

	auto row = [&](const char* label, bool v)
    {
        cout 	<< "  " << std::left << std::setw(40) << label
				<< (v ? green : red)
                << (v ? "Yes" : "No")
                << reset << "\n";
    };
    row("is_const:                ", std::is_const_v			<T>);
    row("is_volatile:             ", std::is_volatile_v		<T>);
    row("is_pointer:              ", std::is_pointer_v			<T>);
    row("is_reference:            ", std::is_reference_v		<T>);
    row("is_lvalue_reference:     ", std::is_lvalue_reference_v	<T>);
    row("is_rvalue_reference:     ", std::is_rvalue_reference_v	<T>);
    row("is_integral:             ", std::is_integral_v		<T>);
    row("is_floating_point:       ", std::is_floating_point_v	<T>);
    row("is_class:                ", std::is_class_v			<T>);
    row("is_enum:                 ", std::is_enum_v			<T>);
    row("is_trivial:              ", std::is_trivial_v			<T>);
    row("is_standard_layout:      ", std::is_standard_layout_v	<T>);
	
	cout << blue << "===== end tester =====\n" << reset;
}

//	--------------------------------------------------------------------------------------------------------
};	//	End of the 	namespace	chat_gpt_seh;
//	--------------------------------------------------------------------------------------------------------
#endif	//	#ifndef INCLUDE_GUARDS_type_properties_tester_HPP
