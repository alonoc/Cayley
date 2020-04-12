#ifndef CAYLEY_UTILITIES_HPP_
#define CAYLEY_UTILITIES_HPP_

namespace cayley
{
    template<bool flag, class IsTrue, class IsFalse>
    struct choose;

    template<class IsTrue, class IsFalse>
    struct choose<true, IsTrue, IsFalse>
    {
        using type = IsTrue;
    };

    template<class IsTrue, class IsFalse>
    struct choose<false, IsTrue, IsFalse>
    {
        using type = IsFalse;
    };
}

#endif