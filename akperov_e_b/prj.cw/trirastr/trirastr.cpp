#include <trirastr/trirastr.hpp>


TriangleRasterizer::TriangleRasterizer(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0) {
    v0_ = v0;
    v1_ = v1;
    v2_ = v2;
    color0_ = color0;
}

void TriangleRasterizer::setTriangle(cv::Point& v0, cv::Point& v1, cv::Point& v2) {
    v0_ = v0;
    v1_ = v1;
    v2_ = v2;
}

void TriangleRasterizer::setColor(cv::Scalar& color0) {
    color0_ = color0;
}

bool TriangleRasterizer::IsPointInTriangle(const cv::Point& p)
{
    int aSide = (v0_.y - v1_.y) * p.x + (v1_.x - v0_.x) * p.y + (v0_.x * v1_.y - v1_.x * v0_.y);
    int bSide = (v1_.y - v2_.y) * p.x + (v2_.x - v1_.x) * p.y + (v1_.x * v2_.y - v2_.x * v1_.y);
    int cSide = (v2_.y - v0_.y) * p.x + (v0_.x - v2_.x) * p.y + (v2_.x * v0_.y - v0_.x * v2_.y);
    return (aSide >= 0 && bSide >= 0 && cSide >= 0) || (aSide < 0 && bSide < 0 && cSide < 0);
}

void TriangleRasterizer::Draw(cv::Mat& image)
{
    std::vector<cv::Point> points = { v0_, v1_, v2_ };
    cv::Rect bbox = cv::boundingRect(points);
    for (int y = bbox.y; y < bbox.y + bbox.height; y++) {
        for (int x = bbox.x; x < bbox.x + bbox.width; x++) {
            cv::Point point(x, y);
            if (IsPointInTriangle(point)) {
                image.at<cv::Vec3b>(y, x)[0] = color0_[0];
                image.at<cv::Vec3b>(y, x)[1] = color0_[1];
                image.at<cv::Vec3b>(y, x)[2] = color0_[2];
            }
        }
    }
}

void TriangleRasterizerVu::setColor(cv::Scalar& color0, cv::Scalar& color1, cv::Scalar& color2) {
    color0_ = color0;
    color1_ = color1;
    color2_ = color2;
}

TriangleRasterizerVu::TriangleRasterizerVu(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0, cv::Scalar& color1, cv::Scalar& color2) {
    v0_ = v0;
    v1_ = v1;
    v2_ = v2;
    color0_ = color0;
    color1_ = color1;
    color2_ = color2;
}

void TriangleRasterizerVu::CalculateWeights(const cv::Point& p, double& w0, double& w1, double& w2)
{
    double denom = (v1_.y - v2_.y) * (v0_.x - v2_.x) + (v2_.x - v1_.x) * (v0_.y - v2_.y);
    w0 = ((v1_.y - v2_.y) * (p.x - v2_.x) + (v2_.x - v1_.x) * (p.y - v2_.y)) / denom;
    w1 = ((v2_.y - v0_.y) * (p.x - v2_.x) + (v0_.x - v2_.x) * (p.y - v2_.y)) / denom;
    w2 = 1.0 - w0 - w1;
}

cv::Scalar TriangleRasterizerVu::InterpolateColors(double w0, double w1, double w2)
{
    cv::Scalar color;
    color[0] = w0 * color0_[0] + w1 * color1_[0] + w2 * color2_[0];
    color[1] = w0 * color0_[1] + w1 * color1_[1] + w2 * color2_[1];
    color[2] = w0 * color0_[2] + w1 * color1_[2] + w2 * color2_[2];
    return color;
}

bool TriangleRasterizerVu::IsPointInTriangle(double& w0, double& w1, double& w2)
{
    return (w0 >= 0 && w0 <= 1) && (w1 >= 0 && w1 <= 1) && (w2 >= 0 && w2 <= 1);
}

void TriangleRasterizerVu::Draw(cv::Mat& image)
{
    std::vector<cv::Point> points = { v0_, v1_, v2_ };
    cv::Rect bbox = cv::boundingRect(points);
    for (int y = bbox.y; y < bbox.y + bbox.height; y++) {
        for (int x = bbox.x; x < bbox.x + bbox.width; x++) {
            cv::Point point(x, y);
            double w0, w1, w2;
            CalculateWeights(point, w0, w1, w2);
            cv::Scalar color = InterpolateColors(w0, w1, w2);
            if (IsPointInTriangle(w0, w1, w2)) {
                image.at<cv::Vec3b>(y, x)[0] = color[0];
                image.at<cv::Vec3b>(y, x)[1] = color[1];
                image.at<cv::Vec3b>(y, x)[2] = color[2];
            }
        }
    }
}

