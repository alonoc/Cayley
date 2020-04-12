#ifndef CAYLEY_ITERATOR_PRIV_HPP_
#define CAYLEY_ITERATOR_PRIV_HPP_

namespace cayley
{
    template<typename T, std::size_t Inc, bool IsConst>
    iterator<T,Inc,IsConst>& iterator<T,Inc,IsConst>::operator++()
    {
        m_Ptr += Inc;
        return *this;
    }

    template<typename T, std::size_t Inc, bool IsConst>
    iterator<T,Inc,IsConst>& iterator<T,Inc,IsConst>::operator--()
    {
        m_Ptr -= Inc;
        return *this;
    }

    template<typename T, std::size_t Inc, bool IsConst>
    iterator<T,Inc,IsConst> iterator<T,Inc,IsConst>::operator++(int dummy_op)
    {
        auto new_ptr_position = m_Ptr + Inc;
        return iterator(new_ptr_position);
    }

    template<typename T, std::size_t Inc, bool IsConst>
    iterator<T,Inc,IsConst> iterator<T,Inc,IsConst>::operator--(int dummy_op)
    {
        auto new_ptr_position = m_Ptr - Inc;
        return iterator(new_ptr_position);
    }

    template<typename T, std::size_t Inc, bool IsConst>
    bool iterator<T,Inc,IsConst>::operator==(const iterator<T,Inc,IsConst>& other)
    {
        return m_Ptr == other.m_Ptr;
    }

    template<typename T, std::size_t Inc, bool IsConst>
    bool iterator<T,Inc,IsConst>::operator!=(const iterator<T,Inc,IsConst>& other)
    {
        return m_Ptr != other.m_Ptr;
    }

    template<typename T, std::size_t Inc, bool IsConst>
    typename iterator<T,Inc,IsConst>::reference iterator<T,Inc,IsConst>::operator*()
    {
        return *m_Ptr;
    }

    template<typename T, std::size_t Inc, bool IsConst>
    typename iterator<T,Inc,IsConst>::pointer iterator<T,Inc,IsConst>::operator->()
    {
        return m_Ptr;
    }
}

#endif