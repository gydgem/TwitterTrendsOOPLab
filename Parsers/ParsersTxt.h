//
// Created by gydgem on 2/24/2025.
//

#ifndef TWITTERTRENDSOOPLAB_PARSERSTXT_H
#define TWITTERTRENDSOOPLAB_PARSERSTXT_H

#include "../entity/Tweet.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <opencv2/core.hpp>

namespace parser::txt {
    std::vector<entity::Tweet> parseTweets(const std::string &path);
} // parser::txt

#endif //TWITTERTRENDSOOPLAB_PARSERSTXT_H
