//
// Created by gydgem on 4/16/2025.
//

#ifndef TWITTERTRENDSOOPLAB_SCALINGS_H
#define TWITTERTRENDSOOPLAB_SCALINGS_H

#include <vector>
#include "../entity/Polygon.h"

namespace algorithm {
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
} //algorithm

#endif //TWITTERTRENDSOOPLAB_SCALINGS_H
