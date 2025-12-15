# ======================================================================
#  ProjectConfig.cmake — универсальные настройки проекта
# ======================================================================

message(STATUS "Loading ProjectConfig.cmake")

# ----------------------------------------------------------------------
# 1. Явно задаём стандарт языка — правильно, переносимо
# ----------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 2b)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Для C11/C17 (если в проекте есть .c файлы)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# ----------------------------------------------------------------------
# 2. Отключаем ВСЕ пути, требующие перекодировки
#    Это решает вашу проблему с кириллицей
# ----------------------------------------------------------------------
# MinGW и Clang при кириллице в путях иногда пытаются "догадаться" кодировку.
# Мы запрещаем перекодировку полностью.
set(CMAKE_C_USE_RESPONSE_FILE_FOR_INCLUDES OFF)
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES OFF)
set(CMAKE_NINJA_FORCE_RESPONSE_FILE OFF)

# ----------------------------------------------------------------------
# 3. Устанавливаем набор флагов, НЕ вмешиваясь в -std=
# ----------------------------------------------------------------------
add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
)
target_compile_options(${TARGET_NAME} PUBLIC -std=c++23)
target_compile_options(${TARGET_NAME} PUBLIC -Wall -Wextra -Wpedantic)
target_compile_options(${TARGET_NAME} PUBLIC -ftemplate-backtrace-limit=10)
# ----------------------------------------------------------------------
# 4. В Release включаем оптимизацию
# ----------------------------------------------------------------------
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE   "-O3 -DNDEBUG")

# ----------------------------------------------------------------------
# 5. В Debug включаем отладку
# ----------------------------------------------------------------------
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_DEBUG   "-O0 -g3")

# ----------------------------------------------------------------------
# 6. Включить вывод всех команд на этапе сборки (по желанию)
# ----------------------------------------------------------------------
set(CMAKE_VERBOSE_MAKEFILE ON)

message(STATUS "ProjectConfig.cmake loaded successfully")
