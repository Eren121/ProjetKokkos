#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Kokkos_Core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>

namespace common_namespaces {
    using namespace Kokkos;
    using namespace cv;
    using namespace std;
}

namespace ui {

    inline void display_results(const cv::Mat& orig, const cv::Mat& result, const std::string& title) {
        using namespace common_namespaces;

        imshow("Image originale", orig);
        imshow(title, result);

        waitKey(0);
    }
}

#endif