void demoPic(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Point& v) {
    std::vector<cv::Point> points = { v0, v1, v2 };
    cv::Rect bbox = cv::boundingRect(points);

    // Создаем файл TikzC:
    std::ofstream tikzFile("../data/results/trirastr_demo.tex");

    // Записываем заголовок файла
    tikzFile << "\\documentclass[tikz]{standalone}\n"
        << "\\usepackage{tkz-euclide}\n" 
        << "\\begin{document}\n"
        << "\\begin{tikzpicture}[xscale=1,yscale=-1]\n";

    // Задаем размер полотна
    tikzFile << "\\tkzInit[xmin=0,xmax=210,ymin=0,ymax=200]\n"
        << "\\tkzClip\n";

    //Задаем вершины треугольника и рассматриваемый пиксель
    tikzFile << "\\coordinate (A) at (" << v0.x << "," << v0.y << ");\n";
    tikzFile << "\\coordinate (B) at (" << v1.x << "," << v1.y << ");\n";
    tikzFile << "\\coordinate (C) at (" << v2.x << "," << v2.y << ");\n";
    tikzFile << "\\coordinate (H) at (" << v.x << "," << v.y << ");\n";


    // Рисуем рамку, по которой пробегается алгоритм
    tikzFile << "\\draw[blue](A) rectangle (C);\n";

    // Рисуем треугольник
    tikzFile << "\\draw[red](A) -- (B) -- (C) -- cycle;\n";

    // Проводим рассчеты и рисуем рассматриваемый пиксель
    int aSide = (v0.y - v1.y) * v.x + (v1.x - v0.x) * v.y + (v0.x * v1.y - v1.x * v0.y);
    int bSide = (v1.y - v2.y) * v.x + (v2.x - v1.x) * v.y + (v1.x * v2.y - v2.x * v1.y);
    int cSide = (v2.y - v0.y) * v.x + (v0.x - v2.x) * v.y + (v2.x * v0.y - v0.x * v2.y);
    if ((aSide >= 0 && bSide >= 0 && cSide >= 0) || (aSide < 0 && bSide < 0 && cSide < 0)) {
        tikzFile << "\\draw[fill = orange](" << v.x - 0.5 << "," << v.y - 0.5
            << ") rectangle(" << v.x + 0.5 << "," << v.y + 0.5 << ");\n";
    }
    else {
        tikzFile << "\\draw(" << v.x - 0.5 << "," << v.y - 0.5
            << ") rectangle(" << v.x + 0.5 << "," << v.y + 0.5 << ");\n";
    }
    // Рисуем высоты до прямых, проходящих через отрезки 
    tikzFile << "\\path(H) -- ($(A)!(H)!(B)$) coordinate(D);\n\
                 \\path(H) -- ($(B)!(H)!(C)$) coordinate(E);\n\
                 \\path(H) -- ($(A)!(H)!(C)$) coordinate(F);\n";
    tikzFile << "\\tkzDrawSegment[style=dashed](H,D);\n\
                 \\tkzDrawSegment[style = dashed](H, E);\n\
                 \\tkzDrawSegment[style = dashed](H, F);\n";

    //Подписываем вершины
    tikzFile << "\\node[scale = 20] at(" << v0.x - 3 << "," << v0.y << ") {A};\n";
    tikzFile << "\\node[scale = 20] at(" << v1.x + 3 << "," << v1.y << ") {B};\n";
    tikzFile << "\\node[scale = 20] at(" << v2.x + 3 << "," << v2.y << ") {C};\n";
    tikzFile << "\\node[scale = 20] at(H) [below] {H};\n";

    //Рядом с картинкой прописываем полученные с помощью формул значения для каждой прямой
    tikzFile << "\\node[scale = 20] at(75, 140) { AB:a = " << v0.y - v1.y << ", b = "
        << v1.x - v0.x << ", c = " << v0.x * v1.y - v1.x * v0.y << ", aSide=" << aSide << "};\n";
    tikzFile << "\\node[scale = 20] at(75, 160) { BC:a = " << v1.y - v2.y << ", b = "
        << v2.x - v1.x << ", c = " << v1.x * v2.y - v2.x * v1.y << ", bSide=" << bSide << "};\n";
    tikzFile << "\\node[scale = 20] at(75, 180) { CA:a = " << v2.y - v0.y << ", b = "
        << v0.x - v2.x << ", c = " << v2.x * v0.y - v0.x * v2.y << ", cSide=" << cSide << "};\n";

    // Рисуем изображение в файле Tikz
    tikzFile << "\\end{tikzpicture}\n"
        << "\\end{document}\n";
    tikzFile.close();
}

