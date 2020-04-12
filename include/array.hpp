#ifndef CAYLEY_ARRAY_HPP_
#define CAYLEY_ARRAY_HPP_

#include <cstddef>
#include <iterator>
#include "iterator.hpp"

namespace cayley
{
    template<typename T, std::size_t N, std::size_t Inc = 1>
    class array
    {
    public:
        static_assert(Inc != 0, "array requires an increment value higher than zero");

        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;
        using size_type = std::size_t;
        using iterator = cayley::iterator<T,Inc,false>;
        using const_iterator = cayley::iterator<T,Inc,true>;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        constexpr array(pointer ptr) : m_Data(ptr) {}
        constexpr array(const array& other) = default;
        constexpr array(array&& other) = default;

        constexpr array& operator=(const array& other) = default;
        constexpr array& operator=(array&& other) = default;

        virtual ~array() {}

        // capacity
        constexpr size_type size() const noexcept;
        constexpr size_type max_size() const noexcept;
        constexpr bool empty() const noexcept;

        // element access
        constexpr reference at(size_type position);
        constexpr const_reference at(size_type position) const;
        constexpr reference operator[](size_type position);
        constexpr const_reference operator[](size_type position) const;
        constexpr reference front();
        constexpr const_reference front() const;
        constexpr reference back();
        constexpr const_reference back() const;

        // iterators
        constexpr iterator begin() noexcept;
        constexpr iterator end() noexcept;
        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cbegin() const noexcept;
        constexpr const_iterator cend() const noexcept;

        constexpr reverse_iterator rbegin() noexcept;
        constexpr reverse_iterator rend() noexcept;
        constexpr const_reverse_iterator rbegin() const noexcept;
        constexpr const_reverse_iterator rend() const noexcept;
        constexpr const_reverse_iterator crbegin() const noexcept;
        constexpr const_reverse_iterator crend() const noexcept;

        // operations
        void fill(const T& value);
        void swap(array<T,N,Inc>& other) noexcept;

    private:
        pointer m_Data;

        constexpr size_type calculate_element_position(size_type position) const noexcept;
        constexpr pointer array_begin() const noexcept;
        constexpr pointer array_end() const noexcept;
    };

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr bool operator==(const array<T,N,Inc>& lhs, const array<T,N,Inc>& rhs);

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr bool operator!=(const array<T,N,Inc>& lhs, const array<T,N,Inc>& rhs);

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr T& get(array<T,N,Inc>& arr) noexcept;

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr const T& get(const array<T,N,Inc>& arr) noexcept;

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr T&& get(array<T,N,Inc>&& arr) noexcept;

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr const T&& get(const array<T,N,Inc>&& arr) noexcept;
}

#include "array_priv.hpp"

#endif