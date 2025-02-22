//
// Created by gydgem on 2/22/2025.
//

#ifndef TWITTERTRENDSOOPLAB_PARSERSJSON_H
#define TWITTERTRENDSOOPLAB_PARSERSJSON_H

#include "State.h"
#include <boost/json.hpp>


namespace parser::json {
    namespace json = boost::json;

    std::vector<State> statesParse(const std::string &strJSON);
} // parser::json

#endif //TWITTERTRENDSOOPLAB_PARSERSJSON_H
