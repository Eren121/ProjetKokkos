#ifndef PERFORMANCE_HPP
#define PERFORMANCE_HPP

#include "config.hpp"

/// Simplifie la gestion de la mesure des performances:
/// sur gpu, cpu, et la comparaison entre les deux
/// @tparam Smoother la méthode de lissage (doit dériver de ::Smoothing)
template<template<class MemSpace, class ExeSpace> class Smoother>
class Performance {
public:

    /// @brief Comparer les versions CPUs et GPUs
    static void compare(int k = 30, const char *filename = "../data/test.jpeg") {
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
};
#endif
