#include "Render.h"

namespace render {
    void draw(cv::Mat &image,
              const entity::Polygon2i &polygon,
              const cv::Scalar &fillColor,
              const cv::Scalar &borderColor,
              int borderThickness) {
        std::vector<std::vector<cv::Point>> contours = {polygon};

        if (fillColor[0] >= 0) {
            cv::drawContours(image, contours, -1, fillColor, cv::FILLED);
        }

        cv::drawContours(image, contours, -1, borderColor, borderThickness, cv::LINE_AA);
    }

    void draw(cv::Mat &image,
              const std::vector<entity::Polygon2i> &polygons,
              const cv::Scalar &fillColor,
              const cv::Scalar &borderColor,
              int borderThickness) {
        if (polygons.empty()) {
            return;
        }


        if (fillColor[0] >= 0) {
            cv::drawContours(image, polygons, -1, fillColor, cv::FILLED);
        }

        cv::drawContours(image, polygons, -1, borderColor, borderThickness, cv::LINE_AA);
    }

    void drawNameInTheCenterPolygon(cv::Mat &image,
                                    const std::string &name,
                                    const entity::Polygon2i &polygon,
                                    const cv::Scalar &textColor,
                                    const cv::Scalar &bgColor) {
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
        if (std::abs(area) < 1e-6) {
            return;
        }

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
        int baseline = 0;

        cv::Size textSize = cv::getTextSize(name, fontFace, fontScale, thickness, &baseline);
        cv::Point textOrg(static_cast<int>(centroidX - textSize.width / 2),
                          static_cast<int>(centroidY + textSize.height / 2));

        // Рисуем фон, если задан
        if (bgColor != cv::Scalar(-1, -1, -1)) {
            cv::Rect bgRect(textOrg.x,
                            textOrg.y - textSize.height,
                            textSize.width,
                            textSize.height + baseline);
            cv::rectangle(image, bgRect, bgColor, cv::FILLED);
        }

        cv::putText(image, name, textOrg, fontFace, fontScale, textColor, thickness, cv::LINE_AA);
    }

    void drawNamesInTheCenterPolygons(cv::Mat &image,
                                      const std::string &name,
                                      const std::vector<entity::Polygon2i> &polygons,
                                      const cv::Scalar &textColor,
                                      const cv::Scalar &bgColor) {

        for (int i = 0; i < polygons.size(); i++) {
            drawNameInTheCenterPolygon(image, name, polygons[i], textColor, bgColor);
        }
    }

    void draw(cv::Mat &image,
              const std::vector<cv::Point2i> &points,
              const std::vector<cv::Scalar> &fillColors,
              const cv::Scalar &borderColor,
              int borderThickness) {

        const int pointRadius = 5;
        const bool hasIndividualColors = !fillColors.empty();

        if (hasIndividualColors && fillColors.size() != points.size()) {
            throw std::invalid_argument("Number of colors must match number of points");
        }

        for (size_t i = 0; i < points.size(); ++i) {
            const cv::Scalar &fillColor = hasIndividualColors
                                          ? fillColors[i]
                                          : borderColor;

            cv::circle(image,
                       points[i],
                       pointRadius,
                       fillColor,
                       cv::FILLED);

            if (borderThickness > 0) {
                cv::circle(image,
                           points[i],
                           pointRadius,
                           borderColor,
                           borderThickness);
            }
        }
    }
}