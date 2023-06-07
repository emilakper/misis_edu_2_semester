#include <trirastr/trirastr.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            throw std::invalid_argument("Error: no input file provided");
        }
        std::ifstream file(argv[1]);
        nlohmann::json j;
        if (!file) {
            throw std::invalid_argument("Error: could not open file");
        }
        file >> j;
        if (j.empty()) {
            throw std::invalid_argument("Error: empty JSON file or there is no one");
        }
        if (!j.contains("point1") || !j["point1"].contains("x") || !j["point1"].contains("y")) {
            throw std::invalid_argument("Error: invalid JSON structure (point1)");
        }
        if (!j.contains("point2") || !j["point2"].contains("x") || !j["point2"].contains("y")) {
            throw std::invalid_argument("Error: invalid JSON structure (point2)");
        }
        if (!j.contains("point3") || !j["point3"].contains("x") || !j["point3"].contains("y")) {
            throw std::invalid_argument("Error: invalid JSON structure (point3)");
        }
        if (!j.contains("color1") || !j["color1"].contains("R") || !j["color1"].contains("G")
            || !j["color1"].contains("B")) {
            throw std::invalid_argument("Error: invalid JSON structure (color1)");
        }
        if (!j.contains("img") || !j["img"].contains("width") || !j["img"].contains("height")
            || !j["img"].contains("R") || !j["img"].contains("G") || !j["img"].contains("B")) {
            throw std::invalid_argument("Error: invalid JSON structure(img)");
        }

        cv::Point v1(j["point1"]["x"], j["point1"]["y"]);
        cv::Point v2(j["point2"]["x"], j["point2"]["y"]);
        cv::Point v3(j["point3"]["x"], j["point3"]["y"]);

        cv::Scalar color1(j["color1"]["B"], j["color1"]["G"], j["color1"]["R"]);

        cv::Mat img(j["img"]["height"], j["img"]["width"], CV_8UC3);
        img = cv::Scalar{ j["img"]["B"],j["img"]["G"],j["img"]["R"] };

        if (v1.x < 0 || v2.x < 0 || v3.x < 0 || v1.x >= img.cols || v2.x >= img.cols || v3.x >= img.cols) {
            throw std::invalid_argument("Error: triangle vertices are out of image bounds");
        }

        if (v1.y < 0 || v2.y < 0 || v3.y < 0 || v1.y >= img.rows || v2.y >= img.rows || v3.y >= img.rows) {
            throw std::invalid_argument("Error: triangle vertices are out of image bounds");
        }

        TriangleRasterizer example(v1, v2, v3, color1);
        example.Draw(img);
        cv::namedWindow("image", cv::WINDOW_NORMAL);
        cv::resizeWindow("image", img.cols, img.rows);
        cv::imshow("image", img);
        cv::waitKey(0);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}