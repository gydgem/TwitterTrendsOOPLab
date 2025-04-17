//
// Created by gydgem on 3/27/2025.
//

#ifndef TWITTERTRENDSOOPLAB_PARSERSCSV_H
#define TWITTERTRENDSOOPLAB_PARSERSCSV_H

#include "../entity/Sentiments.h"
#include "../include/csv2.hpp"

namespace parser::csv {
    entity::Sentiments parseSentiments(const std::string &path);
} //parser::csv


#endif //TWITTERTRENDSOOPLAB_PARSERSCSV_H
