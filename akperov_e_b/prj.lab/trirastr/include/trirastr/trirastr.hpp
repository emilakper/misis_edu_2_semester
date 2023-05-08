#pragma once
#ifndef TRIRASTR_TRIRASTR_HPP_20230428
#define TRIRASTR_TRIRASTR_HPP_20230428

#include <opencv2/opencv.hpp>
#include <vector>

class TriangleRasterizer {
public:
    TriangleRasterizer() = default;
    TriangleRasterizer(const TriangleRasterizer& arr) = default;
    TriangleRasterizer& operator=(const TriangleRasterizer& rhs) = default;
    ~TriangleRasterizer() = default;

    /**
    @brief Конструктор с параметрами.

    @param v0 Первая вершина треугольника.
    @param v1 Вторая вершина треугольника.
    @param v2 Третья вершина треугольника.
    @param color0 Цвет треугольника.
  */
    TriangleRasterizer(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0);
    /**
    @brief Метод для рисования треугольника на изображении.

    @param image Изображение, на котором нужно нарисовать треугольник.
    @return None.
    */
    virtual void Draw(cv::Mat& image);
    virtual void setColor(cv::Scalar& color0);
    void setTriangle(cv::Point& v0, cv::Point& v1, cv::Point& v2);
private:
    /**
    @brief Метод для определения, находится ли точка в треугольнике.

    @param p Точка, которую нужно проверить.
    @return True, если точка находится в треугольнике, иначе - false.
    */
    bool IsPointInTriangle(const cv::Point& p);
protected:
    cv::Point v0_{ 0, 0 };/**< Первая вершина треугольника. */
    cv::Point v1_{ 0, 0 };/**< Вторая вершина треугольника. */
    cv::Point v2_{ 0, 0 };/**< Третья вершина треугольника. */
    cv::Scalar color0_{ 0, 0, 0 };/**< Цвет треугольника */
};

class TriangleRasterizerVu : protected TriangleRasterizer {
public:
    TriangleRasterizerVu() = default;
    TriangleRasterizerVu(const TriangleRasterizerVu& arr) = default;
    TriangleRasterizerVu& operator=(const TriangleRasterizerVu& rhs) = default;
    ~TriangleRasterizerVu() = default;
    TriangleRasterizerVu(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0, cv::Scalar& color1, cv::Scalar& color2);

    virtual void Draw(cv::Mat& image) final;
    virtual void setColor(cv::Scalar& color0, cv::Scalar& color1, cv::Scalar& color2) final;
private:
    bool IsPointInTriangle(double& w0, double& w1, double& w2);
    void CalculateWeights(const cv::Point& p, double& w0, double& w1, double& w2);
    cv::Scalar InterpolateColors(double w0, double w1, double w2);
protected:
    cv::Scalar color1_{ 0, 0, 0 };
    cv::Scalar color2_{ 0, 0, 0 };
};



#endif