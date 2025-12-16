![logo](images/Logo_SolarWind.png)

📂 Структура проекта
Polygon_type_traits/
│
├── build.bat
├── CMakeLists.txt
├── cmake/
│   ├── options.cmake
│   ├── dependencies.cmake
│   └── functions.cmake 		
│
├── images/
│   └── Logo_SolarWind.png
│
├── include/
│   ├── color_output.hpp
│   ├── umbrella_header.hpp
│   └── testers/
│       ├── triviality_tester.hpp
│       ├── type_properties_tester.hpp
│       ├── is_noexec_tester.hpp
│       ├── layout_and_special_members_tester.hpp
│       ├── type_name_tester.hpp
│       ├── standard_layout_tester.hpp
│       ├── sizeof_and_alignof.hpp
│       └── value_category_tester.hpp
│
├── src/
│	├── CMakeLists.txt
│	├── cmake/
│	│   └── sources.cmake
│	│
│ ├── main.cpp
│ ├── test_triviality.cpp
│ ├── test_exception_specification.cpp
│ ├── test_value_category.cpp
│	├── test_layout_and_special_members.cpp
│ ├── test_type_properties.cpp
│ └── test_type_names.cpp
│
└── README.md
