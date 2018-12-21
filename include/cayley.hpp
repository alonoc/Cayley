#ifndef CAYLEY_HPP_
#define CAYLEY_HPP_

#include <memory>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace cayley
{
    template<typename InputIt, typename size_type, typename UnaryFunction>
    InputIt for_each_n_noderef(InputIt first, size_type n, UnaryFunction f)
    {
        for (size_type index = 0; index < n; ++index, ++first) { f(first); }
        return first;
    }

    template<typename T>
    class matrix_iterator
    {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;

        // Constructors
        matrix_iterator(pointer ptr) : m_Ptr{ ptr } {}
        matrix_iterator(const matrix_iterator& other) = default;
        matrix_iterator(matrix_iterator&& other) = default;

        // Copy and Move assign operators
        matrix_iterator& operator=(const matrix_iterator& other) = default;
        matrix_iterator& operator=(matrix_iterator&& other) = default;

        // Destructor
        virtual ~matrix_iterator() {};

        // Pre increment/decrement operators
        matrix_iterator& operator++() { ++m_Ptr; return *this; }
        matrix_iterator& operator--() { --m_Ptr; return *this; }

        // Post increment/decrement operators
        matrix_iterator operator++(int dummy_op) { return matrix_iterator(++m_Ptr); }
        matrix_iterator operator--(int dummy_op) { return matrix_iterator(--m_Ptr); }

        // Equality/Inequality operator
        bool operator==(const matrix_iterator& other) { return m_Ptr == other.m_Ptr; }
        bool operator!=(const matrix_iterator& other) { return m_Ptr != other.m_Ptr; }

        // dereferencing
        reference operator*() { return *m_Ptr; }
        pointer operator->() { return m_Ptr; }

    private:
        pointer m_Ptr;
    };

    template<typename T, typename Allocator = std::allocator<T>>
    class matrix
    {
    public:
        using value_type = T;
        using reference = value_type&;
        using const_reference = const value_type&;
        using iterator = matrix_iterator<T>;
        using pointer = typename std::allocator_traits<Allocator>::pointer;
        using size_type = typename std::allocator_traits<Allocator>::size_type;
        
        // Constructors
        explicit matrix(const Allocator& alloc = Allocator());
        explicit matrix(const size_type rows, const size_type columns, const Allocator& alloc = Allocator());
        matrix(const matrix& other) = delete;
        matrix(matrix&& other) = delete;

        // Copy Assign Operator
        matrix& operator=(const matrix& other) = delete;
        matrix& operator=(matrix&& other) = delete;
        
        // Destructor
        virtual ~matrix();

        // Element Access
        reference at(size_type row, size_type column);
        const_reference at(size_type row, size_type column) const;
        
        // Iterators
        iterator begin();
        iterator end();

        // Capacity
        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type rows_size() const noexcept;
        size_type columns_size() const noexcept;
        size_type capacity() const noexcept;
        void reserve(size_type rows, size_type cols);

    private:
        size_type m_NumOfRows;
        size_type m_NumOfCols;
        size_type m_NumOfElements;
        size_type m_Capacity;
        pointer m_DataPtr;
        Allocator m_Allocator;
    };

    template<typename T, typename Allocator>
    matrix<T, Allocator>::matrix(const Allocator& alloc) :
        m_NumOfRows{ 0 }, m_NumOfCols{ 0 }, m_NumOfElements{ 0 }, m_Capacity{ 0 }, m_DataPtr{ nullptr }, m_Allocator{ alloc }
    {

    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>::matrix(const size_type rows, const size_type columns, const Allocator& alloc) :
        m_NumOfRows{ rows }, m_NumOfCols{ columns }, m_NumOfElements{ rows*columns }, m_Capacity{ rows*columns }, m_Allocator{ alloc }, m_DataPtr{ nullptr }
    {
        if (0 != rows && 0 != columns)
        {
            m_DataPtr = std::allocator_traits<Allocator>::allocate(m_Allocator, m_Capacity);
            auto construct_fn = [&](auto element) { std::allocator_traits<Allocator>::construct(m_Allocator, element); };
            for_each_n_noderef(m_DataPtr, m_NumOfElements, construct_fn);
        }
        else if (0 == rows && 0 == columns)
        {
            // Empty matrix
        }
        else
        {
            throw std::invalid_argument("Invalid number of rows or columns");
        }
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>::~matrix()
    {
        if (nullptr != m_DataPtr)
        {
            if (0 != m_NumOfElements)
            {
                auto destroy_fn = [&](auto Elem) { std::allocator_traits<Allocator>::destroy(m_Allocator, Elem); };
                for_each_n_noderef(m_DataPtr, m_NumOfElements, destroy_fn);
            }
            std::allocator_traits<Allocator>::deallocate(m_Allocator, m_DataPtr, m_Capacity);
            m_DataPtr = nullptr;
        }
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::reference matrix<T, Allocator>::at(size_type row, size_type column)
    {
        if (row >= m_NumOfRows)
        {
            throw std::out_of_range("Invalid matrix<T> row subscript");
        }
        if (column >= m_NumOfCols)
        {
            throw std::out_of_range("Invalid matrix<T> column subscript");
        }
        auto elem_position = (row * m_NumOfCols) + column;
        return m_DataPtr[elem_position];
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::const_reference matrix<T, Allocator>::at(size_type row, size_type column) const
    {
        if (row >= m_NumOfRows)
        {
            throw std::out_of_range("Invalid matrix<T> row subscript");
        }
        if (column >= m_NumOfCols)
        {
            throw std::out_of_range("Invalid matrix<T> column subscript");
        }
        auto elem_position = (row * m_NumOfCols) + column;
        return m_DataPtr[elem_position];
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::iterator matrix<T, Allocator>::begin()
    {
        return iterator{ m_DataPtr };
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::iterator matrix<T, Allocator>::end()
    {
        return iterator{ m_DataPtr + m_NumOfElements };
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::size_type matrix<T, Allocator>::size() const noexcept 
    {
        return m_NumOfElements;
    }

    template<typename T, typename Allocator>
    bool matrix<T, Allocator>::empty() const noexcept 
    {
        return 0 == m_NumOfElements;
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::size_type matrix<T, Allocator>::rows_size() const noexcept
    {
        return m_NumOfRows;
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::size_type matrix<T, Allocator>::columns_size() const noexcept
    {
        return m_NumOfCols;
    }

    template<typename T, typename Allocator>
    typename matrix<T, Allocator>::size_type matrix<T, Allocator>::capacity() const noexcept 
    {
        return m_Capacity;
    }

    template<typename T, typename Allocator>
    void matrix<T, Allocator>::reserve(size_type rows, size_type columns)
    {
        auto NoZeroColsOrRows = (0 != rows && 0 != columns);
        auto IsDiffNumOfColsOrRows = (rows != m_NumOfRows || m_NumOfRows != columns);
        auto AreColsAndRowsEqualOrHigher = (rows >= m_NumOfRows && columns >= m_NumOfCols);
        if (IsDiffNumOfColsOrRows && AreColsAndRowsEqualOrHigher && NoZeroColsOrRows)
        {
            auto new_capacity = rows * columns;
            // Alloc new memory
            auto new_data_ptr = std::allocator_traits<Allocator>::allocate(m_Allocator, new_capacity);
            // Move old members
            std::move(m_DataPtr, m_DataPtr + m_NumOfElements, new_data_ptr);
            if (0 != m_NumOfElements) 
            {
                auto destroy_fn = [&](auto element) { std::allocator_traits<Allocator>::destroy(m_Allocator, element); };
                for_each_n_noderef(m_DataPtr, m_NumOfElements, destroy_fn);
            }
            // Release old memory
            std::allocator_traits<Allocator>::deallocate(m_Allocator, m_DataPtr, m_Capacity);
            // Update class members
            m_Capacity = new_capacity;
            m_DataPtr = new_data_ptr;
        }
    }

    using iMat = matrix<int>;
    using fMat = matrix<float>;
    using dMat = matrix<double>;
}

#endif