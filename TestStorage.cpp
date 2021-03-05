#include "Storage.hpp"
#include <iostream>
#include "config.hpp"
#include "UnitTester.hpp"

using namespace common_namespaces;

TEST("Internal::Storage") {

    Mat3b m({2, 2}, {
        {1, 2, 3}, {4, 5, 6},
        {7, 8, 9}, {10, 11, 12}
    });

    using storage_type = Storage<decltype(m)>;

    ASSERT(storage_type::get(m, 1, 0) == (Pixel {7, 8, 9}));
}

TEST("Internal::Kokkos::Unmanaged") {

    int n = 3;
    Mat m(n, n, CV_8UC3, {0, 0, 0});
        View<uchar**[3], LayoutRight, HostSpace, MemoryTraits<Unmanaged>> view(m.data, n, n);

    view(0, 1, 2) = 9;

    cout << m << endl;
}