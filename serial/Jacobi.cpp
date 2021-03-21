#include "Jacobi.hpp"

using namespace common_namespaces;

namespace Serial {

Mat Jacobi::smooth(Mat in, int max_k) const {
    const int h = in.rows;
    const int w = in.cols;
    Mat out = in.clone();
    Mat tmp(h, w, in.type(), {0, 0, 0});

    for(int k = 0; k < max_k; ++k) {

        smooth_once(tmp, out, h, w);

        swap(tmp, out);
    }

    return out;
}

void Jacobi::smooth_once(Mat &out, const Mat &in, int h, int w) const {

    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            updatePixel(out, i, j);
        }
    }
}

}
