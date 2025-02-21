#include <opencv2/opencv.hpp>
#include <vector>

int main() {
    // Размер изображения
    int width = 1920, height = 1200;

    // Создаём белое изображение
    cv::Mat img = cv::Mat::ones(height, width, CV_8UC3) * 255;

    // Определяем вершины полигона (с использованием cv::Point)
    std::vector<cv::Point> polygon = {
            {100, 100}, {400, 150}, {350, 400}, {150, 350}
    };

    // Заполняем полигон синим цветом
    cv::fillPoly(img, std::vector<std::vector<cv::Point>>{polygon}, cv::Scalar(255, 0, 0));

    // Рисуем границы полигона чёрным цветом с более тонкой и плавной линией
    cv::polylines(img, polygon, true, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);

    // Добавляем текст внутри полигона
    cv::putText(img, "Polygon", {200, 250}, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 0), 2);

    // Сохраняем изображение
    cv::imwrite("polygon.png", img);

    // Показываем изображение
    cv::imshow("Polygon", img);
    cv::waitKey(0);

    return 0;
}
