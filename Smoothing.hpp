#ifndef SMOOTHING_HPP
#define SMOOTHING_HPP

#include "config.hpp"
#include "Storage.hpp"
#include <type_traits>

/// @brief Classe de base pour les algorithmes de lissage Gauss-Seidel et Jacobi
template<typename MemSpace, typename ExeSpace>
class Smoothing {
public:
    using Img = Kokkos::View<uchar**[3], Kokkos::LayoutRight, MemSpace>;

    virtual ~Smoothing() = default;

    cv::Mat smooth(const cv::Mat &in, int k);

    /// @brief Véritable implémentation
    /// Note: public sinon erreur cuda (limitation cuda, apparemment pas de kernel dans une méthode protégée/privée)
    /// @param[out] out le résultat. N'est pas initialisé mais contient la bonne taille
    /// @param[in] in l'image à lisser. L'image en entrée ne doit pas être modifiée
    /// @param k le nombre de lissages à appliquer
    virtual void doSmoothing(Img &out, const Img &in, int h, int w, int k) = 0;


    /// @brief le nom de l'algorithme + indique GPU ou CPU
    std::string complete_name() const {
        using namespace common_namespaces;

        string alg = name();
        alg += " (";
        alg += ExeSpace::name();
        alg += "/";
        alg += MemSpace::name();
        alg += ")";

        return alg;
    }

public:
    /// @brief le nom de l'algorithme
    virtual const char* name() const = 0;

protected:
    /// @brief si cette verson de l'algorithme a besoin que out soit initialisé avec les mêmes pixels que in
    virtual bool needCopyFirst() { return true; }

private:
    bool m_reportTime = true;
};

/// @brief Fonction utilitaire pour le lissage en prenant les 4 voisins proches
/// @param out L'image. Par valeur car la capture est const dans les lambdas, et ne copie pas (shared copy).

template<class Mat> KOKKOS_INLINE_FUNCTION
static void updatePixel(Mat out, Mat in, int i, int j) {
    using namespace common_namespaces;
    using Storage = Storage<Mat>;

    const int h = Storage::height(in);
    const int w = Storage::width(in);

    PixelBase<int> px = Storage::get(in, i, j);
    int n = 1;

    if (i != h - 1) {
        px += Storage::get(in, i + 1, j);
        ++n;
    }
    if (i != 0) {
        px += Storage::get(in, i - 1, j);
        ++n;
    }
    if (j != w - 1) {
        px += Storage::get(in, i, j + 1);
        ++n;
    }
    if (j != 0) {
        px += Storage::get(in, i, j - 1);
        ++n;
    }

    px /= n;
    Storage::set(out, i, j, Pixel(px));
}

template<class Mat> KOKKOS_INLINE_FUNCTION
static void updatePixel(Mat out, int i, int j) {
    updatePixel(out, out, i, j);
}

#include "Smoothing.tpp"

#endif