#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <Kokkos_Core.hpp>
#include <opencv2/core.hpp>


/// template pour permettre l'utilisation de int par exemple pour accumuler sans dépassement de capacité
template<typename T>
struct PixelBase {
public:
    KOKKOS_INLINE_FUNCTION
    PixelBase(T r, T g, T b) {
        val[0] = r;
        val[1] = g;
        val[2] = b;
    }

    template<typename U>
    KOKKOS_INLINE_FUNCTION
    PixelBase(const PixelBase<U>& u) {
        val[0] = u[0];
        val[1] = u[1];
        val[2] = u[2];
    }

    PixelBase(const cv::Vec<T, 3>& v) {
        val[0] = v[0];
        val[1] = v[1];
        val[2] = v[2];
    }

    operator cv::Vec<T, 3>() const {
        return { val[0], val[1], val[2] };
    }

    KOKKOS_INLINE_FUNCTION
    T& operator[](size_t i) { return val[i]; }

    KOKKOS_INLINE_FUNCTION
    T operator[](size_t i) const { return val[i]; }

    KOKKOS_INLINE_FUNCTION
    bool operator==(const PixelBase& other) const {
        return val[0] == other[0] && val[1] == other[1] && val[2] == other[2];
    }

    template<typename U>
    KOKKOS_INLINE_FUNCTION
    PixelBase& operator/=(const U& i) {
        val[0] /= T(i);
        val[1] /= T(i);
        val[2] /= T(i);
        return *this;
    }

    template<typename U>
    KOKKOS_INLINE_FUNCTION
    PixelBase& operator+=(const U &u) {
        val[0] += T(u.val[0]);
        val[1] += T(u.val[1]);
        val[2] += T(u.val[2]);
        return *this;
    }

    T val[3];
};

using Pixel = PixelBase<uchar>;

/**
 * Permet de générifier le code avec cv::Mat ou Kokkos::View en même temps
 * à noter que pour le type des pixels, on utilise qund même les vecteurs d'OpenCV
 * même pour la version Kokkos::View.
 *
 * La définition par défault est pour OpenCV
 */
template<class T>
struct Storage;

template<>
struct Storage<cv::Mat> {
    using T = cv::Mat;

    /// Get pixel
    static Pixel get(const T& mat, int i, int j) {
        return mat.template at<cv::Vec3b>(i, j);
    }

    /// Set pixel
    static void set(T& mat, int i, int j, const Pixel& color) {
        mat.template at<cv::Vec3b>(i, j) = color;
    }

    /// Get width
    static int width(const T& mat) {
        return mat.size[1];
    }

    /// Get height
    static int height(const T& mat) {
        return mat.size[0];
    }
};

template<class Structure, class Layout, class MemSpace, int... componentsIndices>
struct StorageKokkos {
    using T = Kokkos::View<Structure, Layout, MemSpace>;

    // Utilisation des variadiques offre la simplicité d'utilisation des boucles
    // Ainsi que l'optimisation (même si une boucle for aurait sans doute été optimisée)
    // Cependant cela permet l'écriture d'une "boucle" dans les aggrégats comme pour get()

    KOKKOS_INLINE_FUNCTION
    static Pixel get(const T& mat, int i, int j) {

        return { mat(i, j, componentsIndices)... } ;
    }

    KOKKOS_INLINE_FUNCTION
    static void set(T& mat, int i, int j, const Pixel& color) {
        ((mat(i, j, componentsIndices) = color[componentsIndices]), ...);
    }

    /// Attention: width / height invalides si LayoutRight
    KOKKOS_INLINE_FUNCTION
    static int width(const T& mat) {
        return mat.extent(1);
    }

    KOKKOS_INLINE_FUNCTION
    static int height(const T& mat) {
        return mat.extent(0);
    }
};

template<class Structure, class Layout, class MemSpace>
struct Storage<Kokkos::View<Structure, Layout, MemSpace>>
    : public StorageKokkos<Structure, Layout, MemSpace, 0, 1, 2>
{};

#endif