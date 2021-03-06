/*
 * FakePrep.h
 *
 */

#ifndef PROTOCOLS_FAKEPREP_H_
#define PROTOCOLS_FAKEPREP_H_

#include "ReplicatedPrep.h"

template<class T>
class FakePrep : public BufferPrep<T>
{
    SeededPRNG G;

public:
    FakePrep(SubProcessor<T>*, DataPositions& usage) :
            BufferPrep<T>(usage)
    {
    }

    FakePrep(DataPositions& usage, GC::ShareThread<T>&) :
            BufferPrep<T>(usage)
    {
    }

    FakePrep(DataPositions& usage, int = 0) :
            BufferPrep<T>(usage)
    {
    }

    void set_protocol(typename T::Protocol&)
    {
    }

    void buffer_triples()
    {
        for (int i = 0; i < 1000; i++)
        {
            auto a = G.get<T>();
            auto b = G.get<T>();
            this->triples.push_back({{a, b, a * b}});
        }
    }

    void buffer_squares()
    {
        for (int i = 0; i < 1000; i++)
        {
            auto a = G.get<T>();
            this->squares.push_back({{a, a * a}});
        }
    }

    void buffer_inverses()
    {
        for (int i = 0; i < 1000; i++)
        {
            auto a = G.get<T>();
            T aa;
            aa.invert(a);
            this->inverses.push_back({{a, aa}});
        }
    }

    void buffer_bits()
    {
        for (int i = 0; i < 1000; i++)
        {
            this->bits.push_back(G.get_bit());
        }
    }

    void get_dabit_no_count(T& a, typename T::bit_type& b)
    {
        auto bit = G.get_bit();
        a = bit;
        b = bit;
    }
};

#endif /* PROTOCOLS_FAKEPREP_H_ */
