/*
#include <geo2d/geo2d.hpp>

int main() {
    geometry::Point pt({ 12, 3 });
    std::ofstream out;
    geometry::Elipse el({ 7, 7 }, 2, 1);
    geometry::Polyline pl({ {0, 0}, {7, 7}, {3, 12}, {12,14} });
    geometry::Segment sg({ {8, 8}, {12, 8}, {12, 12}, {8,12},{8,8} });
    Style::Canvas canvas({ 0.0,0.0 }, { 15.0,15.0 }, {&pt,&el,&pl,&sg});
    out.open("hello.tex");   
    if (out.is_open())
    {
        canvas.WriteTo(out);
    }
    out.close();
}*/