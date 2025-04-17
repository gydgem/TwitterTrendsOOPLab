//
// Created by gydgem on 4/16/2025.
//

#ifndef TWITTERTRENDSOOPLAB_SENTIMENT_SCORE_H
#define TWITTERTRENDSOOPLAB_SENTIMENT_SCORE_H

#include <string>
#include "../entity/Tweet.h"
#include "../entity/State.h"
#include "../data_structures/Bor.h"

namespace algorithm {

    std::optional<double> calculateSentimentScore(const std::string &tweet,
                                                  const entity::Bor<char, double> &sentiments);

    std::vector<std::optional<double>> calculateSentimentScore(const std::vector<entity::Tweet> &tweets,
                                                               const std::vector<std::optional<double>> &sentimentTweets,
                                                               const std::vector<entity::State> &states);

    bool isPointInPolygons(const cv::Point2d &point,
                           const std::vector<entity::Polygon2d> &polygons);
} // algorithm

#endif //TWITTERTRENDSOOPLAB_SENTIMENT_SCORE_H
