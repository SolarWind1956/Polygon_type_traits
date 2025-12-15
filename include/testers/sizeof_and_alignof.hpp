#pragma once
// 	sizeof_and_alignof.hpp
#ifndef INCLUDE_GUARDS_sizeof_and_alignof_HPP
#define INCLUDE_GUARDS_sizeof_and_alignof_HPP

#include <iostream>
using std::cout; using std::endl;
#include <type_traits>
#include <string>
using std::string;
#include <iomanip>
#include "../color_output.hpp"

namespace chat_gpt_seh {
	
template<typename T>
void sizeof_and_alignof(const std::string& name, int spaces_before) {
	using namespace color_output;
	
    using U [[maybe_unused]]= T;
	
	// 	-----------------------------------------------------------------------------------------------------------------------
    // 	SIZEOF AND ALIGNOF 
	// 	-----------------------------------------------------------------------------------------------------------------------
	size_t 		start 				= name.find_first_not_of(" ");
    size_t 		end 					= name.find_last_not_of(" ");
	std::string 	name_without_spaces 	= "";		// 	Строка состоит только из пробелов
    if (start != std::string::npos && end != std::string::npos) {
        name_without_spaces 			= name.substr(start, end - start + 1);
	}
	int 			space_length 		= spaces_before - name_without_spaces.size();
	
	if (0 >= space_length)  {
		cout		<< bright_red <<	"  Length of name string is too long. Error, exit!!! " << reset << endl; 
		return; 		
	}
		
	cout		<<	"  Size  of " << name_without_spaces 
			<< std::string(space_length, ' ') 
			<< bright_blue << sizeof(T) << reset << endl; 
	cout		<<	"  Align of " << name_without_spaces 
			<< std::string(space_length, ' ') 
			<< bright_blue << alignof(T) << reset << endl;
	cout << "\n";
}
//	--------------------------------------------------------------------------------------------------------
}	//	end of the 	namespace	chat_gpt_seh;
//	--------------------------------------------------------------------------------------------------------
#endif	//	#ifndef INCLUDE_GUARDS_sizeof_and_alignof_HPP
