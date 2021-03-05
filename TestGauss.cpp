#include "UnitTester.hpp"
#include "Gauss.hpp"
#include "Performance.hpp"

using namespace common_namespaces;

TEST("Gauss::Compare") {
    Performance<Gauss>::compare();
}