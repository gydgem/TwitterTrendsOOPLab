#include "Render.h"

namespace render {
    void draw(cv::Mat &image,
              const entity::Polygon2i &polygon) {
        std::vector<std::vector<cv::Point>> contours = {polygon};
        cv::drawContours(image, contours, -1, cv::Scalar(105, 105, 105), 1, cv::LINE_AA);
    }

    void draw(cv::Mat &image,
              const std::vector<entity::Polygon2i> &polygons) {
        cv::drawContours(image, polygons, -1, cv::Scalar(105, 105, 105), 1, cv::LINE_AA);
    }

    void drawNameInTheCenterPolygon(cv::Mat &image,
                             const std::string &name,
                             const entity::Polygon2i &polygon) {
        if (polygon.empty()) {
            return;
        }

        double area = 0.0;
        double centroidX = 0.0;
        double centroidY = 0.0;

        for (size_t i = 0; i < polygon.size(); ++i) {
            size_t j = (i + 1) % polygon.size();
            const auto &p1 = polygon[i];
            const auto &p2 = polygon[j];

            double cross = (p1.x * p2.y) - (p2.x * p1.y);
            area += cross;
            centroidX += (p1.x + p2.x) * cross;
            centroidY += (p1.y + p2.y) * cross;
        }

        area /= 2.0;
        double areaFactor = 1.0 / (6.0 * area);
        centroidX *= areaFactor;
        centroidY *= areaFactor;

        const double minAreaThreshold = 350.0;
        if (std::abs(area) < minAreaThreshold) {
            return;
        }

        double fontScale = 1.2 * std::sqrt(std::abs(area)) / 100.0;
        fontScale = std::max(0.1, std::min(fontScale, 2.0));

        int fontFace = cv::FONT_HERSHEY_SIMPLEX;
        int thickness = 1;
        cv::Scalar color(0, 0, 0);

        int baseline = 0;
        cv::Size textSize = cv::getTextSize(name, fontFace, fontScale, thickness, &baseline);

        cv::Point textOrg(static_cast<int>(centroidX - textSize.width / 2),
                          static_cast<int>(centroidY + textSize.height / 2));

        cv::putText(image, name, textOrg, fontFace, fontScale, color, thickness, cv::LINE_AA);
    }

    void drawNamesInTheCenterPolygons(cv::Mat &image,
                                      const std::vector<std::string> &names,
                                      const std::vector<entity::Polygon2i> &polygons) {
        if (names.size() != polygons.size()) {
            return;
        }

        for (int i = 0; i < names.size(); i++) {
            drawNameInTheCenterPolygon(image, names[i], polygons[i]);
        }
    }

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

        for (const auto &polygon : polygons) {
            for (const auto &point : polygon) {
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
        for (const auto &polygon : polygons) {
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
        for (const auto &p : points) {
            int x = static_cast<int>((p.x - minX) * scale);
            int y = static_cast<int>((p.y - minY) * scale);
            scaledPoints.emplace_back(x, y);
        }
        return scaledPoints;
    }
}