#include "UnitTester.hpp"
#include "Smoothing.hpp"

/// @brief copier en profondeur une matrice OpenCV vers une vue Kokkos
static void copyMatToView(Kokkos::View<uchar**[3], Kokkos::LayoutRight, Kokkos::HostSpace>& view, const cv::Mat& mat) {
    using namespace common_namespaces;

    for(int i = 0; i < mat.rows; ++i) {
        for(int j = 0; j < mat.cols; ++j) {
            for(int k = 0; k < 3; ++k) {
                view(i, j, k) = mat.at<Vec3b>(i, j)[k];
            }
        }
    }
}

template<typename MemSpace, typename ExeSpace>
cv::Mat Smoothing<MemSpace, ExeSpace>::smooth(const cv::Mat &in, int k) {
    using namespace common_namespaces;

    const int h = in.rows;
    const int w = in.cols;
    Mat out(h, w, in.type(), {0, 0, 0});
    Timer timer;

    // Buffer mémoire sur CPU sans copie grâce aux traits
    using ViewUnmanaged = Kokkos::View<
        uchar**[3],
        LayoutRight,
        HostSpace,
        Kokkos::MemoryTraits<Kokkos::Unmanaged>
    >;

    ViewUnmanaged hostBufIn(in.data, h, w);
    ViewUnmanaged hostBufOut(out.data, h, w);

    // Buffer mémoires sur MemSpace
    Img viewIn("Vue d'entrée passée au kernel", h, w);
    Img viewOut("Vue de sortie passée au kernel", h, w);

    Kokkos::deep_copy(viewIn, hostBufIn);

    if(needCopyFirst()) {
        // Si on doit initialiser la sortie avec l'entrée
        // On copie depuis viewIn pour permettre d'optimiser car les deux vues sont sur la même mémoire (CUDA/Host)
        Kokkos::deep_copy(viewOut, viewIn);
    }

    this->doSmoothing(viewOut, viewIn, h, w, k);

    // Récupération du résultat dans le buffer, donc dans out
    Kokkos::deep_copy(hostBufOut, viewOut);

    if(m_reportTime) {
        cout << complete_name() << ": " << timer.seconds() << "s." << endl;
    }

    return out;
}
