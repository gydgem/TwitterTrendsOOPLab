//
// Created by gydgem on 2/24/2025.
//

#include "ParsersTxt.h"

namespace parser::txt {

    std::vector<entity::Tweet> parseTweets(const std::string &path) {
        std::vector<entity::Tweet> tweets;
        std::ifstream file(path);
        if (!file.is_open()) {
            return tweets;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t first_tab = line.find('\t');
            if (first_tab == std::string::npos) {
                continue;
            }
            size_t second_tab = line.find('\t', first_tab + 1);
            if (second_tab == std::string::npos) {
                continue;
            }
            size_t third_tab = line.find('\t', second_tab + 1);
            if (third_tab == std::string::npos) {
                continue;
            }

            std::string coord_str = line.substr(0, first_tab);
            if (coord_str.empty() || coord_str.front() != '[' || coord_str.back() != ']') {
                continue;
            }
            std::string coords = coord_str.substr(1, coord_str.size() - 2);

            size_t comma_pos = coords.find(',');
            if (comma_pos == std::string::npos) {
                continue;
            }
            std::string lat_str = coords.substr(0, comma_pos);
            std::string lon_str = coords.substr(comma_pos + 1);

            auto trim = [](std::string &s) {
                s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                    return !std::isspace(ch);
                }));
                s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                    return !std::isspace(ch);
                }).base(), s.end());
            };
            trim(lat_str);
            trim(lon_str);

            double lat, lon;
            try {
                lat = std::stod(lat_str);
                lon = std::stod(lon_str);
            } catch (const std::exception &) {
                continue;
            }

            std::string tweet_text = line.substr(third_tab + 1);

            entity::Tweet tweet;
            tweet.position = cv::Point2d(lon, lat);
            tweet.tweet = tweet_text;
            tweets.push_back(tweet);
        }

        return tweets;
    }
} // parser::txt