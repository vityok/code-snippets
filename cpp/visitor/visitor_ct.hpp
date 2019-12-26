#pragma once

// Defines visitor template similar to the one in visitor.hpp but
// using boost::callable_traits to deduce classes for which to
// dispatch its argument

#include <boost/callable_traits.hpp>
#include <type_traits>

template<typename Vtor, class... Fs>
class dispatcher
{

  public:
    dispatcher(Vtor &&vtor) : _vtor(std::move(vtor)){};

    void operator()(Animal *what) { try_dispatch<Fs...>(animal_kinds<Fs...>{}, what); };

  private:
    // visitor, that has operator() overloaded for all our types of interest
    Vtor _vtor;

    /// actually performs the visit
    template<class Al>
    bool do_visit(animal_kinds<Al &>, Animal *what)
    {
        if (what->GetId() == Al::ID)
        {
            auto ptr = dynamic_cast<Al *>(what);
            if (ptr != nullptr)
            {
                _vtor(*ptr);
            }
            // consider consumed despite failure to cast
            return true;
        }
        else
        {
            // did not match argument type yet
            return false;
        }
    }

    // terminate recursion for try_dispatch
    template<class D0>
    void try_dispatch(animal_kinds<D0>, Animal *what)
    {
        using args_t = boost::callable_traits::args_t<D0, animal_kinds>;

        do_visit(args_t{}, what);
    }

    // start recursion for try_dispatch
    template<class D0, class D1, class... Ds>
    void try_dispatch(animal_kinds<D0, D1, Ds...>, Animal *what)
    {
        // animal_kinds don't actually create a variable of this
        // kinds, therefore it is safe to instantiate it with
        // references, unlike the tuple, which is used by default
        using args_t = boost::callable_traits::args_t<D0, animal_kinds>;

        if (!do_visit(args_t{}, what))
        {
            try_dispatch<D1, Ds...>(animal_kinds<D1, Ds...>{}, what);
        }
    }
};

template<class... Fs>
std::function<void(Animal *)> dispatch_(Fs... fs)
{
    auto visitor = make_visitor(std::forward<Fs>(fs)...);
    return dispatcher<decltype(visitor), Fs...>(std::move(visitor));
}
