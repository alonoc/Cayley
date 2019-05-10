/**
 * \file static_matrix.hpp
 * 
 * \brief This header file contains the class definition of a static matrix. 
 * 
 */

#ifndef CAYLEY_STATIC_MATRIX_H_
#define CAYLEY_STATIC_MATRIX_H_

#include <type_traits>
#include <stdexcept>

namespace cayley
{
    using size_type = unsigned int;
    template<typename T, size_type R = 3, size_type C = 3>
    class static_matrix
    {
    public:
        static_assert(R != 0, "static_matrix requires a number of rows higher than zero");
        static_assert(C != 0, "static_matrix requires a number of columns higher than zero");
        
        using reference = T&;
        using const_reference = const T&;

        static_matrix() : m_NumOfRows{ R }, m_NumOfCols{ C }, m_NumOfElements{ R*C }
        {
            for(size_type it = 0; it < m_NumOfElements; ++it)
            {
                m_Data[it] = T{};
            }
        };
        
        static_matrix(const static_matrix& other) = default;
        static_matrix(static_matrix&& other) = default;

        static_matrix& operator=(const static_matrix& other) = default;
        static_matrix& operator=(static_matrix&& other) = default;

        virtual ~static_matrix(){};

        constexpr size_type size() const noexcept { return m_NumOfElements; }
        constexpr size_type num_of_rows() const noexcept { return m_NumOfRows; }
        constexpr size_type num_of_cols() const noexcept { return m_NumOfCols; }

        reference at(const size_type row_index, const size_type col_index);
        const_reference at(const size_type row_index, const size_type col_index) const;

    private:
        T m_Data[R*C];
        size_type m_NumOfRows;
        size_type m_NumOfCols;
        size_type m_NumOfElements;

        size_type calculate_element_position(const size_type row_index, const size_type col_index)
        {
            return row_index * m_NumOfCols + col_index;
        }
    };

    template<typename T, size_type R, size_type C>
    typename static_matrix<T,R,C>::reference static_matrix<T,R,C>::at(const size_type row_index, const size_type col_index)
    {
        if (row_index >= m_NumOfRows)
        {
            throw std::out_of_range("Invalid static_matrix<T> row subscript");
        }
        if (col_index >= m_NumOfCols)
        {
            throw std::out_of_range("Invalid static_matrix<T> column subscript");
        }
        auto element_position = calculate_element_position(row_index, col_index);
        return m_Data[element_position];
    }

    template<typename T, size_type R, size_type C>
    typename static_matrix<T,R,C>::const_reference static_matrix<T,R,C>::at(const size_type row_index, const size_type col_index) const
    {
        if (row_index >= m_NumOfRows)
        {
            throw std::out_of_range("Invalid static_matrix<T> row subscript");
        }
        if (col_index >= m_NumOfCols)
        {
            throw std::out_of_range("Invalid static_matrix<T> column subscript");
        }
        auto element_position = calculate_element_position(row_index, col_index);
        return m_Data[element_position];
    }
}

#endif