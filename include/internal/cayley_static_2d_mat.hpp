#ifndef CAYLEY_STATIC_2D_MAT_HPP_INCLUDED
#define CAYLEY_STATIC_2D_MAT_HPP_INCLUDED

#include <array>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

namespace cayley {
    template<typename T, std::size_t R = 3, std::size_t C = 3>
    class static_matrix_2d
    {
        static_assert(R > 0, "Cannot create a 2d static matrix with no rows");
        static_assert(C > 0, "Cannot create a 2d static matrix with no columns");
        
        public:
            using size_type = std::size_t;
            using reference = T&;
            using const_reference = const T&;

            // Constructors
            static_matrix_2d() : m_NumOfRows(R), m_NumOfCols(C), m_NumOfElements(R*C)
            {
                // Default Constructor
            }

            static_matrix_2d(T value) : m_NumOfRows(R), m_NumOfCols(C), m_NumOfElements(R*C)
            {
                std::fill(m_Data, m_Data + m_NumOfElements, value);
            }

            // Access Functions
            reference at(size_type row, size_type column);
            const_reference at(size_type row, size_type column) const;

            // Size Type Functions
            size_type size() const { return m_NumOfElements; }
            size_type rows_size() const { return m_NumOfRows; }
            size_type cols_size() const { return m_NumOfCols; }

        private:
            T m_Data[R*C];
            size_type m_NumOfRows;
            size_type m_NumOfCols;
            size_type m_NumOfElements;

            size_type calculate_element_position(size_type row, size_type column)
            {
                return row * m_NumOfCols + column;
            }
    };

    template<typename T, std::size_t R, std::size_t C>
    typename static_matrix_2d<T,R,C>::reference static_matrix_2d<T,R,C>::at(size_type row, size_type column)
    {
        if (row >= m_NumOfRows)
        {
            throw std::out_of_range("Invalid static_matrix_2d<T> row subscript");
        }
        else if (column >= m_NumOfCols)
        {
            throw std::out_of_range("Invalid static_matrix_2d<T> column subscript");
        }
        auto element_position = calculate_element_position(row, column);
        return m_Data[element_position];
    }

    template<typename T, std::size_t R, std::size_t C>
    typename static_matrix_2d<T,R,C>::const_reference static_matrix_2d<T,R,C>::at(size_type row, size_type column) const
    {
        if (row >= m_NumOfRows)
        {
            throw std::out_of_range("Invalid static_matrix_2d<T> row subscript");
        }
        else if (column >= m_NumOfCols)
        {
            throw std::out_of_range("Invalid static_matrix_2d<T> column subscript");
        }
        auto element_position = calculate_element_position(row, column);
        return m_Data[element_position];
    }
}





#endif