#ifndef RENDER_H
#define RENDER_H

#include <opencv2/opencv.hpp>
#include "../entity/Polygon.h"

namespace render {
    void draw(cv::Mat &image,
              const entity::Polygon2i &polygon,
              const cv::Scalar &fillColor = cv::Scalar::all(-1),
              const cv::Scalar &borderColor = cv::Scalar(105, 105, 105),
              int borderThickness = 1);

    void draw(cv::Mat &image,
              const std::vector<entity::Polygon2i> &polygons,
              const cv::Scalar &fillColor = cv::Scalar::all(-1),
              const cv::Scalar &borderColor = cv::Scalar(105, 105, 105),
              int borderThickness = 1);

    void draw(cv::Mat &image,
              const std::vector<entity::Polygon2i> &polygons,
              const std::vector<cv::Scalar> &fillColors,
              const cv::Scalar &borderColor = cv::Scalar(105, 105, 105),
              int borderThickness = 1);


    void drawNameInTheCenterPolygon(cv::Mat &image,
                                    const std::string &name,
                                    const entity::Polygon2i &polygon,
                                    const cv::Scalar &textColor = cv::Scalar(0, 0, 0),
                                    const cv::Scalar &bgColor = cv::Scalar(-1, -1, -1));

    void drawNamesInTheCenterPolygons(cv::Mat &image,
                                      const std::string &name,
                                      const std::vector<entity::Polygon2i> &polygons,
                                      const cv::Scalar &textColor = cv::Scalar(0, 0, 0),
                                      const cv::Scalar &bgColor = cv::Scalar(-1, -1, -1));

    void draw(cv::Mat &image,
              const std::vector<cv::Point2i> &points,
              const std::vector<cv::Scalar> &fillColors,
              const cv::Scalar &borderColor = cv::Scalar(105, 105, 105),
              int borderThickness = 2);
} // namespace render

#endif // RENDER_H