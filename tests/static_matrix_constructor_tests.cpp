#include "gtest/gtest.h"
#include "static_matrix.hpp"

using namespace cayley;

template<typename T>
class StaticMatrixTest : public ::testing::Test 
{
public:
    using MatrixParamType = T;
    static const size_type Rows = 4;
    static const size_type Cols = 3;
};

using StaticMatrixTypes = ::testing::Types<int, float, double>;
TYPED_TEST_SUITE(StaticMatrixTest, StaticMatrixTypes);

TYPED_TEST(StaticMatrixTest, DefaultConstructor)
{
    // Arrange
    using T = typename TestFixture::MatrixParamType;
    const auto rows = TestFixture::Rows;
    const auto cols = TestFixture::Cols;
    const auto total_elements = rows * cols;
    const auto expected_def_value = T{};

    // Act
    static_matrix<T,rows,cols> mat;

    //Assert
    ASSERT_EQ(total_elements, mat.size()) << "failed checking total number of elements";
    ASSERT_EQ(rows, mat.num_of_rows()) << "failed checking number of rows";
    ASSERT_EQ(cols, mat.num_of_cols()) << "failed checking number of cols";

    for(size_type row_it = 0; row_it < rows; ++row_it)
    {
        for(size_type col_it = 0; col_it < cols; ++col_it)
        {
            EXPECT_EQ(expected_def_value, mat.at(row_it, col_it)) << "failed checking element at [" << row_it << "," << col_it << "]";
        }
    }
}