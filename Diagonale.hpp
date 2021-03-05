#ifndef DIAGONALE_HPP
#define DIAGONALE_HPP

#include "config.hpp"

struct XY {
    int i;
    int j;
};

/// @brief Fonctions utiles pour la gestion des anti-diagonales
/// FOnctions simples, inline, appelables depuis le GPU ou le CPU
class Diagonale {
public:

    /// @brefi min gpu-friendly
    KOKKOS_INLINE_FUNCTION
    static int min(int a, int b) {
        return a < b ? a : b;
    }

    /**
     * @return Le maximum d'éléments dans une diagonale
     */
    KOKKOS_INLINE_FUNCTION
    static int max_elements(int h, int w) {
        return min(h, w);
    }
    /**
     * @return Le nombre de diagonale de la matrice
     */
    KOKKOS_INLINE_FUNCTION
    static int diags(int h, int w) {
        return h + w - 1;
    }

    /**
     * Exemples
     * -------
     *
     * w=5, h=3
     *
     * M=  0 1 2 3 4
     *     1 2 3 4 5
     *     2 3 4 5 6
     *
     * -------
     *
     * w=3, h=5
     *
     * M= 0 1 2
     *    1 2 3
     *    2 3 4
     *    3 4 5
     *    4 5 6
     *
     * @return Les coordonnées du premier élément de la diagonale d
     */
    KOKKOS_INLINE_FUNCTION
    static XY diagFirst(int h, int w, int d) {
        int i, j;

        if(d < h) {
            i = d;
            j = 0;
        }
        else {
            i = h - 1;
            j = d - h + 1;
        }

        return { i, j };
    }

    /**
     * @return Les coordonnées du dernier élément de la diagonale d
     */
    KOKKOS_INLINE_FUNCTION
    static XY diagLast(int h, int w, int d) {
        int i, j;

        if(d < w) {
            i = 0;
            j = d;
        }
        else {
            i = d - w + 1;
            j = w - 1;
        }

        return { i, j };
    }

    /**
     * @return Le nombre d'éléments sur la d-ième diagonale
     */
    KOKKOS_INLINE_FUNCTION
    static int elements(int h, int w, int d) {
        return diagFirst(h, w, d).i - diagLast(h, w, d).i + 1;
    }

    /**
     * @return les coordonnées (row, col) à partir de coordonnées diagonales (id, jd)
     */
    KOKKOS_INLINE_FUNCTION
    static XY asMatCoords(int h, int w, int id, int jd) {
        const XY firstElem = diagFirst(h, w, id);
        const int i0 = firstElem.i;
        const int j0 = firstElem.j;

        return { i0 - jd, j0 + jd };
    }
};
#endif
