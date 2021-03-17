#include "UnitTester.hpp"
#include "GaussK.hpp"
#include "Performance.hpp"

using namespace common_namespaces;

TEST("GaussWindow-K::Compare") {
    Performance::compare_kokkos<GaussK>();
}