//
// Created by gydgem on 4/16/2025.
//

#ifndef TWITTERTRENDSOOPLAB_DATAPROCESSINGHANDLER_H
#define TWITTERTRENDSOOPLAB_DATAPROCESSINGHANDLER_H

#include <vector>
#include "../entity/Polygon.h"
#include "../entity/Sentiments.h"
#include "../entity/Tweet.h"
#include "../entity/State.h"
#include "../data_structures/Bor.h"
#include "../algorithms/sentiment_score.h"
#include "../algorithms/scalings.h"

namespace handler {

    class DataProcessingHandler {
        const std::vector<entity::State> &states;
        const std::vector<entity::Tweet> &tweets;
        const entity::Sentiments &sentiments;

        double minX = 0, minY = 0, scale = 1;
        std::vector<std::vector<entity::Polygon2i>> scaledStatesPolygons;
        std::vector<cv::Point2i> scaledTweetsPoints;
        std::vector<std::optional<double>> sentimentTweets;
        std::vector<std::optional<double>> sentimentStates;
        entity::Bor<char, double> sentimentsBor;

        void generateSentimentsBor();

        void generateSentimentTweets();

        void generateSentimentStates();

        void generateScaled();

    public:

        DataProcessingHandler(const std::vector<entity::State> &states,
                              const std::vector<entity::Tweet> &tweets,
                              const entity::Sentiments &sentiments);

        void calculateAll();

        [[nodiscard]]  double getMinX() const;

        [[nodiscard]] double getMinY() const;

        [[nodiscard]] double getScale() const;

        [[nodiscard]] const std::vector<std::vector<entity::Polygon2i>> &getScaledStatesPolygons() const;

        [[nodiscard]] const std::vector<cv::Point2i> &getScaledTweetsPoints() const;

        [[nodiscard]]  const std::vector<std::optional<double>> &getSentimentTweets() const;

        [[nodiscard]]  const std::vector<std::optional<double>> &getSentimentStates() const;
    };
} // handler

#endif //TWITTERTRENDSOOPLAB_DATAPROCESSINGHANDLER_H
