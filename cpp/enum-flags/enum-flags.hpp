/*
 * Type-safe enum-based bitmask implementation.
 */
#include <initializer_list>
#include <type_traits>

// unlike other implementations, this one does not cast to the
// original enum type and does not introduce new operations over it.
//
// However, EnumeratedFlags can be cast to the underlying data type of
// the given Enum.
template<typename Enum>
struct EnumeratedFlags
{
    using underlying = typename std::underlying_type_t<Enum>;

    EnumeratedFlags() : mask{} { }

    EnumeratedFlags(const EnumeratedFlags& other ) : mask{other.mask} { }

    EnumeratedFlags(EnumeratedFlags&& other ) : mask{other.mask} { }

    // consturct with multiple flags set
    constexpr EnumeratedFlags(std::initializer_list<Enum> ens) {
        mask = 0;
        for (const Enum& en : ens)
        {
            mask |= static_cast<underlying>(en);
        }
    }

    constexpr EnumeratedFlags<Enum> operator += (Enum rhs) {
        mask |= static_cast<underlying>(rhs);
        return *this;
    }

    // EnumeratedFlags<Enum> operator -= (Enum rhs) {
    //     mask ~= static_cast<underlying>(rhs);
    //     return *this;
    // }

    constexpr EnumeratedFlags<Enum> operator &= (Enum rhs) {
        mask &= static_cast<underlying>(rhs);
        return *this;
    }

    // cast to the underlying bitmask
    constexpr inline operator underlying() const {
        return mask;
    }

    constexpr bool AnyOf(Enum en) const {
        return (mask & (static_cast<underlying>(en) != 0));
    }

    // returns true if any of the given flags is set
    constexpr bool AnyOf(Enum en, Enum ens...) const {
        return (mask & (static_cast<underlying>(en) != 0)) || AnyOf(ens);
    }

    constexpr bool AllOf(Enum en) const {
        return (mask & (static_cast<underlying>(en) != 0));
    }

    // returns true of all of the given flags are set
    constexpr bool AllOf(Enum en, Enum ens...) const {
        return (mask & (static_cast<underlying>(en) != 0)) && AllOf(ens);
    }

    // check that precisely all of the given flags match

    // retuns true if this EnumeratedFlags instance has exactly the same flags set
    constexpr bool SameAs(std::initializer_list<Enum> ens) const {
        const EnumeratedFlags<Enum> they{ens};
        return *this == they;
    }

    constexpr bool operator==(const Enum& other) const {
        return mask == other.mask;
    }

    // the bitmask, the actual value of this field-set
    underlying mask;
};
