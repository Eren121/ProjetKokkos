cmake_minimum_required(VERSION 3.16)
project(KokkosTest)


find_package(CUDA REQUIRED)
find_package(OpenMP REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Kokkos REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "--expt-relaxed-constexpr")

add_executable(KokkosTest main.cpp Storage.hpp UnitTester.cpp UnitTester.hpp TestStorage.cpp config.hpp Smoothing.tpp Smoothing.hpp Gauss.tpp Gauss.hpp Diagonale.hpp TestGauss.cpp Performance.hpp GaussK.hpp TestGaussK.cpp Jacobi.hpp TestJacobi.cpp)
target_link_libraries(KokkosTest Kokkos::kokkos)
target_link_libraries(KokkosTest OpenMP::OpenMP_CXX)
target_link_libraries(KokkosTest ${OpenCV_LIBS})
target_link_libraries(KokkosTest ${OpenCV_LIBS})