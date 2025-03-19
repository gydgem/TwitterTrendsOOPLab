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

    void drawNameInTheCenterPolygon(cv::Mat &image,
                                    const std::string &name,
                                    const entity::Polygon2i &polygon);

    void drawNamesInTheCenterPolygons(cv::Mat &image,
                                      const std::vector<std::string> &names,
                                      const std::vector<entity::Polygon2i> &polygons);

    void getScale(const std::vector<entity::Polygon2d> &polygons,
                  int rows,
                  int cols,
                  double &scale,
                  double &minX,
                  double &minY);

    std::vector<entity::Polygon2i>
    scalingThePolygons(const std::vector<entity::Polygon2d> &polygons,
                       double scale,
                       double minX,
                       double minY);

    std::vector<cv::Point2i>
    scalingThePoints(const std::vector<cv::Point2d> &points,
                     double scale,
                     double minX,
                     double minY);

} // render

#endif // TWITTERTRENDSOOPLAB_RENDER_H