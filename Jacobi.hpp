#ifndef JACOBI_HPP
#define JACOBI_HPP

#include "SmoothingKokkos.hpp"

/// @brief Algorithme de lissage de Jacobi
template<typename MemSpace, typename ExeSpace>
class Jacobi : public SmoothingKokkos<MemSpace, ExeSpace> {
public:
    using typename SmoothingKokkos<MemSpace, ExeSpace>::Img;

    void doSmoothing(Img &out, const Img &in, int h, int w, int k) override;

    const char *name() const override { return "Jacobi"; }

    // public pour CUDA mais pourrait être private
    void oneStep(Img &out, const Img &in, int h, int w);
};

template<typename MemSpace, typename ExeSpace>
void Jacobi<MemSpace, ExeSpace>::doSmoothing(Img &out, const Img &in, int h, int w, int k) {
    using namespace common_namespaces;

    Img buffer("Buffer", h, w); // buffer temporaire

    swap(buffer, out); // on copie initialement dans le buffer l'image
    // puisqu'on a demandé de placé l'image dans out initialement

    for(int i = 0; i < k; ++i) {
        this->oneStep(out, buffer, h, w);
        swap(out, buffer);
    }
    out = buffer;
}

template<typename MemSpace, typename ExeSpace>
void Jacobi<MemSpace, ExeSpace>::oneStep(Img& out, const Img& in, int h, int w) {
    using namespace common_namespaces;

    // Sinon on copierait dans chaque thread l'image entière

    // éviter de capturer les pixels voisins dans en tableau (sinon copie)
    // En plus moins rapide car avec plusiuers addition inutiles avec des zéros sur une des dimensions (ex. i+0)

    // parallel_for n'accepte pas de lambda mutable
    Kokkos::parallel_for(
        "Jacobi",
        MDRangePolicy<ExeSpace, Rank<2>>({0, 0}, {h, w}),
        KOKKOS_LAMBDA(const size_t i, const size_t j) {
            updatePixel(out, in, i, j);
        }
    );
}

#endif