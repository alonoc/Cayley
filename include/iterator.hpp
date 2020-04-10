#ifndef CAYLEY_ITERATOR_HPP_
#define CAULEY_ITERATOR_HPP_

#include <iterator>
#include <cstddef>

namespace cayley
{
    
    template<typename T, std::size_t Inc = 1>
    class iterator
    {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using iterator_category = std::input_iterator_tag;
        using difference_type = std::ptrdiff_t;

        // Constructors
        iterator(pointer ptr) : m_Ptr{ ptr } {}
        iterator(const iterator& other) = default;
        iterator(iterator&& other) = default;

        // Copy and Move assign operators
        iterator& operator=(const iterator& other) = default;
        iterator& operator=(iterator&& other) = default;

        // Destructor
        virtual ~iterator() {};

        // Pre increment/decrement operators
        iterator& operator++()
        {
            m_Ptr += Inc; 
            return *this; 
        }

        iterator& operator--()
        {
            m_Ptr -= Inc; 
            return *this; 
        }

        // Post increment/decrement operators
        iterator operator++(int dummy_op)
        {
            auto new_ptr_position = m_Ptr + Inc;
            return iterator(new_ptr_position);
        }

        iterator operator--(int dummy_op)
        {
            auto new_ptr_position = m_Ptr - Inc;
            return iterator(new_ptr_position); 
        }

        // Equality/Inequality operator
        bool operator==(const iterator& other)
        {
            return m_Ptr == other.m_Ptr;
        }

        bool operator!=(const iterator& other)
        {
            return m_Ptr != other.m_Ptr;
        }
        
        // dereferencing
        reference operator*() { return *m_Ptr; }
        pointer operator->() { return m_Ptr; }

    private:
        pointer m_Ptr;
    };
    
}

#endif