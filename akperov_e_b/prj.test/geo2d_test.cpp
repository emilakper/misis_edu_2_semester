#include <geo2d/geo2d.hpp>

int main() {
    geometry::Point pt({ 5.49, 4.0 });
    std::ofstream out;
    geometry::Elipse el({ 5.5, 4.0 }, 4.0, 5.0);
    geometry::Polyline pl({ {5.5, 4.0}, {6.5, 3.0}, {4.8, 2.1} });
    geometry::Segment sg({ {5.5, 4.0}, {6.5, 3.0}, {4.8, 2.1} });
    out.open("hello.txt");   
    if (out.is_open())
    {
        sg.WriteTo(out);
    }
    out.close();
}