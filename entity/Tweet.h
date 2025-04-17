//
// Created by gydgem on 3/27/2025.
//

#ifndef TWITTERTRENDSOOPLAB_TWEET_H
#define TWITTERTRENDSOOPLAB_TWEET_H


#include <opencv2/core/types.hpp>
#include <chrono>

namespace chrono = std::chrono;

namespace entity {
    struct Tweet {
        cv::Point2d position;
        std::string tweet;
    };
}

#endif //TWITTERTRENDSOOPLAB_TWEET_H
