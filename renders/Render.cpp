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

    void drawInTheCenter(cv::Mat &image,
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

    void drawInTheCenter(cv::Mat &image,
                         const std::vector<std::string> &names,
                         const std::vector<entity::Polygon2i> &polygons) {
        if (names.size() != polygons.size()) {
            return;
        }

        for (int i = 0; i < names.size(); i++) {
            drawInTheCenter(image, names[i], polygons[i]);
        }
    }

    std::vector<entity::Polygon2i>
    changingThePolygons(const std::vector<entity::Polygon2d> &polygons,
                        int rows,
                        int cols) {
        if (polygons.empty()) {
            return {};
        }

        double maxX = polygons[0][0].x, minX = polygons[0][0].x;
        double maxY = polygons[0][0].y, minY = polygons[0][0].y;
        for (const auto &polygon: polygons) {
            for (const auto &cord: polygon) {
                maxX = std::max(maxX, cord.x);
                maxY = std::max(maxY, cord.y);
                minX = std::min(minX, cord.x);
                minY = std::min(minY, cord.y);
            }
        }

        double width = maxX - minX;
        double height = maxY - minY;

        double scaleX = (cols - 1) / width;
        double scaleY = (rows - 1) / height;
        double scale = std::min(scaleX, scaleY);

        std::vector<entity::Polygon2i> res;
        res.reserve(polygons.size());

        for (const auto &polygon: polygons) {
            entity::Polygon2i scaledPolygon;
            for (const auto &cord: polygon) {
                double shiftedX = cord.x - minX;
                double shiftedY = cord.y - minY;

                int x = static_cast<int>(shiftedX * scale);
                int y = static_cast<int>(shiftedY * scale);

                scaledPolygon.emplace_back(x, y);
            }
            res.emplace_back(scaledPolygon);
        }

        return res;
    }
}