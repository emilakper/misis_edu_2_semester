#pragma once
#ifndef TRIRASTR_TRIRASTR_HPP_20230428
#define TRIRASTR_TRIRASTR_HPP_20230428

#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>

class TriangleRasterizer {
public:
    TriangleRasterizer() = default;
    TriangleRasterizer(const TriangleRasterizer& arr) = default;
    TriangleRasterizer& operator=(const TriangleRasterizer& rhs) = default;
    ~TriangleRasterizer() = default;
    TriangleRasterizer(TriangleRasterizer&& other) noexcept = default;
    TriangleRasterizer& operator=(TriangleRasterizer&& other) = default;

    /**
    @brief Конструктор с параметрами.

    @param v0 Первая вершина треугольника.
    @param v1 Вторая вершина треугольника.
    @param v2 Третья вершина треугольника.
    @param color0 Цвет треугольника(модель BGR, значения от 0 до 255).
    */
    TriangleRasterizer(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0);
    /**
    @brief Метод для рисования треугольника на изображении.

    @param image Изображение, на котором нужно нарисовать треугольник.
    */
    virtual void Draw(cv::Mat& image);
    /**
    @brief Метод для установки цвета в треугольнике.

    @param color0 Цвет треугольника(модель BGR, значения от 0 до 255).
    */
    virtual void setColor(cv::Scalar& color0);
    /**
    @brief Метод для установки вершин в треугольнике.

    @param v0 Первая вершина треугольника.
    @param v1 Вторая вершина треугольника.
    @param v2 Третья вершина треугольника.
    */
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
    cv::Scalar color0_{ 0, 0, 0 };/**< Цвет треугольника(модель BGR, значения от 0 до 255). */
};

class TriangleRasterizerVu : protected TriangleRasterizer {
public:
    TriangleRasterizerVu() = default;
    TriangleRasterizerVu(const TriangleRasterizerVu& arr) = default;
    TriangleRasterizerVu& operator=(const TriangleRasterizerVu& rhs) = default;
    ~TriangleRasterizerVu() = default;
    TriangleRasterizerVu(TriangleRasterizerVu&& other) noexcept = default;
    TriangleRasterizerVu& operator=(TriangleRasterizerVu&& other) = default;
    /**
    @brief Конструктор с параметрами.

    @param v0 Первая вершина треугольника.
    @param v1 Вторая вершина треугольника.
    @param v2 Третья вершина треугольника.
    @param color0 Первый цвет треугольника(модель BGR, значения от 0 до 255).
    @param color1 Второй цвет треугольника(модель BGR, значения от 0 до 255).
    @param color2 Третий цвет треугольника(модель BGR, значения от 0 до 255).
    */
    TriangleRasterizerVu(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0, cv::Scalar& color1, cv::Scalar& color2);
    /**
    @brief Метод для рисования треугольника на изображении.

    @param image Изображение, на котором нужно нарисовать треугольник.
    */
    virtual void Draw(cv::Mat& image) final;
    /**
    @brief Метод для установки трех цветов для каждой вершины треугольника.

    @param color0 Первый цвет треугольника(модель BGR, значения от 0 до 255).
    @param color1 Второй цвет треугольника(модель BGR, значения от 0 до 255).
    @param color2 Третий цвет треугольника(модель BGR, значения от 0 до 255).
    */
    virtual void setColor(cv::Scalar& color0, cv::Scalar& color1, cv::Scalar& color2) final;
private:
    /**
    @brief Метод для определения, находится ли точка в треугольнике.

    @param w0 Вес для рассматриваемой точки, относительно первой вершины.
    @param w1 Вес для рассматриваемой точки, относительно второй вершины.
    @param w2 Вес для рассматриваемой точки, относительно третьей вершины.
    @return True, если точка находится в треугольнике, иначе - false.
    */
    bool IsPointInTriangle(double& w0, double& w1, double& w2);
    /**
    @brief Метод для рассчета весов треугольника.

    @param p Рассматриваемая точка
    @param w0 Вес для рассматриваемой точки, относительно первой вершины.
    @param w1 Вес для рассматриваемой точки, относительно второй вершины.
    @param w2 Вес для рассматриваемой точки, относительно третьей вершины.
    */
    void CalculateWeights(const cv::Point& p, double& w0, double& w1, double& w2);
    /**
    @brief Интерполирует цвета трех вершин треугольника с помощью весовых коэффициентов.

    @param w0 - весовой коэффициент первой вершины треугольника
    @param w1 - весовой коэффициент второй вершины треугольника
    @param w2 - весовой коэффициент третьей вершины треугольника
    @return cv::Scalar - интерполированный цвет трех вершин треугольника
    */
    cv::Scalar InterpolateColors(double w0, double w1, double w2);
protected:
    cv::Scalar color1_{ 0, 0, 0 };/**< Второй цвет треугольника(модель BGR, значения от 0 до 255) */
    cv::Scalar color2_{ 0, 0, 0 };/**< Третий цвет треугольника(модель BGR, значения от 0 до 255) */
};


/**
      @brief Метод для отрисовки визуализационной картинки алгоритма Брезенхейма.

      @param v0 Первая вершина треугольника.
      @param v1 Вторая вершина треугольника.
      @param v2 Третья вершина треугольника.
      @param v Рассматриваемый пиксель.
    */
void demoPic(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Point& v);
/**
      @brief Метод для отрисовки визуализационной картинки алгоритма Ву.

      @param v0 Первая вершина треугольника.
      @param v1 Вторая вершина треугольника.
      @param v2 Третья вершина треугольника.
      @param v Рассматриваемый пиксель.
    */
void demoPicVu(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Point& v);

#endif