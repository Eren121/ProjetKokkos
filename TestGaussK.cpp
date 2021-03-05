#include "UnitTester.hpp"
#include "GaussK.hpp"
#include "Performance.hpp"

using namespace common_namespaces;

TEST("Gauss-K::Compare") {
    Performance<GaussK>::compare();
}