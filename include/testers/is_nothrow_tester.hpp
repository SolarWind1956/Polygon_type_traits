#pragma once
// 	is_nothrow_tester.hpp
#ifndef INCLUDE_GUARDS_is_nothrow_tester_HPP
#define INCLUDE_GUARDS_is_nothrow_tester_HPP

#include <iostream>
using std::cout; using std::endl;
#include <type_traits>
#include <string>
using std::string;
#include <iomanip>
#include "../color_output.hpp"

namespace chat_gpt_seh {
	
template<typename T1, typename T2 = T1>
void is_nothrow_tester(const std::string& name) {
	using namespace color_output;
	
    using U 		[[maybe_unused]] = T1;
	using WITH 	[[maybe_unused]] = T2;
	using FROM 	[[maybe_unused]] = T1;
	using TO 	[[maybe_unused]] = T2;
	
	auto row = [&](const char* label, bool v)
    {
        cout << "  " << std::left << std::setw(40) << label
                  << (v ? green : red)
                  << (v ? "Yes" : "No")
                  << reset << "\n";
    };
	
	cout << bright_yellow << "\n========== Exception specification (is_nothrow) Tester ==========" << reset << "\n";
    cout << cyan << "Type: " << reset << name << "\n";
	
	// 	--------------------------------------------
    // 	Exception specification
    // 	--------------------------------------------
	
	cout << bright_white << "------------------------------------------------------------\n" << reset;
	
	row("std::is_nothrow_assignable",         	std::is_nothrow_assignable_v				<U&, U const&>);
	row("std::is_nothrow_copy_assignable",        	std::is_nothrow_copy_assignable_v			<U>);
	row("std::is_nothrow_move_assignable",        	std::is_nothrow_move_assignable_v			<U>);
	
	row("std::is_nothrow_constructible",         	std::is_nothrow_constructible_v			<U>);
	row("std::is_nothrow_default_constructible",  	std::is_nothrow_default_constructible_v	<U>);
	row("std::is_nothrow_copy_constructible",     	std::is_nothrow_copy_constructible_v		<U>);
	row("std::is_nothrow_move_constructible",     	std::is_nothrow_move_constructible_v		<U>);
	
	row("std::is_nothrow_destructible",         	std::is_nothrow_destructible_v			<U>);

	
	row("std::is_nothrow_swappable_with",     		std::is_nothrow_swappable_with_v 			<U, WITH>);
	row("std::is_nothrow_swappable",     			std::is_nothrow_swappable_v				<U>);
	
	row("std::is_nothrow_convertible",     		std::is_nothrow_convertible_v 			<FROM, TO>);
	
	cout << bright_white << "------------------------------------------------------------\n" << reset;
    cout << endl;
}	
//	--------------------------------------------------------------------------------------------------------
}	//	end of the 	namespace	chat_gpt_seh;
//	--------------------------------------------------------------------------------------------------------
#endif	//	#ifndef INCLUDE_GUARDS_is_nothrow_tester_HPP
