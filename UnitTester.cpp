#include "UnitTester.hpp"
#include <Kokkos_Core.hpp>
#include <cstring>

int main(int argc, char *argv[]) {
    Kokkos::initialize(argc, argv);

    if(argc > 1) {
        if(strcmp(argv[1], "help") == 0) {
            UnitTester::help();
        }
        else {
            UnitTester::run(argv[1]);
        }
    }
    else {
        UnitTester::runAll();
    }

    Kokkos::finalize();
    return 0;
}