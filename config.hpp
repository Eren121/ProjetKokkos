#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Kokkos_Core.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <algorithm>

namespace common_namespaces {
    using namespace Kokkos;
    using namespace cv;
    using namespace std;
}

namespace ui {


    inline void imshow(const std::string& title, const cv::Mat& img) {
#if !NOGUI
        cv::imshow(title, img);
#else
        std::string f;
        f += title;
        f += ".jpeg";
        std::replace(f.begin(), f.end(), '/', ';'); // Au cas où, car / sépérateur répertoire (et il y a des / dans les noms)
        f = "out/" + f;

        cv::imwrite(f, img);
#endif
    }

    inline void waitKey(int i) {
#if !NOGUI
        cv::waitKey(0);
#endif
    }

    inline void display_results(const cv::Mat& orig, const cv::Mat& result, const std::string& title) {
        using namespace common_namespaces;

        ui::imshow("Image originale", orig);
        ui::imshow(title, result);

        ui::waitKey(0);
    }
}

#endif
