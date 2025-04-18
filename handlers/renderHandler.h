//
// Created by gydgem on 4/17/2025.
//

#ifndef TWITTERTRENDSOOPLAB_RENDERHANDLER_H
#define TWITTERTRENDSOOPLAB_RENDERHANDLER_H

#include <vector>
#include <opencv2/core/types.hpp>
#include <optional>
#include <opencv2/core/mat.hpp>
#include "../entity/Polygon.h"
#include "../data_structures/Bor.h"
#include "../entity/State.h"
#include "../renders/Render.h"

namespace handler {

    class renderHandler {
        std::vector<cv::Scalar> colorState;
        std::vector<cv::Scalar> colorTweets;

        const std::vector<std::vector<entity::Polygon2i>> &scaledStatesPolygons;
        const std::vector<cv::Point2i> &scaledTweetsPoints;
        const std::vector<std::optional<double>> &sentimentTweets;
        const std::vector<std::optional<double>> &sentimentStates;
        const std::vector<entity::State> &states;

        cv::Mat image;
    public:

        renderHandler(const std::vector<std::vector<entity::Polygon2i>> &scaledStatesPolygons,
                      const std::vector<cv::Point2i> &scaledTweetsPoints,
                      const std::vector<std::optional<double>> &sentimentTweets,
                      const std::vector<std::optional<double>> &sentimentStates,
                      const std::vector<entity::State> &states);

        void drawAll();

        [[nodiscard]] const cv::Mat &getImage() const;

        [[nodiscard]] cv::Scalar getStateColor(const std::optional<double> &state,
                                 double min_neg,
                                 double max_pos,
                                 double epsilon) const;

        std::pair<double, double> calculateRange(const std::vector<std::optional<double>> &values) const;
    };

} // handler

#endif //TWITTERTRENDSOOPLAB_RENDERHANDLER_H
