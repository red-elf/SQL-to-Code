cmake_minimum_required(VERSION 3.22)

include(${CMAKE_CURRENT_SOURCE_DIR}/../Versionable/CMake/CMakeLists.txt)

project(${PROJECT_FULL_NAME})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

# Logger dependency:
include_directories("/usr/local/include/Logger-1.0.0")
link_directories("/usr/local/lib/Logger-1.0.0")
link_libraries(Logger-1.0.0)

# Commons dependency:
include_directories("/usr/local/include/Commons-1.0.0")
link_directories("/usr/local/lib/Commons-1.0.0")
link_libraries(Commons-1.0.0)

# Tester dependency:
include_directories("/usr/local/include/Tester-1.0.0")
link_directories("/usr/local/lib/Tester-1.0.0")
link_libraries(Tester-1.0.0)

# SQL Parser dependency:
include_directories("/usr/local/include/hsql")
link_directories("/usr/local/lib/")
link_libraries(sqlparser)

# argparse dependency:
include_directories("/usr/local/include/argparse")

file(

        GLOB APP_SRC
        "*.h" "*.cpp"
        "processor/*.h" "processor/*.cpp"
        "generator/*.h" "generator/*.cpp"
        "generator/implementation/*.h" "generator/implementation/*.cpp"
        "generator/implementation/cpp/*.h" "generator/implementation/cpp/*.cpp"
        "generator/implementation/jvm/*.h" "generator/implementation/jvm/*.cpp"
        "generator/implementation/dart/*.h" "generator/implementation/dart/*.cpp"
)
add_executable(${PROJECT_NAME} ${APP_SRC} main.cpp Utils.h Utils.cpp)

# FIXME: Install the dependencies:
install(TARGETS ${PROJECT_NAME} DESTINATION bin/${PROJECT_NAME})