message	("=================================================== Loading MyCMakeScript.cmake")
set (TEST_VARIABLE 42)

if	(WIN32)
	message	(STATUS "Building for Windows")
endif()

#	Замечание: при обработке проектов система CMake создаёт переменные с именами вида 
#	имя_проекта_SOURCE_DIR
message	("${PROJECT_NAME}_SOURCE_DIR: ${${PROJECT_NAME}_SOURCE_DIR}")
message	("${TARGET_NAME}_SOURCE_DIR: ${${PROJECT_NAME}_SOURCE_DIR}")

#set	(ENV{PATH} "$ENV{PATH};${CMAKE_BINARY_DIR}")
#message	("New ENV{PATH} $ENV{PATH}")

message	("CMAKE_RUNTIME_OUTPUT_DIRECTORY:	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message	("CMAKE_ARCHIVE_OUTPUT_DIRECTORY:	${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
message	("CMAKE_LIBRARY_OUTPUT_DIRECTORY:	${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")

message	("--------------------------------------------------- Finished MyCMakeScript.cmake")