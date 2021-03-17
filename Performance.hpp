#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include "config.hpp"

#define FILENAME "../data/test.jpeg"
#define DEF_K 30

/// Simplifie la gestion de la mesure des performances:
/// sur gpu, cpu, et la comparaison entre les deux
/// @tparam Smoother la méthode de lissage (doit dériver de ::SmoothingKokkos)
class Performance {
public:

    /// @brief Comparer les versions CPUs et GPUs des versions kokkos
    template<template<class MemSpace, class ExeSpace> class Smoother>
    static void compare_kokkos(int k = DEF_K, const char *filename = FILENAME) {
        using namespace common_namespaces;
        Mat orig;

        Mat smoothed_cpu;
        Mat smoothed_gpu;

        Smoother<Kokkos::HostSpace, Kokkos::OpenMP> smoother_cpu;
        Smoother<Kokkos::CudaSpace, Kokkos::Cuda>   smoother_gpu;

        orig = cv::imread(filename);
        
        smoothed_cpu = smoother_cpu.smooth(orig, k);
        smoothed_gpu = smoother_gpu.smooth(orig, k);

        imshow("Originale", orig);
        imshow(string(smoother_gpu.complete_name()), smoothed_gpu);
        imshow(string(smoother_cpu.complete_name()), smoothed_cpu);

        cout << "difference " << smoother_gpu.name() << " = " << cv::norm(smoothed_gpu - smoothed_cpu) << endl;
        waitKey(0);
    }

    // Mesure le temps d'une version
    template<typename Smoother>
    static void benchmark(const Smoother & smoother, int k = DEF_K, const char *filename = FILENAME) {
        using namespace common_namespaces;
        Mat orig;

        Mat smoothed;

        orig = cv::imread(filename);

        Timer timer;

        smoothed = smoother.smooth(orig, k);

        imshow("Originale", orig);
        imshow(string(smoother.name()), smoothed);

        cout << smoother.name() << ": " << timer.seconds() << "s." << endl;
        waitKey(0);
    }
};
#endif
