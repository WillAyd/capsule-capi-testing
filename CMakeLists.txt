cmake_minimum_required(VERSION 3.18)
project(${SKBUILD_PROJECT_NAME} LANGUAGES C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
else()
    add_compile_options(-Wall -Wextra)
endif()

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

# Detect the installed nanobind package and import it into CMake
execute_process(
  COMMAND "${Python_EXECUTABLE}" -m nanobind --cmake_dir
  OUTPUT_STRIP_TRAILING_WHITESPACE OUTPUT_VARIABLE NB_DIR)
list(APPEND CMAKE_PREFIX_PATH "${NB_DIR}")
find_package(nanobind CONFIG REQUIRED)

include(FetchContent)
FetchContent_Declare(nanoarrow-project
  GIT_REPOSITORY https://github.com/apache/arrow-nanoarrow.git
  GIT_TAG apache-arrow-nanoarrow-0.3.0
)
FetchContent_MakeAvailable(nanoarrow-project)

nanobind_add_module(somelib somelib.cpp)
target_link_libraries(somelib PRIVATE nanoarrow)
install(TARGETS somelib
  LIBRARY DESTINATION ${SKBUILD_PROJECT_NAME})
