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
    @brief ����������� � �����������.

    @param v0 ������ ������� ������������.
    @param v1 ������ ������� ������������.
    @param v2 ������ ������� ������������.
    @param color0 ���� ������������.
  */
    TriangleRasterizer(cv::Point& v0, cv::Point& v1, cv::Point& v2, cv::Scalar& color0);
    /**
    @brief ����� ��� ��������� ������������ �� �����������.

    @param image �����������, �� ������� ����� ���������� �����������.
    @return None.
    */
    virtual void Draw(cv::Mat& image);
    virtual void setColor(cv::Scalar& color0);
    void setTriangle(cv::Point& v0, cv::Point& v1, cv::Point& v2);
private:
    /**
    @brief ����� ��� �����������, ��������� �� ����� � ������������.

    @param p �����, ������� ����� ���������.
    @return True, ���� ����� ��������� � ������������, ����� - false.
    */
    bool IsPointInTriangle(const cv::Point& p);
protected:
    cv::Point v0_{ 0, 0 };/**< ������ ������� ������������. */
    cv::Point v1_{ 0, 0 };/**< ������ ������� ������������. */
    cv::Point v2_{ 0, 0 };/**< ������ ������� ������������. */
    cv::Scalar color0_{ 0, 0, 0 };/**< ���� ������������ */
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