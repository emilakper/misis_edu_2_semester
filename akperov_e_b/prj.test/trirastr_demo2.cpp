#include <trirastr\trirastr.hpp>
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
        demoPicVu(v0, v1, v2, v);
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

/*
int main()
{
    // Создаем треугольник
    cv::Point v0(50, 55);
    cv::Point v1(170, 10);
    cv::Point v2(200, 110);
    std::vector<cv::Point> points = { v0, v1, v2 };
    cv::Rect bbox = cv::boundingRect(points);

    // Создаем файл Tikz
    std::ofstream tikzFile("trirastr_demo2_1.tex");

    // Записываем заголовок файла
    tikzFile << "\\documentclass[tikz]{standalone}\n"
        << "\\begin{document}\n"
        << "\\begin{tikzpicture}[xscale=1,yscale=-1]\n";

    // Задаем размер полотна
    tikzFile << "\\draw[help lines, use as bounding box](0, 0) (210, 200);\n";

    // Рисуем рамку, по которой пробегается алгоритм
    tikzFile << "\\draw[blue]"
        << "(" << bbox.x << "," << bbox.y << ") rectangle ("
        << bbox.x + bbox.width - 1 << "," << bbox.y + bbox.height - 1 << ");\n";

    // Рисуем треугольник
    tikzFile << "\\draw[red]"
        << "(" << v0.x << "," << v0.y << ") -- "
        << "(" << v1.x << "," << v1.y << ") -- "
        << "(" << v2.x << "," << v2.y << ") -- cycle;\n";

    // Рисуем единичные векторы
    tikzFile << "\\draw[thick, ->, black] (" << v0.x <<
        "," << v0.y << ") -- (" << v1.x << ", " << v1.y << ");\n";
    tikzFile << "\\draw[thick, ->, black] (" << v0.x <<
        "," << v0.y << ") -- (" << v2.x << ", " << v2.y << ");\n";

    //Задаем рассматриваемый пиксель для треугольника и рисуем векторы с весами для него
    int x = 125;
    int y = 35;
    double denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
    double w0 = ((v1.y - v2.y) * (x - v2.x) + (v2.x - v1.x) * (y - v2.y)) / denom;
    double w1 = ((v2.y - v0.y) * (x - v2.x) + (v0.x - v2.x) * (y - v2.y)) / denom;
    double w2 = 1.0 - w0 - w1;

    tikzFile << "\\draw[thick, ->, purple,line width=15pt] (" << v0.x <<
        "," << v0.y << ") -- (" << v0.x+(v1.x-v0.x)*w1 << ", " << v0.y + (v1.y - v0.y) * w1 << ");\n";
    tikzFile << "\\draw[thick, ->, purple,line width=15pt] (" << v0.x + (v1.x - v0.x) * w1 <<
        "," << v0.y + (v1.y - v0.y) * w1 << ") -- (" << v0.x + (v1.x - v0.x) * w1 + (v2.x - v0.x) * w2 << ", " << v0.y + (v1.y - v0.y) * w1 + (v2.y - v0.y) * w2 << ");\n";
    tikzFile << "\\draw[thick, ->, purple,line width=15pt] (" << v0.x <<
        "," << v0.y << ") -- (" << v0.x + (v2.x - v0.x) * w2 << ", " << v0.y + (v2.y - v0.y) * w2 << ");\n";

    tikzFile << "\\draw[fill={rgb:red,"<< w0 <<"; green, "<< w1 <<"; blue, " 
        << w0 << "}](" << x - 0.5 << ", " << y - 0.5 << ") rectangle(" <<
        x + 0.5 << "," << y + 0.5 << ");\n";

    //Подписываем вершины
    tikzFile << "\\node[scale = 20] at(" << v0.x - 3 << "," << v0.y << ") {A};\n";
    tikzFile << "\\node[scale = 20] at(" << v1.x + 3 << "," << v1.y << ") {B};\n";
    tikzFile << "\\node[scale = 20] at(" << v2.x + 3 << "," << v2.y << ") {C};\n";

    //Подписываем вектора-компоненты для рассматриваемого пикселя
    tikzFile << "\\node[scale = 10] at(" << v0.x + (v1.x - v0.x) * w1 << 
        ", " << v0.y + (v1.y - v0.y) * w1 - 4 << ") { w1 x AB };\n";
    tikzFile << "\\node[scale = 10] at(" << v0.x + (v1.x - v0.x) * w1 + (v2.x - v0.x) * w2 <<
        ", " << v0.y + (v1.y - v0.y) * w1 + (v2.y - v0.y) * w2 + 4 << ") { w1 x AB };\n";

    //Рядом с картинкой прописываем полученные с помощью формул значения для каждой прямой
    tikzFile << "\\node[scale = 20] at(75, 140) { w0 = " << w0 << ", w1 ="
        << w1 << ", w2 = " << w2 << "};\n";

    // Рисуем изображение в файле Tikz
    tikzFile << "\\end{tikzpicture}\n"
        << "\\end{document}\n";
    tikzFile.close();

    // Повторяем аналогично для пикселя вне треугольника
    std::ofstream tikzFile2("trirastr_demo2_2.tex");
    tikzFile2 << "\\documentclass[tikz]{standalone}\n"
        << "\\begin{document}\n"
        << "\\begin{tikzpicture}[xscale=1,yscale=-1]\n";
    tikzFile2 << "\\draw[help lines, use as bounding box](0, 0) (210, 200);\n";
    tikzFile2 << "\\draw[blue]"
        << "(" << bbox.x << "," << bbox.y << ") rectangle ("
        << bbox.x + bbox.width - 1 << "," << bbox.y + bbox.height - 1 << ");\n";
    tikzFile2 << "\\draw[red]"
        << "(" << v0.x << "," << v0.y << ") -- "
        << "(" << v1.x << "," << v1.y << ") -- "
        << "(" << v2.x << "," << v2.y << ") -- cycle;\n";
    tikzFile2 << "\\draw[thick, ->, black] (" << v0.x <<
        "," << v0.y << ") -- (" << v1.x << ", " << v1.y << ");\n";
    tikzFile2 << "\\draw[thick, ->, black] (" << v0.x <<
        "," << v0.y << ") -- (" << v2.x << ", " << v2.y << ");\n";
    // Пиксель вне треугольника
    x = 75;
    y = 75;
    denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
    w0 = ((v1.y - v2.y) * (x - v2.x) + (v2.x - v1.x) * (y - v2.y)) / denom;
    w1 = ((v2.y - v0.y) * (x - v2.x) + (v0.x - v2.x) * (y - v2.y)) / denom;
    w2 = 1.0 - w0 - w1;
    tikzFile2 << "\\draw[thick, ->, purple,line width=15pt] (" << v0.x <<
        "," << v0.y << ") -- (" << v0.x + (v1.x - v0.x) * w1 << ", " << v0.y + (v1.y - v0.y) * w1 << ");\n";
    tikzFile2 << "\\draw[thick, ->, purple,line width=15pt] (" << v0.x + (v1.x - v0.x) * w1 <<
        "," << v0.y + (v1.y - v0.y) * w1 << ") -- (" << v0.x + (v1.x - v0.x) * w1 + (v2.x - v0.x) * w2 << ", " << v0.y + (v1.y - v0.y) * w1 + (v2.y - v0.y) * w2 << ");\n";
    tikzFile2 << "\\draw[thick, ->, purple,line width=15pt] (" << v0.x <<
        "," << v0.y << ") -- (" << v0.x + (v2.x - v0.x) * w2 << ", " << v0.y + (v2.y - v0.y) * w2 << ");\n";
    tikzFile2 << "\\draw[fill=white](" << x - 0.5 << ", " << y - 0.5 << ") rectangle(" <<
        x + 0.5 << "," << y + 0.5 << ");\n";
    tikzFile2 << "\\node[scale = 20] at(" << v0.x - 3 << "," << v0.y << ") {A};\n";
    tikzFile2 << "\\node[scale = 20] at(" << v1.x + 3 << "," << v1.y << ") {B};\n";
    tikzFile2 << "\\node[scale = 20] at(" << v2.x + 3 << "," << v2.y << ") {C};\n";
    tikzFile2 << "\\node[scale = 10] at(" << v0.x + (v1.x - v0.x) * w1 <<
        ", " << v0.y + (v1.y - v0.y) * w1 - 4 << ") { w1 x AB };\n";
    tikzFile2 << "\\node[scale = 10] at(" << v0.x + (v1.x - v0.x) * w1 + (v2.x - v0.x) * w2 <<
        ", " << v0.y + (v1.y - v0.y) * w1 + (v2.y - v0.y) * w2 + 4 << ") { w1 x AB };\n";
    tikzFile2 << "\\node[scale = 20] at(75, 140) { w0 = " << w0 << ", w1 ="
        << w1 << ", w2 = " << w2 << "};\n";
    tikzFile2 << "\\end{tikzpicture}\n"
        << "\\end{document}\n";
    tikzFile2.close();
}*/