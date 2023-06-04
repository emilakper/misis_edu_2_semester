#include <trirastr/trirastr.hpp>
#include <fstream>
#include <nlohmann/json.hpp>

int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    nlohmann::json j;
    try {
        if (!file) {
            throw std::invalid_argument("Error: could not open file");
        }
        file >> j;
        cv::Point v1(j["point1"]["x"], j["point1"]["y"]);
        cv::Point v2(j["point2"]["x"], j["point2"]["y"]);
        cv::Point v3(j["point3"]["x"], j["point3"]["y"]);

        cv::Scalar color1(j["color1"]["B"], j["color1"]["G"], j["color1"]["R"]);
        cv::Scalar color2(j["color2"]["B"], j["color2"]["G"], j["color2"]["R"]);
        cv::Scalar color3(j["color3"]["B"], j["color3"]["G"], j["color3"]["R"]);

        cv::Mat img(j["img"]["height"], j["img"]["width"], CV_8UC3);
        img = cv::Scalar{j["img"]["B"],j["img"]["G"],j["img"]["R"]};

        TriangleRasterizerVu example(v1, v2, v3, color1, color2, color3);
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