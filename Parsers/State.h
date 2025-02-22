//
// Created by gydgem on 2/22/2025.
//

#ifndef TWITTERTRENDSOOPLAB_STATE_H
#define TWITTERTRENDSOOPLAB_STATE_H


#include <string>
#include <opencv2/opencv.hpp>
#include "Polygon.h"

struct State {
    std::string name;
    std::vector<Polygon2d> polygons;

    State() = default;

    State(std::string name, std::vector<Polygon2d> polygons);
};


#endif //TWITTERTRENDSOOPLAB_STATE_H
