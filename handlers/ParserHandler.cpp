#include "ParserHandler.h"
#include <fstream>

namespace handler {

    ParserHandler::ParserHandler(const std::string &statesPath,
                                 const std::string &tweetsPath,
                                 const std::string &sentimentsPath) : pathToStates(statesPath),
                                                               pathToTweets(tweetsPath),
                                                               pathToSentiments(sentimentsPath) {
    }

    void ParserHandler::loadAll() {
        loadStates();
        loadTweets();
        loadSentiments();
    }

    void ParserHandler::loadStates() {
        std::ifstream file(pathToStates);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open states file: " + pathToStates);
        }

        std::string jsonContent(
                (std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>()
        );

        states = parser::json::statesParse(jsonContent);
    }

    void ParserHandler::loadTweets() {
        tweets = parser::txt::parseTweets(pathToTweets);
        if (tweets.empty()) {
            throw std::runtime_error("No tweets parsed from: " + pathToTweets);
        }
    }

    void ParserHandler::loadSentiments() {
        sentiments = parser::csv::parseSentiments(pathToSentiments);
        if (sentiments.empty()) {
            throw std::runtime_error("No sentiments parsed from: " + pathToSentiments);
        }
    }

    const std::vector<entity::State> &ParserHandler::getStates() const {
        return states;
    }

    const std::vector<entity::Tweet> &ParserHandler::getTweets() const {
        return tweets;
    }

    const entity::Sentiments &ParserHandler::getSentiments() const {
        return sentiments;
    }
} // namespace handler