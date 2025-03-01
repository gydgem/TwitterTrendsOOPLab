//
// Created by gydgem on 2/22/2025.
//

#include "ParsersJSON.h"

namespace parser::json {
    entity::Polygon2d parseStatePolygon2d(const json::array &value) {
        entity::Polygon2d res;

        for (const auto &it: value) {
            if (!it.is_array() || it.as_array().size() != 2) {
                throw std::runtime_error("Invalid JSON: Polygon2d");
            }

            double point[2];

            for (size_t i = 0; i < 2; i++) {
                if (it.as_array().at(0).is_double()) {
                    point[i] = it.as_array().at(i).as_double();
                } else if (it.as_array().at(i).is_int64()) {
                    point[i] = it.as_array().at(i).as_int64();
                }
            }

            res.emplace_back(point[0], point[1]);
        }

        return res;
    }

    std::vector<entity::State> statesParse(const std::string &strJSON) {
        std::vector<entity::State> res;
        json::value jv = json::parse(strJSON);
        if (!jv.is_object()) {
            throw std::runtime_error("Invalid JSON: State");
        }

        json::object jo = jv.as_object();
        for (const auto &[key, value]: jo) {
            if (!value.is_array()) {
                throw std::runtime_error("Invalid JSON: State");
            }

            res.emplace_back();
            res.back().name = key;
            json::array temp = value.as_array();

            if (temp.size() == 1) {
                if (!temp.at(0).is_array()) {
                    throw std::runtime_error("Invalid JSON: State");
                }

                res.back().polygons.emplace_back(parseStatePolygon2d(temp.at(0).as_array()));
            } else {
                for (auto polygon: temp) {
                    if (!polygon.at(0).is_array()) {
                        throw std::runtime_error("Invalid JSON: State");
                    }

                    try {
                        res.back().polygons.emplace_back(parseStatePolygon2d(polygon.at(0).as_array()));
                    }
                    catch (std::exception) {
                        throw std::runtime_error("Invalid JSON: State");
                    }
                }
            }
        }

        res.shrink_to_fit();
        return res;
    }

}// parser::json