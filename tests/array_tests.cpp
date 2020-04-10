#include "gtest/gtest.h"
#include "array.hpp"
#include <array>
#include <cstddef>

using namespace cayley;

TEST(bc,bc)
{
    const std::size_t num_of_elements = 6;
    const std::size_t num_of_rows = 2;
    const std::size_t num_of_cols = 3;

    std::array<int, num_of_elements> arr_base = 
    {
        1,2,3,
        4,5,6
    };

    array<int,num_of_cols>             arr1(arr_base.data());
    array<int,num_of_rows,num_of_cols> arr2(arr_base.data());

    for(std::size_t it = 0; it < num_of_cols; ++it)
    {
        ASSERT_EQ(arr_base.at(it), arr1.at(it));
    }

    for(std::size_t it = 0; it < num_of_rows; ++it)
    {
        ASSERT_EQ(arr_base.at(it * num_of_cols), arr2.at(it));
    }

    for(auto elem : arr1)
    {
        ASSERT_EQ(1, elem);
    }
}