//
// Created by gydgem on 3/27/2025.
//

#include "ParsersCSV.h"


namespace parser::csv {
    entity::Sentiments parseSentiments(const std::string &path) {
        csv2::Reader<> reader;
        std::ifstream file(path);
        std::string content((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());

        if (!reader.parse(content)) return {};

        entity::Sentiments result;

        for (const auto &row: reader) {
            std::vector<std::string> cells;

            for (const auto &cell: row) {
                cells.emplace_back();
                cell.read_value(cells.back());
            }

            if (cells.size() >= 2) {
                result.emplace_back(
                        cells[0],
                        std::stod(cells[1])
                );
            }
        }

        return result;
    }
} //parser::csv
