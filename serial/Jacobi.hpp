#ifndef JACOBI_HPP
#define JACOBI_HPP

#include "SmoothingKokkos.hpp"

namespace Serial {

class Jacobi {
public:
    const char* name() const { return "Jacobi [Serial]"; }

    cv::Mat smooth(cv::Mat in, int max_k) const;

private:
    void smooth_once(cv::Mat &out, const cv::Mat& in, int h, int w) const;
};

}

#endif