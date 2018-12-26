#ifndef CAYLEY_HPP_
#define CAYLEY_HPP_

#include <memory>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <initializer_list>

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
        explicit matrix(const size_type rows, const size_type columns, const T& value, const Allocator& alloc = Allocator());
        matrix(std::initializer_list<std::initializer_list<T>> init, const Allocator& alloc = Allocator());
        matrix(const matrix& other);
        matrix(matrix&& other);

        // Copy Assign Operator
        matrix& operator=(const matrix& other);
        matrix& operator=(matrix&& other);
        
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
        if (0 != m_NumOfRows && 0 != m_NumOfCols)
        {
            m_DataPtr = std::allocator_traits<Allocator>::allocate(m_Allocator, m_Capacity);
            auto construct_fn = [&](auto element) { std::allocator_traits<Allocator>::construct(m_Allocator, element); };
            for_each_n_noderef(m_DataPtr, m_NumOfElements, construct_fn);
        }
        else if (0 == m_NumOfRows && 0 == m_NumOfCols)
        {
            // Empty matrix
        }
        else
        {
            throw std::invalid_argument("Invalid matrix<T> dimensions");
        }
    }

    template<typename T, typename Allocator>
    matrix<T,Allocator>::matrix(const size_type rows, const size_type columns, const T& value, const Allocator& alloc) :
        m_NumOfRows{ rows }, m_NumOfCols{ columns }, m_NumOfElements{ rows*columns }, m_Capacity{ rows*columns }, m_Allocator{ alloc }, m_DataPtr{ nullptr }
    {
        if (0 != m_NumOfRows && 0 != m_NumOfCols)
        {
            m_DataPtr = std::allocator_traits<Allocator>::allocate(m_Allocator, m_Capacity);
            auto construct_fn = [&](auto element) { std::allocator_traits<Allocator>::construct(m_Allocator, element, value); };
            for_each_n_noderef(m_DataPtr, m_NumOfElements, construct_fn);
        }
        else if (0 == m_NumOfRows && 0 == m_NumOfCols)
        {
            // Empty matrix
        }
        else
        {
            throw std::invalid_argument("Invalid matrix<T> dimensions");
        }
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>::matrix(std::initializer_list<std::initializer_list<T>> init, const Allocator& alloc = Allocator()) :
        m_Allocator{ alloc }
    {
        auto const num_of_rows = init.size();
        if (0 == num_of_rows) 
        {
            m_NumOfRows = 0;
            m_NumOfCols = 0;
            m_NumOfElements = 0;
            m_Capacity = 0;
            m_DataPtr = nullptr;
        }
        else 
        {
            auto const num_of_cols = init.begin()->size();
            bool is_initializer_list_ok = 0 != num_of_cols;
            m_NumOfRows = num_of_rows;
            m_NumOfCols = num_of_cols;
            m_Capacity = num_of_rows * num_of_cols;
            m_NumOfElements = 0;
            
            // Allocate new memory
            m_DataPtr = std::allocator_traits<Allocator>::allocate(m_Allocator, m_Capacity);
            
            auto data_ptr = m_DataPtr;
            for (auto row : init) 
            {
                if (num_of_cols != row.size()) 
                {
                    is_initializer_list_ok = false;
                    break;
                }
                for (auto element : row) 
                {
                    std::allocator_traits<Allocator>::construct(m_Allocator, data_ptr, element); 
                    ++data_ptr;
                    ++m_NumOfElements;
                }
            }

            if (!is_initializer_list_ok) 
            {
                if (0 != m_NumOfElements)
                {
                    auto destroy_fn = [&](auto Elem) { std::allocator_traits<Allocator>::destroy(m_Allocator, Elem); };
                    for_each_n_noderef(m_DataPtr, m_NumOfElements, destroy_fn);
                }
                if (0 != m_Capacity)
                {
                    std::allocator_traits<Allocator>::deallocate(m_Allocator, m_DataPtr, m_Capacity);
                }
                throw std::invalid_argument("Invalid matrix<T> dimensions");
            }
        }
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>::matrix(const matrix& other) : 
        m_NumOfRows{ other.m_NumOfRows }, m_NumOfCols{ other.m_NumOfCols }, m_NumOfElements{ other.m_NumOfElements }, m_Capacity{ other.m_Capacity },
        m_DataPtr{ nullptr }, m_Allocator{}
    {
        if (0 != m_Capacity)
        {
            m_DataPtr = std::allocator_traits<Allocator>::allocate(m_Allocator, m_Capacity);
        }
        if (0 != m_NumOfElements)
        {
            auto other_ptr = other.m_DataPtr;
            auto construct_fn = [&](auto element) { std::allocator_traits<Allocator>::construct(m_Allocator, element, *other_ptr); ++other_ptr; };
            for_each_n_noderef(m_DataPtr, m_NumOfElements, construct_fn);
        }
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>::matrix(matrix&& other) :
        m_NumOfRows{ std::move(other.m_NumOfRows) }, m_NumOfCols{ std::move(other.m_NumOfCols) }, m_NumOfElements{ std::move(other.m_NumOfElements) },
        m_Capacity{ std::move(other.m_Capacity) }, m_DataPtr{ std::move(other.m_DataPtr) }, m_Allocator{ std::move(other.m_Allocator) }
    {
        other.m_NumOfRows = 0;
        other.m_NumOfCols = 0;
        other.m_NumOfElements = 0;
        other.m_Capacity = 0;
        other.m_DataPtr = nullptr;
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>& matrix<T, Allocator>::operator=(const matrix& other) 
    {
        if (this != &other) 
        {
            // copy-swap idiom
            matrix tmp_copy(other);
            std::swap(m_NumOfRows, tmp_copy.m_NumOfRows);
            std::swap(m_NumOfCols, tmp_copy.m_NumOfCols);
            std::swap(m_NumOfElements, tmp_copy.m_NumOfElements);
            std::swap(m_Capacity, tmp_copy.m_Capacity);
            std::swap(m_DataPtr, tmp_copy.m_DataPtr);
            std::swap(m_Allocator, tmp_copy.m_Allocator);
        }
        return *this;
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>& matrix<T, Allocator>::operator=(matrix&& other) 
    {
        if (this != &other)
        {
            // release current memory
            if (0 != m_NumOfElements)
            {
                auto destroy_fn = [&](auto Elem) { std::allocator_traits<Allocator>::destroy(m_Allocator, Elem); };
                for_each_n_noderef(m_DataPtr, m_NumOfElements, destroy_fn);
            }
            if (0 != m_Capacity)
            {
                std::allocator_traits<Allocator>::deallocate(m_Allocator, m_DataPtr, m_Capacity);
            }

            // copy members
            m_NumOfRows = other.m_NumOfRows;
            m_NumOfCols = other.m_NumOfRows;
            m_NumOfElements = other.m_NumOfElements;
            m_Capacity = other.m_Capacity;
            m_DataPtr = other.m_DataPtr;

            // set other empty
            other.m_NumOfRows = 0;
            other.m_NumOfCols = 0;
            other.m_NumOfElements = 0;
            other.m_Capacity = 0;
            other.m_DataPtr = nullptr;
        }
        return *this;
    }

    template<typename T, typename Allocator>
    matrix<T, Allocator>::~matrix()
    {
        if (0 != m_NumOfElements)
        {
            auto destroy_fn = [&](auto Elem) { std::allocator_traits<Allocator>::destroy(m_Allocator, Elem); };
            for_each_n_noderef(m_DataPtr, m_NumOfElements, destroy_fn);
        }
        if (0 != m_Capacity)
        {
            std::allocator_traits<Allocator>::deallocate(m_Allocator, m_DataPtr, m_Capacity);        
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
        auto ColsAndRowsAreNotZero = (0 != rows && 0 != columns);
        auto ColsOrRowsAreDifferent = (rows != m_NumOfRows || m_NumOfRows != columns);
        auto ColsAndRowsAreEqualOrHigher = (rows >= m_NumOfRows && columns >= m_NumOfCols);
        if (ColsAndRowsAreNotZero && ColsOrRowsAreDifferent && ColsAndRowsAreEqualOrHigher)
        {
            auto new_capacity = rows * columns;
            // alloc new memory
            auto new_data_ptr = std::allocator_traits<Allocator>::allocate(m_Allocator, new_capacity);
            if (0 != m_NumOfElements) 
            {
                // move members
                std::move(m_DataPtr, m_DataPtr + m_NumOfElements, new_data_ptr);
                // destroy old members
                auto destroy_fn = [&](auto element) { std::allocator_traits<Allocator>::destroy(m_Allocator, element); };
                for_each_n_noderef(m_DataPtr, m_NumOfElements, destroy_fn);
            }
            // release old memory
            std::allocator_traits<Allocator>::deallocate(m_Allocator, m_DataPtr, m_Capacity);
            // update class members
            m_Capacity = new_capacity;
            m_DataPtr = new_data_ptr;
        }
    }

    using iMat = matrix<int>;
    using fMat = matrix<float>;
    using dMat = matrix<double>;
}

#endif