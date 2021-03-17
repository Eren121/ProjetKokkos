#ifndef GAUSSK_HPP
#define GAUSSK_HPP

#include "SmoothingKokkos.hpp"
#include "Diagonale.hpp"

/// Version de GaussWindow-Seidel parallèle mais non-optimisée car traite les étapes les unes après les autres
/// Parallèle mais pas dans toutes les dimensions (dimensions des pixels mais pas dimension des étapes)
template<typename MemSpace, typename ExeSpace>
class GaussK : public SmoothingKokkos<MemSpace, ExeSpace> {
public:
    using typename SmoothingKokkos<MemSpace, ExeSpace>::Img;

    const char *name() const override { return "Gauss-Seidel [K]"; }

    void doSmoothing(Img &out, const Img &in, int h, int w, int k) override {

        // étapes
        for(int cur_k = 0; cur_k < k; ++cur_k) {

            // chaque diagonale de l'image
            for(int id = 0; id < Diagonale::diags(h, w); ++id) {

                Kokkos::parallel_for(
                    Kokkos::RangePolicy<ExeSpace>(0, Diagonale::elements(h, w, id)),
                    KOKKOS_LAMBDA(const size_t jd) {
                        const auto [ i, j ] = Diagonale::asMatCoords(h, w, id, jd);
                        updatePixel(out, i, j);
                });
            }
        }
    }
};

#endif
