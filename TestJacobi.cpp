#include "UnitTester.hpp"
#include "Jacobi.hpp"
#include "Performance.hpp"

using namespace common_namespaces;

TEST("Jacobi::Compare") {
    Performance<Jacobi>::compare();
}