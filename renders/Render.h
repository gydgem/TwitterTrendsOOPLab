#ifndef TWITTERTRENDSOOPLAB_RENDER_H
#define TWITTERTRENDSOOPLAB_RENDER_H

#include <string>
#include <cmath>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "../utils/Polygon.h"

namespace Render {
    void draw(cv::Mat &image,
              const Utils::Polygon2i &polygon);

    void draw(cv::Mat &image,
              const std::vector<Utils::Polygon2i> &polygons);

    void drawInTheCenter(cv::Mat &image,
                         const std::string &name,
                         const Utils::Polygon2i &polygon);

    void drawInTheCenter(cv::Mat &image,
                         const std::vector<std::string> &names,
                         const std::vector<Utils::Polygon2i> &polygons);

    std::vector<Utils::Polygon2i>
    changingThePolygon(const stdc::vector<Utils::Polygon2d> &polygons,
                       int rows,
                       int cols);

} // Render

#endif // TWITTERTRENDSOOPLAB_RENDER_H