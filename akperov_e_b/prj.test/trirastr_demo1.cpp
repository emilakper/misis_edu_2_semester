#include <trirastr\trirastr.hpp>
#include <fstream>

int main()
{
    // Создаем треугольник
    cv::Point v0(50, 10);
    cv::Point v1(200, 10);
    cv::Point v2(200, 110);
    std::vector<cv::Point> points = { v0, v1, v2 };
    cv::Rect bbox = cv::boundingRect(points);

    // Создаем файл Tikz
    std::ofstream tikzFile("trirastr_demo1_1.tex");

    // Записываем заголовок файла
    tikzFile << "\\documentclass[tikz]{standalone}\n"
        << "\\begin{document}\n"
        << "\\begin{tikzpicture}[xscale=1,yscale=-1]\n";

    // Задаем размер полотна
    tikzFile << "\\draw[help lines, use as bounding box](0, 0) (210, 200);\n";

    // Рисуем рамку, по которой пробегается алгоритм
    tikzFile << "\\draw[blue]"
        << "(" << bbox.x << "," << bbox.y << ") rectangle ("
        << bbox.x+ bbox.width-1 << "," << bbox.y+ bbox.height-1 << ");\n";

    // Рисуем треугольник
    tikzFile << "\\draw[red]"
        << "(" << v0.x << "," << v0.y << ") -- "
        << "(" << v1.x << "," << v1.y << ") -- "
        << "(" << v2.x << "," << v2.y << ") -- cycle;\n";

    // Задаем рассматриваемый пиксель для треугольника и проводим рассчеты
    int x = 125;
    int y = 35;
    tikzFile << "\\draw[fill = orange](" << x - 0.5 << "," << y - 0.5 
        << ") rectangle(" << x + 0.5 << "," << y + 0.5 << ");\n";
    int aSide = (v0.y - v1.y) * x + (v1.x - v0.x) * y + (v0.x * v1.y - v1.x * v0.y);
    int bSide = (v1.y - v2.y) * x + (v2.x - v1.x) * y + (v1.x * v2.y - v2.x * v1.y);
    int cSide = (v2.y - v0.y) * x + (v0.x - v2.x) * y + (v2.x * v0.y - v0.x * v2.y);
    
    // Задаем штриховые линии, соединяющие вершины с рассматриваемым пикселем(для лучшей видимости)
    tikzFile << "\\draw[dashed, ultra thick](" << v0.x << "," << v0.y 
        << ") -- (" << x << "," << y << ");\n";
    tikzFile << "\\draw[dashed, ultra thick](" << v1.x << "," << v1.y 
        << ") -- (" << x << "," << y << ");\n";
    tikzFile << "\\draw[dashed, ultra thick](" << v2.x << "," << v2.y 
        << ") -- (" << x << "," << y << ");\n";

    //Подписываем вершины
    tikzFile << "\\node[scale = 20] at(" << v0.x - 3 << "," << v0.y << ") {A};\n";
    tikzFile << "\\node[scale = 20] at(" << v1.x + 3 << "," << v1.y << ") {B};\n";
    tikzFile << "\\node[scale = 20] at(" << v2.x + 3 << "," << v2.y << ") {C};\n";

    //Рядом с картинкой прописываем полученные с помощью формул значения для каждой прямой
    tikzFile << "\\node[scale = 20] at(75, 140) { AB:a = " << v0.y - v1.y << ", b = " 
        << v1.x - v0.x << ", c = " << v0.x * v1.y - v1.x * v0.y << ", aSide="<<aSide<<"};\n";
    tikzFile << "\\node[scale = 20] at(75, 160) { BC:a = " << v1.y - v2.y << ", b = " 
        << v2.x - v1.x << ", c = " << v1.x * v2.y - v2.x * v1.y << ", bSide=" << bSide << "};\n";
    tikzFile << "\\node[scale = 20] at(75, 180) { CA:a = " << v2.y - v0.y << ", b = " 
        << v0.x - v2.x << ", c = " << v2.x * v0.y - v0.x * v2.y << ", cSide=" << cSide << "};\n";

    // Рисуем изображение в файле Tikz
    tikzFile << "\\end{tikzpicture}\n"
        << "\\end{document}\n";
    tikzFile.close();

    //Аналогичные действия для второй картинки с пикселем вне треугольника
    std::ofstream tikzFile2("trirastr_demo1_2.tex");

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

    // Другой пиксель вне трегольника
    x = 125;
    y = 75;
    tikzFile2 << "\\draw[fill = orange](" << x - 0.5 << "," << y - 0.5
        << ") rectangle(" << x + 0.5 << "," << y + 0.5 << ");\n";
    aSide = (v0.y - v1.y) * x + (v1.x - v0.x) * y + (v0.x * v1.y - v1.x * v0.y);
    bSide = (v1.y - v2.y) * x + (v2.x - v1.x) * y + (v1.x * v2.y - v2.x * v1.y);
    cSide = (v2.y - v0.y) * x + (v0.x - v2.x) * y + (v2.x * v0.y - v0.x * v2.y);

    tikzFile2 << "\\draw[dashed, ultra thick](" << v0.x << "," << v0.y
        << ") -- (" << x << "," << y << ");\n";
    tikzFile2 << "\\draw[dashed, ultra thick](" << v1.x << "," << v1.y
        << ") -- (" << x << "," << y << ");\n";
    tikzFile2 << "\\draw[dashed, ultra thick](" << v2.x << "," << v2.y
        << ") -- (" << x << "," << y << ");\n";

    tikzFile2 << "\\node[scale = 20] at(" << v0.x - 3 << "," << v0.y << ") {A};\n";
    tikzFile2 << "\\node[scale = 20] at(" << v1.x + 3 << "," << v1.y << ") {B};\n";
    tikzFile2 << "\\node[scale = 20] at(" << v2.x + 3 << "," << v2.y << ") {C};\n";

    tikzFile2 << "\\node[scale = 20] at(75, 140) { AB:a = " << v0.y - v1.y << ", b = "
        << v1.x - v0.x << ", c = " << v0.x * v1.y - v1.x * v0.y << ", aSide=" << aSide << "};\n";
    tikzFile2 << "\\node[scale = 20] at(75, 160) { BC:a = " << v1.y - v2.y << ", b = "
        << v2.x - v1.x << ", c = " << v1.x * v2.y - v2.x * v1.y << ", bSide=" << bSide << "};\n";
    tikzFile2 << "\\node[scale = 20] at(75, 180) { CA:a = " << v2.y - v0.y << ", b = "
        << v0.x - v2.x << ", c = " << v2.x * v0.y - v0.x * v2.y << ", cSide=" << cSide << "};\n";

    tikzFile2 << "\\end{tikzpicture}\n"
        << "\\end{document}\n";
    tikzFile2.close();
}