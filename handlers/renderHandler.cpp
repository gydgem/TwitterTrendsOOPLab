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
        const double epsilon = 0.01;

        // Рассчитываем общий диапазон для штатов и твитов
        auto [min_val, max_val] = calculateSentimentRange();

        // Отрисовка штатов
        for (size_t i = 0; i < states.size(); i++) {
            const auto color = getStateColor(
                    sentimentStates[i],
                    min_val,
                    max_val,
                    epsilon
            );

            render::draw(image, scaledStatesPolygons[i], color);
            render::drawNamesInTheCenterPolygons(image, states[i].name, scaledStatesPolygons[i]);
        }

        // Отрисовка твитов
        std::vector<cv::Scalar> tweetColors;
        tweetColors.reserve(sentimentTweets.size());

        for (const auto &tweet: sentimentTweets) {
            tweetColors.push_back(getStateColor(tweet, min_val, max_val, epsilon));
        }

        if (!scaledTweetsPoints.empty()) {
            render::draw(
                    image,
                    scaledTweetsPoints,
                    tweetColors,
                    cv::Scalar(105, 105, 105), // Цвет границы
                    1 // Толщина границы
            );
        }
    }

// Вспомогательные функции
    std::pair<double, double> renderHandler::calculateSentimentRange() const {
        double min_val = 0.0;
        double max_val = 0.0;
        bool first_valid = true;

        // Обрабатываем штаты
        for (const auto &state: sentimentStates) {
            if (state.has_value()) {
                const double val = state.value();
                if (first_valid) {
                    min_val = val;
                    max_val = val;
                    first_valid = false;
                } else {
                    min_val = std::min(min_val, val);
                    max_val = std::max(max_val, val);
                }
            }
        }

        // Обрабатываем твиты
        for (const auto &tweet: sentimentTweets) {
            if (tweet.has_value()) {
                const double val = tweet.value();
                if (first_valid) {
                    min_val = val;
                    max_val = val;
                    first_valid = false;
                } else {
                    min_val = std::min(min_val, val);
                    max_val = std::max(max_val, val);
                }
            }
        }

        // Защита от одинаковых значений
        if (std::fabs(min_val - max_val) < 1e-6) {
            return {first_valid ? -1.0 : min_val - 1.0,
                    first_valid ? 1.0 : max_val + 1.0};
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

        // Расчет цветов градиента
        if (value < -epsilon) {
            const double t = (value - min_neg) / (-epsilon - min_neg);
            const int green = static_cast<int>(165 * std::clamp(t, 0.0, 1.0));
            return cv::Scalar(0, green, 255); // Красный-оранжевый
        } else {
            const double t = (value - epsilon) / (max_pos - epsilon);
            const int green = 100 + static_cast<int>(155 * std::clamp(t, 0.0, 1.0));
            return cv::Scalar(0, green, 0); // Зеленый градиент
        }
    }

    const cv::Mat &renderHandler::getImage() const {
        return image;
    }
} // handler