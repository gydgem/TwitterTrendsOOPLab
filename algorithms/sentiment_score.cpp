//
// Created by gydgem on 4/16/2025.
//

#include "sentiment_score.h"

namespace algorithm {
    std::optional<double> calculateSentimentScore(
            const std::string &tweet,
            const entity::Bor<char, double> &sentiments)
    {
        double total_score = 0.0;
        int match_count = 0;
        size_t n = tweet.size();
        size_t i = 0;

        auto is_delimiter = [](char c) {
            return std::isspace(static_cast<unsigned char>(c)) ||
                   std::ispunct(static_cast<unsigned char>(c));
        };

        while (i < n) {
            size_t max_length = 0;
            double current_value = 0.0;
            const entity::Bor<char, double>::node_type *current_node = &sentiments.root_node();

            for (size_t j = i; j < n; ++j) {
                // Преобразование символа в нижний регистр
                const char c = static_cast<char>(std::tolower(
                        static_cast<unsigned char>(tweet[j])
                ));

                auto next_node = sentiments.get_next(*current_node, c);
                if (!next_node.has_value()) break;

                current_node = &next_node->get();

                if (sentiments.is_end_node(*current_node)) {
                    // Проверка границ слова с учетом оригинального регистра
                    bool left_ok = (i == 0) || is_delimiter(tweet[i - 1]);
                    bool right_ok = (j == n - 1) || is_delimiter(tweet[j + 1]);

                    if (left_ok && right_ok) {
                        max_length = j - i + 1;
                        current_value = current_node->end_value.value();
                    }
                }
            }

            if (max_length > 0) {
                total_score += current_value;
                match_count++;
                i += max_length;
            } else {
                i++;
            }
        }

        return (match_count > 0) ? std::optional<double>(total_score/match_count) : std::nullopt;
    }

    bool isPointInPolygons(const cv::Point2d &point, const std::vector<entity::Polygon2d> &polygons) {
        cv::Point2f test_point(static_cast<float>(point.x),
                               static_cast<float>(point.y));

        for (const auto &polygon: polygons) {
            std::vector<cv::Point2f> converted_polygon;
            converted_polygon.reserve(polygon.size());

            for (const auto &pt: polygon) {
                converted_polygon.emplace_back(
                        static_cast<float>(pt.x),
                        static_cast<float>(pt.y)
                );
            }

            if (cv::pointPolygonTest(converted_polygon, test_point, false) >= 0) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::optional<double>> calculateSentimentScore(
            const std::vector<entity::Tweet> &tweets,
            const std::vector<std::optional<double>> &sentimentTweets,
            const std::vector<entity::State> &states) {
        std::vector<std::optional<double>> result;
        result.reserve(states.size());

        const auto isTweetInState = [](const entity::Tweet &tweet, const entity::State &state) {
            return isPointInPolygons(tweet.position, state.polygons);
        };

        for (const auto &state: states) {
            double total = 0.0;
            size_t count = 0;

            for (size_t i = 0; i < tweets.size(); ++i) {
                if (isTweetInState(tweets[i], state)) {
                    if (sentimentTweets[i].has_value()){
                        total += sentimentTweets[i].value_or(0.0);
                        ++count;
                    }
                }
            }

            result.emplace_back(count ? std::optional(total / count) : std::nullopt);
        }

        return result;
    }
} // algorithm