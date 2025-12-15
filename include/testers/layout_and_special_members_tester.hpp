//	layout_and_special_members_tester.hpp
#pragma once
#include <type_traits>
#include <iostream>
#include <string_view>
#include <cstddef> 					// 	offsetof

#include "../color_output.hpp"
#include "sizeof_and_alignof.hpp"
#include "type_names_tester.hpp"

namespace	chat_gpt_seh
{
	
template<typename T>
void 	layout_and_special_members_tester(std::string_view 	header = "")
{
    using namespace std;

    cout << bright_white << "\n===== layout_and_special_members_tester<"
         << type_names_tester<T>() << "> =====\n" << reset;

    if (!header.empty())
        cout << header << "\n";

    // --------------------------------------------------------------
    // 	Special members
    // --------------------------------------------------------------
    auto status = [&](bool trivial, bool exists)
    {
        if (trivial) 	cout << green << "[trivial]" << reset;
		else 
        if (exists)  	cout << bright_yellow << "[non-trivial]" << reset;
		else 			cout << bright_blue << "[non-trivial]" << reset;
        return       "";
    };

    cout << color_output::yellow << "\n[ Special members ]\n" << color_output::reset;

    cout << "  default ctor       : "
         << status(is_trivially_default_constructible_v<T>,
                   is_default_constructible_v<T>) << "\n";

    cout << "  copy ctor          : "
         << status(is_trivially_copy_constructible_v<T>,
                   is_copy_constructible_v<T>) << "\n";

    cout << "  move ctor          : "
         << status(is_trivially_move_constructible_v<T>,
                   is_move_constructible_v<T>) << "\n";

    cout << "  copy assign        : "
         << status(is_trivially_copy_assignable_v<T>,
                   is_copy_assignable_v<T>) << "\n";

    cout << "  move assign        : "
         << status(is_trivially_move_assignable_v<T>,
                   is_move_assignable_v<T>) << "\n";

    cout << "  destructor         : "
         << status(is_trivially_destructible_v<T>,
                   is_destructible_v<T>) << "\n";

    // --------------------------------------------------------------
    // 	Triviality sets
    // --------------------------------------------------------------
    cout << color_output::yellow << "\n[ Triviality sets ]\n" << color_output::reset;

	auto row = [&](const char* label, bool v)
    {
        cout << std::left << std::setw(15) << label
             << (v ? green : red)
             << (v ? "Yes" : "No")
             << reset << "\n";
    };
    row("  trivial            : ", is_trivial_v<T>);

    row("  trivially copyable : ", is_trivially_copyable_v<T>);

    row("  standard-layout    : ", is_standard_layout_v<T>);

    row("  aggregate          : ", is_aggregate_v<T>);

    row("  POD                : ", (is_trivial_v<T> && is_standard_layout_v<T>));
    // --------------------------------------------------------------
    // 	Layout info
    // --------------------------------------------------------------
    cout << color_output::yellow << "\n[ Layout ]\n" << color_output::reset;

    row("  is_empty           : ", is_empty_v<T>);

// 	-----------------------------------------------------------------------------------------------------------------------
    // 	SIZEOF AND ALIGNOF 
	// 	-----------------------------------------------------------------------------------------------------------------------
	sizeof_and_alignof<T>(" header    : ", 12);
	
	
    cout << color_output::blue << "===== end tester =====\n" << color_output::reset;
	
	
}
//	--------------------------------------------------------------------------------------------------------
};	//	End of the 	namespace	chat_gpt_seh;