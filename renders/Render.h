#ifndef TWITTERTRENDSOOPLAB_RENDER_H
#define TWITTERTRENDSOOPLAB_RENDER_H

#include <string>
#include <cmath>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "../entity/Polygon.h"

namespace render {
    void draw(cv::Mat &image,
              const entity::Polygon2i &polygon);

    void draw(cv::Mat &image,
              const std::vector<entity::Polygon2i> &polygons);

    void drawInTheCenter(cv::Mat &image,
                         const std::string &name,
                         const entity::Polygon2i &polygon);

    void drawInTheCenter(cv::Mat &image,
                         const std::vector<std::string> &names,
                         const std::vector<entity::Polygon2i> &polygons);

    std::vector<entity::Polygon2i>
    changingThePolygons(const std::vector<entity::Polygon2d> &polygons,
                        int rows,
                        int cols);

} // render

#endif // TWITTERTRENDSOOPLAB_RENDER_H