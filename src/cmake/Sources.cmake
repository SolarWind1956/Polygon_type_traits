cmake_minimum_required(VERSION 3.20...3.30.1)	# Our version 3.30.1

message	("===================================================== Loading Sources.cmake")

#	-----------------------------------------------------------------------------------------------
#	Перечисляем имена исходников 
set	(SOURCE_FILES_LST	 
	${SOURCE_FILES_DIR}main.cpp 
	${SOURCE_FILES_DIR}test_triviality.cpp
	${SOURCE_FILES_DIR}test_value_category.cpp
	${SOURCE_FILES_DIR}test_type_properties.cpp
	${SOURCE_FILES_DIR}test_layout_and_special_members.cpp
	${SOURCE_FILES_DIR}test_exception_specification.cpp
) 
#	Добавляем список исходников к проекту
target_sources	(	${TARGET_NAME} PUBLIC ${SOURCE_FILES_LST} )
message	("----------------------------------------------------- Finished Sources.cmake")