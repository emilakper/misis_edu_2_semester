#include <trirastr/trirastr.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>


int main(int argc, char* argv[]) {
    std::ifstream file(argv[1]);
    nlohmann::json j;
    try {
        if (!file) {
            throw std::invalid_argument("Error: could not open file");
        }
        file >> j;
        cv::Point v0(j["point1"]["x"], j["point1"]["y"]);
        cv::Point v1(j["point2"]["x"], j["point2"]["y"]);
        cv::Point v2(j["point3"]["x"], j["point3"]["y"]);
        cv::Point v(j["pixel"]["x"], j["pixel"]["y"]);
        demoPic(v0, v1, v2, v);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}