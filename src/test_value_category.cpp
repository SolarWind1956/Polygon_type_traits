// 	test_value_category.cpp
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
	******************************************************************************************************
	value category of expression test 
	---------------------------------------------------------------------------------------------------------------------------------------------------
*/
template <typename T>
T	templ_func_ret_value(){
	cout << "-------------- I'm " <<  __PRETTY_FUNCTION__  << endl;
	return T{};
}
template <typename T>
struct AnyStruct{
	T 	m_any_field{T{}};
};

void test_value_category(){
	cout << color_output::blue 
		<< "-------------- I'm " << __PRETTY_FUNCTION__ << " of Polygon_type_traits"  
		<< color_output::reset 
		<< endl;
	
	/*
		--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	*/
	cout << " ********************************************************	 `r-value` " << endl;
	/*
	К категории `r-value` относятся следующие выражения,
	являющиеся `pr-value` или `x-value`:	
	
	-	чисто математические значения (например, 7 или символ 'а'), 
		которые не обязательно имеют связанное с ними место хранения;
		они существуют только для вычислений, 
		но после того, как они были использованы, 
		на них нельзя ссылаться. 
*/
	cout << "  Тип 'a' == " << type_names_tester<decltype('a')>() << endl;	
	cout_test_result(value_category<decltype(('a'))>());
	static_assert(is_rvalue_expr_v<decltype(('a'))>);
	static_assert(is_prvalue_expr_v<decltype(('a'))>);
/*	
	- 	любые `литеральные значения`, за исключением `строковых литералов` 
		(например, 7, 'а', true, nullptr), являются r-значениями, 
		как и результаты многих встроенных арифметических вычислений
		(например, х + 5 для `х` целочисленного типа).
*/
	cout << "  Тип 'true' == " << type_names_tester<decltype(true)>() << endl;	
	cout_test_result(value_category<decltype((true))>());
	static_assert(is_rvalue_expr_v<decltype((true))>);
	static_assert(is_prvalue_expr_v<decltype((true))>);
	
	cout << "  Тип 'nullptr' == " << type_names_tester<decltype(nullptr)>() << endl;	
	cout_test_result(value_category<decltype((nullptr))>());
	static_assert(is_rvalue_expr_v<decltype((nullptr))>);
	static_assert(is_prvalue_expr_v<decltype((nullptr))>);
	
	cout << "  Тип '7 + true' == " << type_names_tester<decltype(7 + true)>() << endl;	
	cout_test_result(value_category<decltype((7 + true))>());
	static_assert(is_rvalue_expr_v<decltype((7 + true))>);
	static_assert(is_prvalue_expr_v<decltype((7 + true))>);

/*
	-	вызовов функций, возвращающих результат "по значению". 
*/
	cout << "  Тип 'templ_func_ret_value<double>()' == " 
			<< type_names_tester<decltype(templ_func_ret_value<double>())>() << endl;	
	cout_test_result(value_category<decltype((templ_func_ret_value<double>()))>());
	static_assert(is_rvalue_expr_v<decltype((templ_func_ret_value<double>()))>);
	static_assert(is_prvalue_expr_v<decltype((templ_func_ret_value<double>()))>);
/*	
	-	все `временные значения` являются `r-значениями`.
		(Хотя это не относится к именованным ссылкам, которые ссылаются на них.)
*/
	cout << "  Тип 'AnyStruct<int>{42}' == " << type_names_tester<decltype(AnyStruct<int>{42})>() << endl;	
	cout_test_result(value_category<decltype((AnyStruct<int>{42}))>());
	static_assert(is_rvalue_expr_v<decltype((AnyStruct<int>{42}))>);
	static_assert(is_prvalue_expr_v<decltype((AnyStruct<int>{42}))>);
/*
	--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
	cout << " ********************************************************	 `l-value` " << endl;
/*
	К категории `l-value` относятся следующие выражения:

	-	`имя переменной`, `функции` или `поле класса` любого типа. 
*/
	double dbl_var{3.14};
	cout << "  Тип `double dbl_var{3.14}` == " 
		<< type_names_tester<decltype(dbl_var)>() << endl;	
	cout_test_result(value_category<decltype((dbl_var))>());
	//auto cat_chgpt	=	value_category_chgpt<decltype((dbl_var))>;
	/*
		In instantiation of 
		'constexpr const std::pair<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char> > 
		chat_gpt_seh::value_category_chgpt<double&>':

		required from here
		
		auto cat_chgpt  =       value_category_chgpt<decltype((dbl_var))>;
      
		error: the type 
		'const std::pair<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char> >' 
		of 
		'constexpr' variable 'chat_gpt_seh::value_category_chgpt<double&>' is not literal
		note: 'std::pair<std::__cxx11::basic_string<char>, std::__cxx11::basic_string<char> >' is not literal because:
		
		constexpr variable 
		cannot have `non-literal type` 
		'const pair_return_type' (aka 'const pair<basic_string<char>, basic_string<char>>')

	*/
	
	static_assert(is_lvalue_expr_v<decltype((dbl_var))>);
	static_assert(is_glvalue_expr_v<decltype((dbl_var))>);
	
	cout << "  Тип 'templ_func_ret_value<int>' == " 
			<< type_names_tester<decltype(templ_func_ret_value<int>)>() << endl;	
	cout_test_result(value_category<decltype((templ_func_ret_value<int>))>());
	static_assert(is_lvalue_expr_v<decltype((templ_func_ret_value<int>))>);
	static_assert(is_glvalue_expr_v<decltype((templ_func_ret_value<int>))>);
	
	AnyStruct<int>	any_struct{42};
	cout << "  Тип `any_struct.m_any_field` == " 
		<< type_names_tester<decltype(any_struct.m_any_field)>() << endl;	
	cout_test_result(value_category<decltype((any_struct.m_any_field))>());
	static_assert(is_lvalue_expr_v<decltype((any_struct.m_any_field))>);
	static_assert(is_glvalue_expr_v<decltype((any_struct.m_any_field))>);
/*	
		Даже если 'переменная' является `r-value`-ссылкой, 
		'имя этой переменной' в выражении является `l-value`;
*/
	int&&	r_value_ref	=	42;
	cout << "  Тип `auto&&	r_value_ref	=	42` == " 
		<< type_names_tester<decltype(r_value_ref)>() << endl;	
	cout_test_result(value_category<decltype((r_value_ref))>());
	static_assert(is_lvalue_expr_v<decltype((r_value_ref))>);
	static_assert(is_glvalue_expr_v<decltype((r_value_ref))>);
/*
	-	вызов функции или перегруженного оператора, 
		возвращающего `l-value`-ссылку, 
		либо выражение преобразования к типу `l-value`-ссылки;
		
	-	`встроенные операторы присваивания`, 
		составные операторы присваивания (=, +=, /= и т. д.), 
		`встроенные преинкремент` и `предекремент` (++a, --b), 
		`встроенный оператор разыменования указателя` (*ptr);
		
	-	`встроенный оператор обращения по индексу` (a[n] или n[a]), 
		когда один из операндов – `l-value` массив;
		
	-	вызов функции или перегруженного оператора, 
		возвращающего `r-value`-ссылку на функцию;

	-	строковый литерал, например "Hello, world!".
*/
	cout << "  Тип строкового литерала `Hello, world!` == " 
		<< type_names_tester<decltype("Hello, world!")>() << endl;	
	cout_test_result(value_category<decltype(("Hello, world!"))>());
	static_assert(is_lvalue_expr_v<decltype(("Hello, world!"))>);
	static_assert(is_glvalue_expr_v<decltype(("Hello, world!"))>);
/*
		`Строковый литерал` отличается от всех остальных литералов в языке C++ именно тем, 
		что является `l-value` (хотя и неизменяемым). 
		
		Например, можно получить его адрес:

		auto * 	ptr = &”Hello, world!”; 			// 	тут `константный указатель`, на самом деле
*/
/*
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
	cout << "********************************************************		`x-value`" << endl;
/*
	
	Примеры выражений категории `x-value`:

	-	вызов функции или встроенного оператора, 
		возвращающего `r-value`-ссылку, 
		например std::move(x);

		и в самом деле, для результата вызова std::move() 
		нельзя получить адрес в памяти 
		или 
		инициализировать им ссылку, 
		
		но в то же время, это выражение может быть полиморфным.
*/
	std::string 	s 		= "hello";
	[[maybe_unused]]
	auto&& 		rref_s 	= std::move(s); 	// 	`rref_s` ссылается на объект `s`, превращая его в "подвижный"
	cout << "string s = `hello`;  Тип  == std::move(s); " 
		<< type_names_tester<decltype(std::move(s))>() << endl;	
	cout_test_result(value_category<decltype((std::move(s)))>());
	static_assert(is_xvalue_expr_v<decltype((std::move(s)))>);
	static_assert(is_glvalue_and_rvalue_expr_v<decltype((std::move(s)))>);
/*		
	-	встроенный оператор обращения по индексу (a[n] или n[a]), 
		когда один из операндов – `r-value`-массив.	
*/		
/*
	-----------------------------------------------------------------------------------------------------------------------------------------------------------------
*/		
	cout << "********************************************************	  `pr-value`" << endl;	
/*
	К категории 'pr-value' относятся следующие выражения:

	-	литерал (кроме строкового), например `42`, `true` или `nullptr`;
	
	-	вызов функции или перегруженного оператора, 
		который возвращает не ссылку 
		
		(str.substr(1, 2), str1 + str2, it++) 
		
		или выражение преобразования к нессылочному типу 
		
		(например static_cast<double>(x), std::string{}, (int)42);
		
	-	`встроенные постинкремент` и `постдекремент` (a++, b--), 
		`встроенные математические операции` (a + b, a % b, a & b, a << b, и т.д.), 
		`встроенные логические операции` (a && b, a || b, !a, и т.д.), 
		`операции сравнения` (a < b, a == b, a >= b, и т.д.), 
		`встроенная операция взятия адреса` (&a);

	-	указатель `this`;

	-	`элемент перечисления`;

	-	`нетиповой параметр шаблона`, если он – не класс;
	
	-	`лямбда-выражение`, например [](int x){ return x * x; }.
*/
	auto any_lambda	=	[](int x){ return x * x; };
	cout << "auto any_lambda	=	[](int x){ return x * x; };  Тип  any_lambda ==  " 
		<< type_names_tester<decltype(any_lambda(11))>() << endl;	
	cout_test_result(value_category<decltype((any_lambda(11)))>());
	static_assert(is_prvalue_expr_v<decltype((any_lambda(11)))>);
	static_assert(is_rvalue_expr_v<decltype((any_lambda(11)))>);
}
