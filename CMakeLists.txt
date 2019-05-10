cmake_minimum_required(VERSION 2.6)
project(Cayley)

#compiler flags
set(CMAKE_CXX_STANDARD 14)
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

#setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

include_directories(include/)

file(GLOB test_files_SRC
    "tests/*.cpp"
)

#add executable
add_executable(
    cayleyTests 
    ${test_files_SRC}
)

#link test executables against gtest
target_link_libraries(cayleyTests ${GTEST_LIBRARY} pthread)

#add tests
add_test(
    NAME cayleyTests
    COMMAND cayleyTests
)