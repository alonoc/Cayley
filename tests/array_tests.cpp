#include "gtest/gtest.h"
#include "array.hpp"
#include <array>
#include <cstddef>
#include <iostream>

using namespace cayley;

TEST(bc,bc)
{
    const std::size_t num_of_elements = 12;
    const std::size_t num_of_rows = 3;
    const std::size_t num_of_cols = 4;

    std::array<int, num_of_elements> arr_base = 
    {
        1,2,3,4,
        5,6,7,8,
        9,0,1,2
    };

    {
        // row array
        array<int, num_of_cols> arr(arr_base.data());

        // checking capacity
        ASSERT_EQ(num_of_cols, arr.size());
        ASSERT_EQ(num_of_cols, arr.max_size());
        ASSERT_FALSE(arr.empty());

        // checking element access
        ASSERT_EQ(arr_base[0], arr.front());
        ASSERT_EQ(arr_base[num_of_cols-1], arr.back());

        for(std::size_t it = 0; it < num_of_cols; ++it)
        {
            ASSERT_EQ(arr_base.at(it), arr.at(it));
            ASSERT_EQ(arr_base[it], arr[it]);
        }

        // checking begin and end
        std::cerr << "arr1 : -- forward --\n";
        for(auto it = arr.begin(); it != arr.end(); ++it)
        {
            std::cerr << "arr1 --> " << *it << "\n";
        }

        std::cerr << "arr1 : -- backward --\n";
        // checking rbegin and rend
        for(auto it = arr.rbegin(); it != arr.rend(); ++it)
        {
            std::cerr << "arr1 --> " << *it << "\n";
        }
    }

    {
        array<int, num_of_rows, num_of_cols> arr(arr_base.data());

        // checking capacity
        ASSERT_EQ(num_of_rows, arr.size());
        ASSERT_EQ(num_of_rows, arr.max_size());
        ASSERT_FALSE(arr.empty());

        // checking element access
        ASSERT_EQ(arr_base[0], arr.front());
        ASSERT_EQ(arr_base[(num_of_rows-1)*num_of_cols], arr.back());

        for(std::size_t it = 0; it < num_of_rows; ++it)
        {
            ASSERT_EQ(arr_base.at(it * num_of_cols), arr.at(it));
            ASSERT_EQ(arr_base[it * num_of_cols], arr[it]);
        }

        // checking begin and end
        std::cerr << "arr2 : -- forward --\n";
        for(auto it = arr.begin(); it != arr.end(); ++it)
        {
            std::cerr << "arr2 --> " << *it << "\n";
        }

        std::cerr << "arr2 : -- backward --\n";
        // checking rbegin and rend
        for(auto it = arr.rbegin(); it != arr.rend(); ++it)
        {
            std::cerr << "arr2 --> " << *it << "\n";
        }
    }

    {
        array<int, 0, 1> arr(nullptr);
        array<int, 0, 1> arr1(arr);
        array<int, 0, 1> arr2(std::move(arr1));
        array<int, 0, 1> arr3 = arr2;
        array<int, 0, 1> arr4 = std::move(arr3);

        //checking capacity
        ASSERT_EQ(0, arr.size());
        ASSERT_EQ(0, arr.max_size());
        ASSERT_TRUE(arr.empty());
    }

    {
        array<int, num_of_cols> arr(arr_base.data() + num_of_cols);
        // checking begin and end
        std::cerr << "arr4 : -- forward --\n";
        for(auto it = arr.begin(); it != arr.end(); ++it)
        {
            std::cerr << "arr4 --> " << *it << "\n";
        }

        std::cerr << "arr4 : -- backward --\n";
        // checking rbegin and rend
        for(auto it = arr.rbegin(); it != arr.rend(); ++it)
        {
            std::cerr << "arr4 --> " << *it << "\n";
        }
    }

    {
        array<int, num_of_rows, num_of_cols> arr(arr_base.data()+1);
        // checking begin and end
        std::cerr << "arr5 : -- forward --\n";
        for(auto it = arr.begin(); it != arr.end(); ++it)
        {
            std::cerr << "arr5 --> " << *it << "\n";
        }

        std::cerr << "arr5 : -- backward --\n";
        // checking rbegin and rend
        for(auto it = arr.rbegin(); it != arr.rend(); ++it)
        {
            std::cerr << "arr5 --> " << *it << "\n";
        }
    }

    {
        array<int, num_of_cols> arr1(arr_base.data() );
        array<int, num_of_cols> arr2(arr_base.data() + num_of_cols);

        std::cerr << "get<0>(arr) = " << get<0>(arr1) << "\n";
        arr1.fill(100);
        arr1.swap(arr2);
        std::cerr << "get<0>(arr) = " << get<0>(arr1) << "\n";

        if(arr1 == arr2)
        {
            std::cerr << "arr1 is equal to arr2\n";
        }
        if(arr1 != arr2)
        {
            std::cerr << "arr1 is not equal to arr2\n";
        }
    }

}