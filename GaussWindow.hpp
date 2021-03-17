#ifndef GAUSS_HPP
#define GAUSS_HPP

#include "SmoothingKokkos.hpp"

/// @brief Algorithme de lissage de GaussWindow-Seidel
template<typename MemSpace, typename ExeSpace>
class GaussWindow : public SmoothingKokkos<MemSpace, ExeSpace> {
public:
    using typename SmoothingKokkos<MemSpace, ExeSpace>::Img;

    void doSmoothing(Img &out, const Img &in, int h, int w, int k) override;

    const char *name() const override;
};

#include "GaussWindow.tpp"

#endif

