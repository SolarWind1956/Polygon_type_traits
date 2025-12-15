![logo](images/Logo_SolarWind.png)

📂 Структура проекта
Polygon_type_traits/
│
├── build.bat					# Пакетный файл запуска автомата сборки CMake в настраиваемом режиме
├── CMakeLists.txt
├── cmake/                     	# настройки и конфигурация сборки
│   ├── options.cmake       	# 
│   ├── dependencies.cmake    	# 
│   └── functions.cmake    		# 
│
├── images/
│   └── Logo_SolarWind.png     	# Логотип проекта
│
├── include/
│   ├── color_output.hpp       	# ANSI-цвета для красивого терминального вывода
│   ├── umbrella_header.hpp    	# единый входной заголовок для всех тестеров
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
│	│   └── sources.cmake      	# перечень всех исходных файлов
│	│
│   ├── main.cpp               	# единый тест-раннер
│   ├── test_triviality.cpp
│   ├── test_exception_specification.cpp
│   ├── test_value_category.cpp
│	├── test_layout_and_special_members.cpp
│   ├── test_type_properties.cpp
│   └── test_type_names.cpp
│
└── README.md


А теперь — профессиональная структура:
cmake/
    ProjectOptions.cmake      # стандарт языка, предупреждения, sanitizers
    ProjectConfig.cmake       # проектные дефайны
    FetchDependencies.cmake   # зависимости (если появятся)
    Utils.cmake               # функции
src/
    CMakeLists.txt
    Sources.cmake
include/
    (нет CMake!)