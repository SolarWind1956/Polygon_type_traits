// 	main.cpp
/*
	
*/
#include <iostream>
using std::cout; using std::endl;
#include <type_traits>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include "..\include\color_output.hpp"
#include "..\include\umbrella_header.hpp"

using namespace	chat_gpt_seh;

//	Внешние функции, определенный в других единицах трансляции
extern void test_triviality();					//	Тест типов на тривиальность
extern void test_value_category();				//	Тест типов в отношении значений категорий выражений
extern void test_type_properties();				//	Тест группы выборочных свойств типов
extern void test_layout_and_special_members();		//	Тест типов в отношении специальных членов и
												//	стандартной схемы размещения
extern void test_exception_specification();		//	Тест типов в отношении спецификации исключений
												
/*
	******************************************************************************************************
	main()
	---------------------------------------------------------------------------------------------------------------------------------------------------
*/
int main() {
	color_output::init();
    cout << color_output::blue << "-------------- I'm " <<  __PRETTY_FUNCTION__  << color_output::reset << endl; 
	//cout << "-------------- I'm " <<  __PRETTY_FUNCTION__  << endl;
	
	cout << color_output::bright_yellow << "bright_yellow" << color_output::reset << endl;
	cout << color_output::yellow << "yellow" << color_output::reset << endl;
	
	cout << color_output::bright_black << "bright_black" << color_output::reset << endl;
	cout << color_output::black << "black" << color_output::reset << endl;
	
	cout << color_output::bright_white << "bright_white" << color_output::reset << endl;
	cout << color_output::white << "white" << color_output::reset << endl;
	
	//	Тест типов на тривиальность
	test_triviality();
	
	//	Тест типов в отношении значений категорий выражений
	test_value_category();

	//	Тест группы выборочных свойств типов
	test_type_properties();
		
	//	Тест типов в отношении специальных членов и стандартной схемы размещения
	test_layout_and_special_members();	
	
	//	Тест типов в отношении спецификации исключений
	test_exception_specification();
	
	system("pause");
	
    return 0;
}
