#include "UnitTester.hpp"
#include "Performance.hpp"
#include "serial/Jacobi.hpp"
#include "serial/Gauss.hpp"

using namespace common_namespaces;

TEST("Serial::Jacobi") {
    Serial::Jacobi smoother;
    Performance::benchmark(smoother);
}

TEST("Serial::Gauss") {
    Serial::Gauss smoother;
    Performance::benchmark(smoother);
}
