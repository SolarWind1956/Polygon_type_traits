#pragma once
// 	triviality_tester.hpp
#ifndef INCLUDE_GUARDS_triviality_tester_HPP
#define INCLUDE_GUARDS_triviality_tester_HPP

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
void triviality_tester(const std::string& name) {
	using namespace color_output;
	
    using U [[maybe_unused]] = T;
	
	auto row = [&](const char* label, bool v)
    {
        cout << "  " << std::left << std::setw(40) << label
                  << (v ? green : red)
                  << (v ? "Yes" : "No")
                  << reset << "\n";
    };
	
	cout << bright_yellow << "\n========== Triviality Tester ==========" << reset << "\n";
    cout << cyan << "Type: " << reset << name << "\n\n";
	
	// 	--------------------------------------------
    // 	HIGH-LEVEL CLASSIFICATION
    // 	--------------------------------------------
    bool is_triv    						= 	std::is_trivial_v						<U>;
	bool is_standard 					= 	std::is_standard_layout_v					<U>;
	[[maybe_unused]]
	bool is_pod 							= 	(is_triv && is_standard); 						// 	for reporting
#if 0	
	bool is_pod                   		= 	std::is_pod_v							<U>;  	// 	historical	
#endif	
          
	cout << bright_white << "[ High-level classification ]\n" << reset;
	
	row("std::is_trivial_v",                	std::is_trivial_v						<U>);
	row("std::is_trivially_copyable_v",     	std::is_trivially_copyable_v				<U>);
	row("std::is_trivially_constructible_v",  	std::is_trivially_constructible_v			<U>);
	
    row("std::is_standard_layout_v",        	std::is_standard_layout_v					<U>);
    row("std::is_pod_v (historical)",       	is_pod);
	row("std::is_aggregate_v",       			std::is_aggregate_v						<U>);

    cout << "\n";
	
	// 	--------------------------------------------------------
    // 	SPECIAL MEMBER FUNCTIONS
    // 	--------------------------------------------------------
	
	cout << bright_white << "[ Special member triviality ]\n" << reset;

    row("Default constructor trivial",    	std::is_trivially_default_constructible_v	<U>);
    row("Destructor trivial",                	std::is_trivially_destructible_v			<U>);
	
    row("Copy constructor trivial",          	std::is_trivially_copy_constructible_v		<U>);
	row("Copy assignment trivial",           	std::is_trivially_copy_assignable_v		<U>);
	
    row("Move constructor trivial",          	std::is_trivially_move_constructible_v		<U>);
    row("Move assignment trivial",           	std::is_trivially_move_assignable_v		<U>);

    cout << "\n";

    // 	--------------------------------------------------------------------------------------------------------------------
    // 	USER-PROVIDED DETECTION (approximate, heuristic)
    // 	--------------------------------------------------------------------------------------------------------------------
    // 	Эти проверки не определяются стандартом напрямую.
    // 	Но если default ctor НЕ тривиальный, но exists → он user-provided.
    // 	Это эвристика, но 99% случаев правильно работает.

    cout << bright_white << "[ Heuristics: user-provided members ]\n" << reset;

    auto user_row = [&](const char* label, bool trivial, bool is_constructible)
    {
        // приблизительно: если существует, но не trivial → user-provided
        bool user_provided = (is_constructible && !trivial);

        cout << "  " << std::left << std::setw(40) << label
                  << (user_provided ? yellow : green)
                  << (user_provided ? "USER-PROVIDED" : "OK")
                  << reset << "\n";
    };
	
    user_row("Default constructor", std::is_trivially_default_constructible_v<U>,
             std::is_default_constructible_v<U>);

    user_row("Destructor", std::is_trivially_destructible_v			<U>,
             std::is_destructible_v<U>);

	bool 	has_user_dtor 				= 	std::is_destructible_v					<U> 
										&& 	!std::is_trivially_destructible_v			<U>
										&&  !std::is_trivially_copyable_v				<U>; 	
	user_row("User Defined Destructor", has_user_dtor,
             std::is_destructible_v<U>);
		
	user_row("Copy constructor", std::is_trivially_copy_constructible_v		<U>,
             std::is_copy_constructible_v<U>);

    user_row("Move constructor", std::is_trivially_move_constructible_v<U>,
             std::is_move_constructible_v<U>);

    user_row("Copy assignment", std::is_trivially_copy_assignable_v<U>,
             std::is_copy_assignable_v<U>);

    user_row("Move assignment", std::is_trivially_move_assignable_v		<U>,
             std::is_move_assignable_v<U>);

	//	С этим нужно будет поработать позже
	//bool default_constructible 			= 	std::is_default_constructible_v			<U>;
	
	//bool is_nothrow_default_constructible	=	std::is_nothrow_default_constructible_v	<U>;


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
    if (is_triv)
        cout << green  << "                                TRIVIAL\n" << reset;
    else
        cout << red    << "                                NON-TRIVIAL\n" << reset;

    cout << "  Full POD (trivial + standard layout): ";
    if (is_triv && is_standard)
        cout << green << "  YES\n" << reset;
    else
        cout << red   << "  NO\n" << reset;
}	
//	--------------------------------------------------------------------------------------------------------
}	//	end of the 	namespace	chat_gpt_seh;
//	--------------------------------------------------------------------------------------------------------
#endif	//	#ifndef INCLUDE_GUARDS_triviality_tester_HPP
