//
// Created by gydgem on 2/22/2025.
//

#ifndef TWITTERTRENDSOOPLAB_PARSERSJSON_H
#define TWITTERTRENDSOOPLAB_PARSERSJSON_H

#include "../entity/State.h"
#include <boost/json.hpp>


namespace parser::json {
    namespace json = boost::json;

    entity::Polygon2d parseStatePolygon2d(const json::array &value);

    std::vector<entity::State> statesParse(const std::string &strJSON);

    std::vector<entity::State> statesParseFromFile(std::string &path);
} // parser::json

#endif //TWITTERTRENDSOOPLAB_PARSERSJSON_H
