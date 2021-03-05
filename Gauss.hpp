#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "Smoothing.hpp"

/// @brief Algorithme de lissage de Gauss-Seidel
template<typename MemSpace, typename ExeSpace>
class Gauss : public Smoothing<MemSpace, ExeSpace> {
public:
    using typename Smoothing<MemSpace, ExeSpace>::Img;

    void doSmoothing(Img &out, const Img &in, int h, int w, int k) override;

    const char *name() const override;
};

#include "Gauss.tpp"

#endif

