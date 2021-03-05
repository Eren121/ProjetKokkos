#include <Kokkos_Core.hpp>
#include <opencv2/core.hpp>
#include <iostream>
#include <cstddef>
#include <type_traits>

const int N = 10'000;

using namespace std;
using namespace Kokkos;

template<bool sameSpace, class In, class Out>
void copy(Out& out, const In& in);

template<bool host>
struct Copy;

template<>
struct Copy<true> {
    template<typename In, typename Out>
    static void copy(Out &out, const In &in) {
        out = in;
    }
};

template<>
struct Copy<false> {
    template<typename In, typename Out>
    static void copy(Out &out, const In &in) {
        Kokkos::deep_copy(out, in);
    }
};

template<typename MemSpace, typename ExeSpace>
View<float**, LayoutRight, HostSpace> test(const char *title)
{
    // LayoutRight = row major (C standard)

    View<float**, LayoutRight, MemSpace> v("data", N, N);

    Timer timer;


    Kokkos::parallel_for(MDRangePolicy<ExeSpace, Rank<2>>({0, 0}, {N, N}),
        KOKKOS_LAMBDA(const size_t i, const size_t j) {
        v(i, j) = i * N + j;
    });

    cout << title << " : " << timer.seconds() << " secondes." << endl;

    View<float**, LayoutRight, HostSpace> h_m("host data", N, N);

    Copy<std::is_same_v<MemSpace, HostSpace>>::copy(h_m, v);
    return h_m;
}

int main2(int argc, char *argv[]) {
    Kokkos::initialize();

    {
        auto v1 = test<CudaSpace, Cuda>("Cuda");
        auto v2 = test<HostSpace, OpenMP>("OpenMP");


        cv::Mat m1(N, N, CV_32F, v1.data());
        cv::Mat m2(N, N, CV_32F, v2.data());

        if(N <= 10) {
            cout << "m1 = " << m1 << endl << "m2 = " << m2 << endl;
        }

        cout << "diff = " << cv::norm(m1 - m2) << endl;
    }

    Kokkos::finalize();
    return 0;
}
