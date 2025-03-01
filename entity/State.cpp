//
// Created by gydgem on 2/22/2025.
//

#include "State.h"

namespace entity {
    State::State(std::string name, std::vector<entity::Polygon2d> polygons) : name(std::move(name)),
                                                                              polygons(std::move(polygons)) {
    }
}