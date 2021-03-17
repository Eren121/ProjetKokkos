#ifndef SERIAL_GAUSS_HPP
#define SERIAL_GAUSS_HPP

#include "SmoothingKokkos.hpp"

namespace Serial {

class Gauss {
public:
    const char* name() const { return "Gauss-Seidel [Serial]"; }

    cv::Mat smooth(cv::Mat in, int max_k) const;
};

}

#endif