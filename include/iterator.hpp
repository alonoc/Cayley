#ifndef CAYLEY_ITERATOR_HPP_
#define CAULEY_ITERATOR_HPP_

#include <iterator>
#include <cstddef>
#include "utilities.hpp"

namespace cayley
{
    template<typename T, std::size_t Inc = 1, bool IsConst = false>
    class iterator
    {
    public:
        static_assert(Inc != 0, "Iterator requires an increment value higher than zero");

        using value_type = T;
        using reference = typename choose<IsConst, const T&, T&>::type;
        using pointer = typename choose<IsConst, const T*, T*>::type;
        using iterator_category = std::bidirectional_iterator_tag;
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
        iterator& operator++();
        iterator& operator--();

        // Post increment/decrement operators
        iterator operator++(int dummy_op);
        iterator operator--(int dummy_op);

        // Equality/Inequality operator
        bool operator==(const iterator& other);
        bool operator!=(const iterator& other);

        // dereferencing
        reference operator*();
        pointer operator->();

    private:
        pointer m_Ptr;
    };
    
}

#include "iterator_priv.hpp"

#endif