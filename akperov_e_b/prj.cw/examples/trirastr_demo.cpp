#include <trirastr/trirastr.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>


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
        if (!j.contains("pixel") || !j["pixel"].contains("x") || !j["pixel"].contains("y")) {
            throw std::invalid_argument("Error: invalid JSON structure (point3)");
        }
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