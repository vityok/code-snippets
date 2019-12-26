#pragma once

/// Relies on the Animal class being declared by this moment
///
/// See additional information on the approach in this code:
///
/// Bartlomiej Filipek, 2 Lines Of Code and 3 C++17 Features - The overload Pattern
/// https://dev.to/fenbf/2-lines-of-code-and-3-c-17-features-the-overload-pattern-pgg
///
/// Matt Kline. std::visit is everything wrong with modern C++
/// https://bitbashing.io/std-visit.html
///
/// https://foonathan.net/2017/12/visitors/
///
/// Arne Mertz. Overload: Build a Variant Visitor on the Fly
/// https://arne-mertz.de/2018/05/overload-build-a-variant-visitor-on-the-fly/

/// ------------------------------------------------------- VISITOR BEGIN

template<class... Fs>
struct overload;

template<class F0, class... Frest>
struct overload<F0, Frest...> : F0, overload<Frest...>
{
    overload(F0 f0, Frest... rest) : F0(f0), overload<Frest...>(rest...) {}

    using F0::operator();
    using overload<Frest...>::operator();
};

template<class F0>
struct overload<F0> : F0
{
    overload(F0 f0) : F0(f0) {}

    using F0::operator();
};

template<class... Fs>
overload<Fs...> make_visitor(Fs... fs)
{
    return overload<Fs...>(std::forward<Fs>(fs)...);
}

// -- dispatch vairants for the produced visitor
template<class... Variants>
struct animal_kinds
{
};

#ifndef USE_CT
#    include "visitor_std.hpp"
#endif // without boost callable traits

#ifdef USE_CT
#    include "visitor_ct.hpp"
#endif

// -- end dispatch vairants for the produced visitor

/// ------------------------------------------------------- VISITOR END
