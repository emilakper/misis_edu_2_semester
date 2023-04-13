#include <iostream>

#pragma once
#ifndef GEO2D_GEO2D_HPP_20230407
#define GEO2D_GEO2D_HPP_20230407

class Figure
{
protected:
    int width, height;
public:
    void SetWidth(int w) {
        width = w;
    }
    void SetHeight(int h) {
        height = h;
    }
    void writeTo() {
        std::cout << width << " x " << height << std::endl;
    }
};

class PolyLine : public Figure
{
    int line;
public:
    void CreateLine(int c) {
        line = c;
        width = c / 5;
        height = c * 5;
    }
};

class Point : public Figure
{
    int point;
public:
    void CreateLine(int c) {
        point = c;
    }
};

class Elipse : public Figure
{
    int elipse;
public:
    void CreateLine(int c) {
        elipse = c;
    }
};

class Segment : public PolyLine
{
    int segment;
public:
    void CreateSegment(int c) {
        segment = c;
    }
};


#endif