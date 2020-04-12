#ifndef CAYLEY_ARRAY_PRIV_HPP_
#define CAYLEY_ARRAY_PRIV_HPP_

#include <stdexcept>

namespace cayley
{
    // capacity
    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::size_type array<T,N,Inc>::size() const noexcept
    {
        return N;
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::size_type array<T,N,Inc>::max_size() const noexcept
    {
        return N;
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr bool array<T,N,Inc>::empty() const noexcept
    {
        return N == 0;
    }

    // element access
    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::reference array<T,N,Inc>::at(size_type position)
    {
        if(position >= N)
        {
            throw std::out_of_range("Invalid array<T> subscript");
        }
        auto element_position = calculate_element_position(position);
        return m_Data[element_position];
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reference array<T,N,Inc>::at(size_type position) const
    {
        if(position >= N)
        {
            throw std::out_of_range("Invalid array<T> subscript");
        }
        auto element_position = calculate_element_position(position);
        return m_Data[element_position];
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::reference array<T,N,Inc>::operator[](size_type position)
    {
        auto element_position = calculate_element_position(position);
        return m_Data[element_position];
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reference array<T,N,Inc>::operator[](size_type position) const
    {
        auto element_position = calculate_element_position(position);
        return m_Data[element_position];
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::reference array<T,N,Inc>::front()
    {
        return *begin();
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reference array<T,N,Inc>::front() const
    {
        return *begin();
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::reference array<T,N,Inc>::back()
    {
        auto last_element = --end();
        return *last_element;
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reference array<T,N,Inc>::back() const
    {
        auto last_element = --end();
        return *last_element;
    }

    // iterators
    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::iterator array<T,N,Inc>::begin() noexcept
    {
        return iterator(array_begin());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::iterator array<T,N,Inc>::end() noexcept
    {
        return iterator(array_end());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_iterator array<T,N,Inc>::begin() const noexcept
    {
        return const_iterator(array_begin());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_iterator array<T,N,Inc>::end() const noexcept
    {
        return const_iterator(array_end());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_iterator array<T,N,Inc>::cbegin() const noexcept
    {
        return const_iterator(array_begin());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_iterator array<T,N,Inc>::cend() const noexcept
    {
        return const_iterator(array_end());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::reverse_iterator array<T,N,Inc>::rbegin() noexcept
    {
        return reverse_iterator(array_end());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::reverse_iterator array<T,N,Inc>::rend() noexcept
    {
        return reverse_iterator(array_begin());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reverse_iterator array<T,N,Inc>::rbegin() const noexcept
    {
        return const_reverse_iterator(array_end());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reverse_iterator array<T,N,Inc>::rend() const noexcept
    {
        return const_reverse_iterator(array_begin());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reverse_iterator array<T,N,Inc>::crbegin() const noexcept
    {
        return const_reverse_iterator(array_end());
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::const_reverse_iterator array<T,N,Inc>::crend() const noexcept
    {
        return const_reverse_iterator(array_begin());
    }

    // operations
    template<typename T, std::size_t N, std::size_t Inc>
    void array<T,N,Inc>::fill(const T& value)
    {
        for(auto it = begin(); it != end(); ++it)
        {
            *it = value;
        }
    }

    template<typename T, std::size_t N, std::size_t Inc>
    void array<T,N,Inc>::swap(array<T,N,Inc>& other) noexcept
    {
        pointer tmp = other.m_Data;
        other.m_Data = this->m_Data;
        this->m_Data = tmp;
    }

    // helper functions
    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::size_type array<T,N,Inc>::calculate_element_position(size_type position) const noexcept
    {
        return position * Inc;
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::pointer array<T,N,Inc>::array_begin() const noexcept
    {
        return m_Data;
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr typename array<T,N,Inc>::pointer array<T,N,Inc>::array_end() const noexcept
    {
        return m_Data + (N * Inc);
    }

    // non-member functions
    template<typename T, std::size_t N, std::size_t Inc>
    constexpr bool operator==(const array<T,N,Inc>& lhs, const array<T,N,Inc>& rhs)
    {
        bool are_equal = true;
        typename array<T,N,Inc>::size_type i = 0;
        for(;i < N; ++i)
        {
            if(lhs[i] != rhs[i])
            {
                are_equal = false;
                break;
            }
        }
        return are_equal;
    }

    template<typename T, std::size_t N, std::size_t Inc>
    constexpr bool operator!=(const array<T,N,Inc>& lhs, const array<T,N,Inc>& rhs)
    {
        return !(lhs == rhs);
    }

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr T& get(array<T,N,Inc>& arr) noexcept
    {
        static_assert(I < N, "Invalid array<T> subscript");
        return arr[I];
    }

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr const T& get(const array<T,N,Inc>& arr) noexcept
    {
        static_assert(I < N, "Invalid array<T> subscript");
        return arr[I];
    }

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr T&& get(array<T,N,Inc>&& arr) noexcept
    {
        static_assert(I < N, "Invalid array<T> subscript");
        return arr[I];
    }

    template<std::size_t I, typename T, std::size_t N, std::size_t Inc>
    constexpr const T&& get(const array<T,N,Inc>&& arr) noexcept
    {
        static_assert(I < N, "Invalid array<T> subscript");
        return arr[I];
    }
}

#endif