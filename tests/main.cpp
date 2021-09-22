#include <catch2/catch_test_macros.hpp>
#include "cayley_all.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "static matrix 2d constructors works" )
{
    using namespace cayley;
    static_matrix_2d<int, 4, 4> s_mat;
    REQUIRE( s_mat.size() == 16 );
    REQUIRE( s_mat.rows_size() == 4 );
    REQUIRE( s_mat.cols_size() == 3 );
}