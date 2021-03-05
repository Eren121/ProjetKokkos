#include "Gauss.hpp"
#include "Diagonale.hpp"

template<typename MemSpace, typename ExeSpace>
const char *Gauss<MemSpace, ExeSpace>::name() const {
    return "Gauss-Seidel";
}

template<typename MemSpace, typename ExeSpace>
void Gauss<MemSpace, ExeSpace>::
doSmoothing(Img &out, const Img &in, int h, int w, int k) {
    using namespace common_namespaces;

    const int tf = 2 * k - 1; // Taille de la fenêtre (mais 1/2 pixel est traité à chaque itération)
    const int nb_diags = Diagonale::diags(h, w);
    const int nb_elements_max = Diagonale::max_elements(h, w);

    for(int f = -tf + 1; f < nb_diags; ++f) {

        //for(int id = f; id < f + tf; id += 2) {
        // nb_iterations = ((f + tf - f) + 1) / 2
        //               = (tf + 1) / 2
        Kokkos::parallel_for(

            "Gauss-Seidel glissement de la fenêtre",

            MDRangePolicy<ExeSpace, Rank<2>>({0, 0}, {(tf + 1) / 2, nb_elements_max}),

            // on ne peut pas faire des kernels CUDA récursifs, on utilise alors MDRange
            // même si cela fait que certains kernels ne travaillent pas
            // peut être même optimisé car le nombre de threads au moins est constant

            KOKKOS_LAMBDA(const size_t step, const size_t jd) {

                const int id = f + step * 2;
                const auto nb_elements = Diagonale::elements(h, w, id);

                // On lance plus de threads que nécessaires sur la dimension 2 si ce n'est pas la diagonale du milieu
                // Sur la dimension 1 aussi au début et à la fin de la boucle

                if(id >= 0 && id < nb_diags && jd < nb_elements) {

                    const auto [ i, j ] = Diagonale::asMatCoords(h, w, id, jd);
                    updatePixel(out, i, j);
                }
            }
        );
    }

//        Kokkos::parallel_for(
//            MDRangePolicy<ExeSpace, Rank<2>>({0, 0}, {h, w}),
//            KOKKOS_LAMBDA(const size_t i, const size_t j) {
//                auto out_ = out;
//                Storage<Img>::set(out_, i, j, Storage<Img>::get(in, i, j));
//            }
//        );
}
