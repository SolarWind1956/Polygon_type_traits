//	type_names_tester.hpp
#ifndef INCLUDE_GUARDS_type_names_tester_HPP
#define INCLUDE_GUARDS_type_names_tester_HPP

#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <memory>


#if defined(__clang__)
#   include <c++/v1/cxxabi.h>
#elif defined(__GNUG__)
#   include <cxxabi.h>
#endif

template <typename T>
std::string 	demangle_type_name(const char* name)
{
#if defined(__clang__) || defined(__GNUG__)
    int status = 0;
    std::unique_ptr<char, void(*)(void*)> res{
        abi::__cxa_demangle(name, nullptr, nullptr, &status),
        std::free
    };
    return (status == 0) ? res.get() : name;
#else
    // MSVC возвращает уже "читаемое" имя
    return name;
#endif
}
namespace	chat_gpt_seh
{
template <typename T>
std::string 	type_names_tester()
{
	std::string 	qualifiers;
    if (std::is_const_v<std::remove_reference_t<T>>) {
        qualifiers += "const ";
	}
    if (std::is_volatile_v<std::remove_reference_t<T>>){
        qualifiers += "volatile ";
	}
    using 		base_type 		= 	std::remove_cv_t<std::remove_reference_t<T>>;
    std::string 	type_name 		= 	demangle_type_name<base_type>(typeid(base_type).name());

    std::string ref_type;
    if (std::is_lvalue_reference_v<T>) {
        ref_type = "&";
	}	
    else if (std::is_rvalue_reference_v<T>) {
        ref_type = "&&";
	}	
	return qualifiers + type_name + ref_type;
}


//	--------------------------------------------------------------------------------------------------------
};	//	End of the 	namespace	chat_gpt_seh;
//	--------------------------------------------------------------------------------------------------------
#endif	//	#ifndef INCLUDE_GUARDS_type_names_tester_HPP