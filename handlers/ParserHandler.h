//
// Created by gydgem on 4/16/2025.
//

#ifndef TWITTERTRENDSOOPLAB_PARSERHANDLER_H
#define TWITTERTRENDSOOPLAB_PARSERHANDLER_H

#include <stdexcept>
#include "../parsers/ParsersJSON.h"
#include "../parsers/ParsersTxt.h"
#include "../parsers/ParsersCSV.h"

namespace handler {

    class ParserHandler {
    private:
        const std::string &pathToStates;
        const std::string &pathToTweets;
        const std::string &pathToSentiments;

        std::vector<entity::State> states;
        std::vector<entity::Tweet> tweets;
        entity::Sentiments sentiments;

        void loadStates();

        void loadTweets();

        void loadSentiments();

    public:

        ParserHandler(const std::string &statesPath,
                      const std::string &tweetsPath,
                      const std::string &sentimentsPath);

        void loadAll();

        [[nodiscard]] const std::vector<entity::State> &getStates() const;

        [[nodiscard]] const std::vector<entity::Tweet> &getTweets() const;

        [[nodiscard]] const entity::Sentiments &getSentiments() const;


    };

} // namespace handler

#endif //TWITTERTRENDSOOPLAB_PARSERHANDLER_H