#include "Diagonale.hpp"
#include "Gauss.hpp"

using namespace common_namespaces;

namespace Serial {

Mat Gauss::smooth(Mat in, int max_k) const {
    const int h = in.rows;
    const int w = in.cols;
    Mat tmp = in.clone();

    for(int k = 0; k < max_k; ++k) {

        for(int id = 0; id < Diagonale::diags(h, w); ++id) {

            const auto max_e = Diagonale::elements(h, w, id);

            for(int jd = 0; jd < max_e; ++jd) {

                const auto [ i, j ] = Diagonale::asMatCoords(h, w, id, jd);
                updatePixel(tmp, i, j);

            }
        }
    }

    return tmp;
}

}