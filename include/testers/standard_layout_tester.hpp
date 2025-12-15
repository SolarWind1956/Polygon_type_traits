#pragma once
// 	standard_layout_tester.hpp
#ifndef INCLUDE_GUARDS_standard_layout_tester_HPP
#define INCLUDE_GUARDS_standard_layout_tester_HPP

#include <iostream>
using std::cout; using std::endl;
#include <type_traits>
#include <string>
using std::string;
#include <iomanip>
#include "../color_output.hpp"
#include "sizeof_and_alignof.hpp"

namespace chat_gpt_seh {
	
template<typename T>
void standard_layout_tester(const std::string& name) {
	using namespace color_output;
	
    using U = T;
	
	auto row = [&](const char* label, bool v)
    {
        cout << "  " << std::left << std::setw(40) << label
                  << (v ? green : red)
                  << (v ? "Yes" : "No")
                  << reset << "\n";
    };
	
	cout << bright_yellow << "\n========== Standard-layout Tester ==========" << reset << "\n";
    cout << cyan << "Type: " << reset << name << "\n\n";
	
	// 	--------------------------------------------
    // 	HIGH-LEVEL CLASSIFICATION
    // 	--------------------------------------------
    bool is_standard_layout				= 	std::is_standard_layout_v					<U>;
	bool is_trivial 						= 	std::is_trivial_v						<U>;
	bool is_aggregate 					= 	std::is_aggregate_v						<U>;
        
	cout << bright_white << "[ High-level classification ]\n" << reset;
	
    row("std::is_standard_layout",        	is_standard_layout);
	row("std::is_trivial",        			is_trivial);
    row("std::is_aggregate",       			is_aggregate);

    cout << "\n";
	
    // 	-----------------------------------------------------------------------------------------------------------------------
    // 	SIZEOF AND ALIGNOF 
	// 	-----------------------------------------------------------------------------------------------------------------------
	sizeof_and_alignof<T>("name", 31);
    // 	-----------------------------------------------------------------------------------------------------------------------
    // 	SUMMARY
    // 	-----------------------------------------------------------------------------------------------------------------------
	
	cout << bright_white << "[ Summary ]\n" << reset;

	cout << "  Type is ";
    if (is_standard_layout)
        cout << green  << "                                STANDARD-LAYOUT\n" << reset;
    else
        cout << red    << "                                NON-STANDARD-LAYOUT\n" << reset;
	
    cout << "  Type is ";
    if (is_trivial)
        cout << green  << "                                TRIVIAL\n" << reset;
    else
        cout << red    << "                                NON-TRIVIAL\n" << reset;

    cout << "  Full POD (trivial + standard layout): ";
    if (is_trivial && is_standard_layout)
        cout << green << "  YES\n" << reset;
    else
        cout << red   << "  NO\n" << reset;
}	
//	--------------------------------------------------------------------------------------------------------
}	//	end of the 	namespace	chat_gpt_seh;
//	--------------------------------------------------------------------------------------------------------
#endif	//	#ifndef INCLUDE_GUARDS_standard_layout_tester_HPP
