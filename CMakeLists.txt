cmake_minimum_required(VERSION 3.0)
project(Cayley)

#compiler flags
set(CMAKE_CXX_STANDARD 14)
if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()
if ( MSVC )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()


#find dependencies
find_package(Catch2 3 REQUIRED)

#setup testing
enable_testing()
include_directories(include/)

file(GLOB test_files_SRC
    "tests/*.cpp"
)

#add executable
add_executable(
    cayleyTests 
    ${test_files_SRC}
)

#Link against catch2
target_link_libraries(cayleyTests PRIVATE Catch2::Catch2WithMain)

#add tests
add_test(
    NAME cayleyTests
    COMMAND cayleyTests
)