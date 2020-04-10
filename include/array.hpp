#ifndef CAYLEY_ARRAY_HPP_
#define CAYLEY_ARRAY_HPP_

#include <cstddef>
#include "iterator.hpp"

namespace cayley
{
    template<typename T, std::size_t S, std::size_t Inc = 1>
    class array
    {
    public:
        static_assert(S != 0, "array requires a number of elements higher than zero");
        static_assert(Inc != 0, "array requires an increment value higher than zero");

        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using size_type = std::size_t;
        using iterator = cayley::iterator<T,Inc>;

        array(pointer ptr) : m_Data(ptr) {}
        array(const array& other) = default;
        array(array&& other) = default;

        array& operator=(const array& other) = default;
        array& operator=(array&& other) = default;

        virtual ~array() {}

        constexpr size_type size() const noexcept { return S; }
        constexpr reference at(size_type position);
        constexpr const_reference at(size_type position) const;

        constexpr iterator begin() noexcept;
        constexpr iterator end() noexcept;


    private:
        pointer m_Data;
        constexpr size_type calculate_element_position(size_type position) const noexcept;
    };

    template<typename T, std::size_t S, std::size_t Inc>
    constexpr typename array<T,S,Inc>::reference array<T,S,Inc>::at(size_type position)
    {
        if(position >= S)
        {

        }
        return m_Data[position*Inc];
    }

    template<typename T, std::size_t S, std::size_t Inc>
    constexpr typename array<T,S,Inc>::const_reference array<T,S,Inc>::at(size_type position) const
    {
        if(position >= S)
        {

        }
        return m_Data[position*Inc];
    }

    template<typename T, std::size_t S, std::size_t Inc>
    constexpr typename array<T,S,Inc>::iterator array<T,S,Inc>::begin() noexcept
    {
        return iterator(m_Data);
    }

    template<typename T, std::size_t S, std::size_t Inc>
    constexpr typename array<T,S,Inc>::iterator array<T,S,Inc>::end() noexcept
    {
        return iterator(m_Data + S);
    }

}

#endif