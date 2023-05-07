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

void TriangleRasterizer::DrawExplain(cv::Mat& image)
{
    cv::Mat image_copy = image.clone();
    std::vector<cv::Point> points = { v0_, v1_, v2_ };
    cv::Rect bbox = cv::boundingRect(points);
    cv::namedWindow("image", cv::WINDOW_NORMAL);
    cv::resizeWindow("image", image.cols, image.rows);
    for (int y = bbox.y; y < bbox.y + bbox.height; y++) {
        for (int x = bbox.x; x < bbox.x + bbox.width; x++) {
            cv::Point point(x, y);
            cv::line(image, cv::Point(0, y), cv::Point(image.cols - 1, y), cv::Scalar(0, 0, 255), 1);
            cv::line(image, cv::Point(x, 0), cv::Point(x, image.rows - 1), cv::Scalar(0, 0, 255), 1);
            if (IsPointInTriangle(point)) {
                image_copy.at<cv::Vec3b>(y, x)[0] = color0_[0];
                image_copy.at<cv::Vec3b>(y, x)[1] = color0_[1];
                image_copy.at<cv::Vec3b>(y, x)[2] = color0_[2];

                image.at<cv::Vec3b>(y, x)[0] = color0_[0];
                image.at<cv::Vec3b>(y, x)[1] = color0_[1];
                image.at<cv::Vec3b>(y, x)[2] = color0_[2];
            }
            cv::waitKey(1);
            cv::imshow("image", image);
            image_copy.copyTo(image);
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

