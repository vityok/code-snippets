#pragma once

// defines dispatcher by using only standard functions from C++11

template<typename Vtor, class... Variants>
class dispatcher
{

  public:
    dispatcher(Vtor &&vtor) : _vtor(std::move(vtor)){};

    void dispatch(Animal *what)
    {
        do_dispatch<Variants...>(animal_kinds<Variants...>{}, what);
    };

    void operator()(Animal *what) { dispatch(what); }

  private:
    Vtor _vtor;

    // terminate recursion for do_dispatch
    template<typename V0>
    void do_dispatch(animal_kinds<V0>, Animal *what)
    {
        if (what->GetId() == V0::ID)
        {
            auto ptr = dynamic_cast<V0 *>(what);
            if (ptr != nullptr)
            {
                _vtor(*ptr);
            }
        }
    }

    // start recursion for do_dispatch
    template<typename V0, typename V1, typename... Vs>
    void do_dispatch(animal_kinds<V0, V1, Vs...>, Animal *what)
    {
        if (what->GetId() == V0::ID)
        {
            auto ptr = dynamic_cast<V0 *>(what);
            if (ptr != nullptr)
            {
                _vtor(*ptr);
            }
        }
        else
        {
            do_dispatch<V1, Vs...>(animal_kinds<V1, Vs...>{}, what);
        }
    }
};

template<class... Variants, typename... Fs>
std::function<void(Animal *)> make_dispatch(animal_kinds<Variants...>, Fs&&... fs)
{
    auto visitor = make_visitor(std::forward<Fs>(fs)...);
    return dispatcher<decltype(visitor), Variants...>(std::move(visitor));
}
