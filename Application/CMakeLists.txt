cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

project(ddl2code)

set(LOGGER_VERSION_MAJOR 1)
set(LOGGER_VERSION_MINOR 0)

include_directories("${PROJECT_BINARY_DIR}")

set(EXTRA_LIBS ${EXTRA_LIBS})

file(GLOB APP_SRC)

# Logger dependency:
include_directories("/usr/local/include/Logger") # Access to shared library header files
link_directories("/usr/local/lib/Logger") # Link shared library
link_libraries(Logger)

add_executable(ddl2code ${APP_SRC} main.cpp)
