cmake_minimum_required	(VERSION 3.20...3.30.1)	# Our version 3.30.1

set(CMAKE_VERBOSE_MAKEFILE ON)
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# -----------------------------------------------------------------------------------------------
# Выбор компилятора 
# ----------------------------------------------------------------------------------------------- 
#set(CMAKE_LANG_COMPILER_ID "Clang")
#SET (CMAKE_CXX_COMPILER "C:/msys64/clang64/bin/clang++.exe") 

SET (CMAKE_CXX_COMPILER "C:/msys64/mingw64/bin/g++.exe") 
set(CMAKE_GNU_COMPILER_ID "GNU") 

message ("Выбранный компилятор: ${CMAKE_CXX_COMPILER}") 
# -----------------------------------------------------------------------------------------------
message	("================================================ Loading MAIN CMakeLists.txt")
set	(PROJECT_NAME "Polygon_type_traits_console_project")
project	(
	${PROJECT_NAME} 
	VERSION 1.1.1.1 
	DESCRIPTION "Polygon_type_traits console project"
	LANGUAGES C CXX
)
message	("CMAKE_VERSION: ${CMAKE_VERSION}")
message	("${PROJECT_NAME}_VERSION: ${${PROJECT_NAME}_VERSION}")

set	(TARGET_NAME "Polygon_type_traits")

# ---------------------------------------------------------------
# 4. Output directories
# ---------------------------------------------------------------
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
message	("Paths to additional CMake modules ${CMAKE_MODULE_PATH}")

message	("TEST_VARIABLE is equal to [${TEST_VARIABLE}]")
# Запустить скрипт MyCMakeScript.cmake на выполнение:
include	(MyCMakeScript) # Этот скрипт, кроме всего, установит переменную TEST_VARIABLE в значение 42
message	("TEST_VARIABLE is equal to [${TEST_VARIABLE}]")

#	-----------------------------------------------------------------------------------------------
#	Подключаем Скрипт включения заголовочных файлов
include	(Includes)

#	-----------------------------------------------------------------------------------------------
#	Подключаем Скрипт включения библиотек
add_subdirectory	(lib)			#	Соберем библиотеку

#	Запускаем сборку исполняемого файла
add_executable	(${TARGET_NAME})

#	Подключаем Скрипт выбора и настройки компиляторов
include	(ProjectConfig)

add_subdirectory	(src)			

target_link_libraries	(${TARGET_NAME})

message	("-------------------------------------------------- Finished MAIN CMakeLists.txt")