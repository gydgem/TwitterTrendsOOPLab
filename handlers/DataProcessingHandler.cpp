//
// Created by gydgem on 4/16/2025.
//

#include "DataProcessingHandler.h"


namespace handler {
    void DataProcessingHandler::generateSentimentsBor() {
        for (const auto &[msg, value]: sentiments) {
            sentimentsBor.insert(msg.begin(), msg.end(), value);
        }
    }

    void DataProcessingHandler::generateSentimentTweets() {
        sentimentTweets = {};
        sentimentTweets.reserve(tweets.size());
        for (const auto &[position, msg]: tweets) {
            sentimentTweets.emplace_back(algorithm::calculateSentimentScore(msg, sentimentsBor));
        }
    }

    void DataProcessingHandler::generateSentimentStates() {
        sentimentStates = algorithm::calculateSentimentScore(tweets, sentimentTweets, states);
    }

    void DataProcessingHandler::generateScaled() {
        std::vector<entity::Polygon2d> polygons;
        std::vector<cv::Point2d> points;

        for (const auto &state: states) {
            for (const auto &polygon: state.polygons) {
                polygons.emplace_back(polygon);
            }
        }

        for (const auto &tweet: tweets) {
            points.emplace_back(tweet.position);
        }

        algorithm::getScale(polygons, 1080, 1920, scale, minX, minY);

        auto mirrorPolygons = [](std::vector<entity::Polygon2i> &polygons) {
            for (auto &polygon: polygons) {
                for (auto &point: polygon) {
                    point.y = 1080 - point.y;
                }
            }
        };

        auto mirrorPoint = [](std::vector<cv::Point2i> &points) {
            for (auto &point: points) {
                point.y = 1080 - point.y;
            }
        };

        for (const auto &state: states) {
            scaledStatesPolygons.emplace_back(algorithm::scalingThePolygons(state.polygons, scale, minX, minY));
            mirrorPolygons(scaledStatesPolygons.back());
        }

        scaledTweetsPoints = algorithm::scalingThePoints(points, scale, minX, minY);
        mirrorPoint(scaledTweetsPoints);
    }

    double DataProcessingHandler::getMinX() const {
        return minX;
    }

    double DataProcessingHandler::getMinY() const {
        return minY;
    }

    double DataProcessingHandler::getScale() const {
        return scale;
    }

    const std::vector<std::vector<entity::Polygon2i>> &DataProcessingHandler::getScaledStatesPolygons() const {
        return scaledStatesPolygons;
    }

    const std::vector<cv::Point2i> &DataProcessingHandler::getScaledTweetsPoints() const {
        return scaledTweetsPoints;
    }

    const std::vector<std::optional<double>> &DataProcessingHandler::getSentimentTweets() const {
        return sentimentTweets;
    }

    const std::vector<std::optional<double>> &DataProcessingHandler::getSentimentStates() const {
        return sentimentStates;
    }

    DataProcessingHandler::DataProcessingHandler(const std::vector<entity::State> &states,
                                                 const std::vector<entity::Tweet> &tweets,
                                                 const entity::Sentiments &sentiments) : states(states),
                                                                                         tweets(tweets),
                                                                                         sentiments(sentiments) {
    }

    void DataProcessingHandler::calculateAll() {
        generateSentimentsBor();
        generateSentimentTweets();
        generateSentimentStates();
        generateSentimentStates();
        generateScaled();
    }
} // handler