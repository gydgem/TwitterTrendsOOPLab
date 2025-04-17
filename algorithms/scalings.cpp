//
// Created by gydgem on 4/16/2025.
//
#include "scalings.h"

namespace algorithm {
    void getScale(const std::vector<entity::Polygon2d> &polygons,
                  int rows,
                  int cols,
                  double &scale,
                  double &minX,
                  double &minY) {
        if (polygons.empty()) {
            scale = 1.0;
            minX = 0.0;
            minY = 0.0;
            return;
        }

        minX = polygons[0][0].x;
        double maxX = polygons[0][0].x;
        minY = polygons[0][0].y;
        double maxY = polygons[0][0].y;

        for (const auto &polygon: polygons) {
            for (const auto &point: polygon) {
                minX = std::min(minX, point.x);
                maxX = std::max(maxX, point.x);
                minY = std::min(minY, point.y);
                maxY = std::max(maxY, point.y);
            }
        }

        double width = maxX - minX;
        double height = maxY - minY;

        double scaleX = (cols - 1) / (width != 0 ? width : 1);
        double scaleY = (rows - 1) / (height != 0 ? height : 1);
        scale = std::min(scaleX, scaleY);
    }

    std::vector<entity::Polygon2i>
    scalingThePolygons(const std::vector<entity::Polygon2d> &polygons,
                       double scale,
                       double minX,
                       double minY) {
        std::vector<entity::Polygon2i> res;
        res.reserve(polygons.size());
        for (const auto &polygon: polygons) {
            auto scaledPoints = scalingThePoints(polygon, scale, minX, minY);
            res.emplace_back(scaledPoints);
        }
        return res;
    }

    std::vector<cv::Point2i>
    scalingThePoints(const std::vector<cv::Point2d> &points,
                     double scale,
                     double minX,
                     double minY) {
        std::vector<cv::Point2i> scaledPoints;
        scaledPoints.reserve(points.size());
        for (const auto &p: points) {
            int x = static_cast<int>((p.x - minX) * scale);
            int y = static_cast<int>((p.y - minY) * scale);
            scaledPoints.emplace_back(x, y);
        }

        return scaledPoints;
    }
} //algorithm