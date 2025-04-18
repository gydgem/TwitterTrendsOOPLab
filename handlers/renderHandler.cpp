//
// Created by gydgem on 4/17/2025.
//

#include "renderHandler.h"


namespace handler {
    renderHandler::renderHandler(const std::vector<std::vector<entity::Polygon2i>> &scaledStatesPolygons,
                                 const std::vector<cv::Point2i> &scaledTweetsPoints,
                                 const std::vector<std::optional<double>> &sentimentTweets,
                                 const std::vector<std::optional<double>> &sentimentStates,
                                 const std::vector<entity::State> &states) :
            scaledStatesPolygons(scaledStatesPolygons),
            scaledTweetsPoints(scaledTweetsPoints),
            sentimentTweets(sentimentTweets),
            sentimentStates(sentimentStates),
            states(states) {
        image = cv::Mat(1080, 1920, CV_8UC3, cv::Scalar(255, 255, 255));
    }

    void renderHandler::drawAll() {

        const auto stateRange = calculateRange(sentimentStates);
        const auto tweetRange = calculateRange(sentimentTweets);

        const double epsilonState = 0.03 * (stateRange.second - stateRange.first);
        const double epsilonTweet = 0.03 * (tweetRange.second - tweetRange.first);

        for (size_t i = 0; i < states.size(); i++) {
            const auto color = getStateColor(
                    sentimentStates[i],
                    stateRange.first,
                    stateRange.second,
                    epsilonState
            );
            render::draw(image, scaledStatesPolygons[i], color);
            render::drawNamesInTheCenterPolygons(image, states[i].name, scaledStatesPolygons[i]);
        }

        std::vector<cv::Scalar> tweetColors;
        std::vector<cv::Point2i> tweetPoints;
        tweetColors.reserve(sentimentTweets.size());
        tweetPoints.reserve(sentimentTweets.size());

        for (size_t i = 0; i < sentimentTweets.size(); i++) {
            if (sentimentTweets[i].has_value()) {
                tweetColors.emplace_back(getStateColor(
                        sentimentTweets[i],
                        tweetRange.first,
                        tweetRange.second,
                        epsilonTweet
                ));
                tweetPoints.emplace_back(scaledTweetsPoints[i]);
            }
        }

        if (!tweetPoints.empty()) {
            render::draw(
                    image,
                    tweetPoints,
                    tweetColors,
                    cv::Scalar(105, 105, 105),
                    1
            );
        }
    }


    std::pair<double, double> renderHandler::calculateRange(
            const std::vector<std::optional<double>> &values
    ) const {
        double min_val = 0.0;
        double max_val = 0.0;
        bool first_valid = false;

        for (const auto &val: values) {
            if (val.has_value()) {
                const double current = val.value();
                if (!first_valid) {
                    min_val = current;
                    max_val = current;
                    first_valid = true;
                } else {
                    min_val = std::min(min_val, current);
                    max_val = std::max(max_val, current);
                }
            }
        }

        if (!first_valid) {
            return {-1.0, 1.0};
        }

        if (std::fabs(max_val - min_val) < 1e-6) {
            return {min_val - 1.0, max_val + 1.0};
        }

        return {min_val, max_val};
    }

    cv::Scalar renderHandler::getStateColor(
            const std::optional<double> &state,
            double min_neg,
            double max_pos,
            double epsilon
    ) const {
        if (!state.has_value()) {
            return cv::Scalar(128, 128, 128); // Серый для nullopt
        }

        const double value = state.value();

        if (std::fabs(value) <= epsilon) {
            return cv::Scalar(255, 255, 255); // Белый для нейтральных
        }

        if (value < -epsilon) {
            // t==0 при value==min_neg → глубокий синий (255,0,0)
            // t==1 при value==-epsilon → светло-голубой (255,255,0)
            const double t = (value - min_neg) / (-epsilon - min_neg);
            const int green = static_cast<int>(255 * std::clamp(t, 0.0, 1.0));
            return cv::Scalar(255, green, 0);
        } else {
            // t==0 при value==epsilon → жёлтый (0,255,255)
            // t==1 при value==max_pos → оранжевый (0,165,255)
            const double t = (value - epsilon) / (max_pos - epsilon);
            const int green = 255 - static_cast<int>(90 * std::clamp(t, 0.0, 1.0));
            return cv::Scalar(0, green, 255);
        }
    }


    const cv::Mat &renderHandler::getImage() const {
        return image;
    }
} // handler