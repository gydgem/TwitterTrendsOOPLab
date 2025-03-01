#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>
#include "entity/Polygon.h"
#include "entity/State.h"
#include "Parsers/ParsersJSON.h"
#include "renders/Render.h"

std::ostream &operator<<(std::ostream &os, const cv::Point2d &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
}

std::ostream &operator<<(std::ostream &os, const entity::Polygon2d &polygon) {
    os << "[";
    for (size_t i = 0; i < polygon.size(); ++i) {
        os << polygon[i];
        if (i < polygon.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::ostream &operator<<(std::ostream &os, const entity::State &state) {
    os << "State: " << state.name << "\n";
    os << "Polygons:\n";
    for (size_t i = 0; i < state.polygons.size(); ++i) {
        os << "  Polygon2d " << i + 1 << ": " << state.polygons[i] << "\n";
    }
    return os;
}

std::string readFileToString(const std::string &filePath) {
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    auto str = readFileToString("resources/data/states.json");

    auto states = parser::json::statesParse(str);

    std::vector<entity::Polygon2d> polygons;
    std::vector<std::string> names;
    for (auto &state: states) {
        for (auto &polygon: state.polygons) {
            for (auto &point: polygon) {
                point.y *= -1;
            }

            polygons.emplace_back(polygon);
            names.emplace_back(state.name);
        }
    }

    cv::Mat image = cv::Mat::zeros(1080, 1920, CV_8UC3);
    image.setTo(cv::Scalar(255, 255, 255)); // Белый фон

    std::vector<entity::Polygon2i> tempPolygons = render::changingThePolygons(polygons, 1080, 1920);

    render::draw(image, tempPolygons);
    render::drawInTheCenter(image, names, tempPolygons);

    cv::imshow("Polygons on Image", image);
    cv::waitKey(0);

    cv::imwrite("output.png", image);

    return 0;
}