void demoPicVu(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Point& v) {
    std::vector<cv::Point> points = { v0, v1, v2 };
    cv::Rect bbox = cv::boundingRect(points);

    // Создаем файл Tikz
    std::ofstream tikzFile("../data/results/trirastr_demoVu.tex");

    // Записываем заголовок файла
    tikzFile << "\\documentclass[tikz]{standalone}\n"
        << "\\usepackage{tkz-euclide}\n"
        << "\\begin{document}\n"
        << "\\begin{tikzpicture}[xscale=1,yscale=-1]\n";

    // Задаем размер полотна
    tikzFile << "\\tkzInit[xmin=0,xmax=210,ymin=0,ymax=200]\n"
        << "\\tkzClip\n";

    //Задаем вершины треугольника и рассматриваемый пиксель
    tikzFile << "\\coordinate (A) at (" << v0.x << "," << v0.y << ");\n";
    tikzFile << "\\coordinate (B) at (" << v1.x << "," << v1.y << ");\n";
    tikzFile << "\\coordinate (C) at (" << v2.x << "," << v2.y << ");\n";
    tikzFile << "\\coordinate (H) at (" << v.x << "," << v.y << ");\n";

    // Рисуем рамку, по которой пробегается алгоритм
    tikzFile << "\\draw[blue](A) rectangle (C);\n";

    // Рисуем треугольник и достаиваем треугольники до пикселя
    tikzFile << "\\draw[red](A) -- (B) -- (C) -- cycle;\n";

    tikzFile << "\\draw (A) -- (H);\n\
                 \\draw(B) -- (H);\n\
                 \\draw(C) -- (H);\n";

    //Задаем рассматриваемый пиксель для треугольника, рассчитываем веса и красим пиксель
    double denom = (v1.y - v2.y) * (v0.x - v2.x) + (v2.x - v1.x) * (v0.y - v2.y);
    double w0 = ((v1.y - v2.y) * (v.x - v2.x) + (v2.x - v1.x) * (v.y - v2.y)) / denom;
    double w1 = ((v2.y - v0.y) * (v.x - v2.x) + (v0.x - v2.x) * (v.y - v2.y)) / denom;
    double w2 = 1.0 - w0 - w1;
    if ((w0 >= 0 && w0 <= 1) && (w1 >= 0 && w1 <= 1) && (w2 >= 0 && w2 <= 1)) {
        tikzFile << "\\draw[fill={rgb:red," << w0 << "; green, " << w1 << "; blue, "
            << w0 << "}](" << v.x - 0.5 << ", " << v.y - 0.5 << ") rectangle(" <<
            v.x + 0.5 << "," << v.y + 0.5 << ");\n";
    }
    else {
        tikzFile << "\\draw(" << v.x - 0.5 << ", " << v.y - 0.5 << ") rectangle(" <<
            v.x + 0.5 << "," << v.y + 0.5 << ");\n";
    }

    //Подписываем вершины
    tikzFile << "\\node[scale = 20] at(" << v0.x - 3 << "," << v0.y << ") {A};\n";
    tikzFile << "\\node[scale = 20] at(" << v1.x + 3 << "," << v1.y << ") {B};\n";
    tikzFile << "\\node[scale = 20] at(" << v2.x + 3 << "," << v2.y << ") {C};\n";
    tikzFile << "\\node[scale = 20] at(H) [above] {H};\n";
    //Рядом с картинкой прописываем полученные с помощью формул значения для каждой прямой
    tikzFile << "\\node[scale = 20] at(75, 140) { w0 = " << w0 << ", w1 ="
        << w1 << ", w2 = " << w2 << "};\n";

    // Рисуем изображение в файле Tikz
    tikzFile << "\\end{tikzpicture}\n"
        << "\\end{document}\n";
    tikzFile.close();
}