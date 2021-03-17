#include "UnitTester.hpp"
#include "GaussWindow.hpp"
#include "Performance.hpp"

using namespace common_namespaces;

TEST("GaussWindow::Compare") {
    Performance::compare_kokkos<GaussWindow>();
}