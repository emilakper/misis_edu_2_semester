#include <fstream>
#include <string>
#include <vector>

namespace geometry {
    class Figure {
    public:
        using Coordinates = std::tuple<double, double>;
    public:
        constexpr Figure() = default;
        ~Figure() = default;
        Figure(const Figure&) = default;
        Figure& operator=(const Figure&) = default;

        virtual void WriteTo(std::ofstream& ostream) const = 0;
        virtual void ReadFrom(std::istream& istream) = 0;
    };

    class Point : public Figure {
    public:
        constexpr Point() = default;
        ~Point() = default;
        Point(const Point&) = default;
        Point& operator=(const Point&) = default;

        explicit constexpr Point(const Coordinates& pt);

        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    private:
        Coordinates point_ {0.0, 0.0};
    };
    
    class Polyline : public Figure {
    public:
        constexpr Polyline() = default;
        ~Polyline() = default;
        Polyline(const Polyline&) = default;
        Polyline& operator=(const Polyline&) = default;

        Polyline(std::initializer_list<Coordinates> il);
        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    protected:
        std::vector<Coordinates> vertex_{ {0.0,0.0} };
    };
    
    
    class Elipse : public Figure {
    public:
        constexpr Elipse() = default;
        ~Elipse() = default;
        Elipse(const Elipse&) = default;
        Elipse& operator=(const Elipse&) = default;

        explicit constexpr Elipse(const Coordinates& center, const double& halfa, const double& halfb);

        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    private:
        Coordinates center_;
        double halfA_;
        double halfB_;
    };
    
    class Segment :public Figure, protected Polyline {
    public:
        constexpr Segment() = default;
        ~Segment() = default;
        Segment(const Segment&) = default;
        Segment& operator=(const Segment&) = default;

        Segment(std::initializer_list<Coordinates> il);
        void WriteTo(std::ofstream& ostream) const;
        void ReadFrom(std::istream& istream);
    private:
        std::string fill_colour{ "" };
    };
}

void geometry::Point::WriteTo(std::ofstream& ostream) const {
    ostream << "(" << std::get<0>(point_) << ", " << std::get<1>(point_) << ")" << std::endl;
}

void geometry::Point::ReadFrom(std::istream& istream){
    istream >> std::get<0>(point_);
    istream >> std::get<1>(point_);
}

constexpr geometry::Point::Point(const Coordinates& pt)
    : point_(pt)
{
}

constexpr geometry::Elipse::Elipse(const Coordinates& center, const double& halfa, const double& halfb)
    : center_(center), halfA_(halfa), halfB_(halfb)
{
}

void geometry::Elipse::WriteTo(std::ofstream& ostream) const {
    ostream << "(" << std::get<0>(center_) << ", " << std::get<1>(center_) << ")" << halfA_ << ", " << halfB_ << std::endl;
}

void geometry::Elipse::ReadFrom(std::istream& istream) {
    istream >> std::get<0>(center_);
    istream >> std::get<1>(center_);
    istream >> halfA_;
    istream >> halfB_;
}

geometry::Polyline::Polyline(std::initializer_list<Coordinates> il) {
    for (auto i : il) {
        vertex_.push_back(i);
    }
}

void geometry::Polyline::WriteTo(std::ofstream& ostream) const {
    for (size_t i = 0; i < vertex_.size(); ++i) {
        ostream << "(" << std::get<0>(vertex_[i]) << ", " << std::get<1>(vertex_[i]) << ")";
        if (i != vertex_.size() - 1) {
            ostream << " -- ";
        }
    }
}

void geometry::Polyline::ReadFrom(std::istream& istream) {
    Coordinates x;
    istream >> std::get<0>(x) >> std::get<1>(x);
    vertex_.push_back(x);
}

//����������� ������� ��� Segment
geometry::Segment::Segment(std::initializer_list<Coordinates> il) {
    for (auto i : il) {
        vertex_.push_back(i);
    }
}

void geometry::Segment::WriteTo(std::ofstream& ostream) const {
    ostream << "colourful picture ";
    for (size_t i = 0; i < vertex_.size(); ++i) {
        ostream << "(" << std::get<0>(vertex_[i]) << ", " << std::get<1>(vertex_[i]) << ")";
        if (i != vertex_.size() - 1) {
            ostream << " -- ";
        }
    }
}

void geometry::Segment::ReadFrom(std::istream& istream) {
    Coordinates x;
    istream >> std::get<0>(x) >> std::get<1>(x);
    vertex_.push_back(x);
}

namespace Style {
    class Color {
    private:
        std::string colorName = "";
        int R = 0;
        int G = 0;
        int B = 0;
        double A = 1.0;
    };

    class Width {
    public:
        void setWidth(double& num);
    private:
        double width_ = 1.0;
    };

    class Canvas : public geometry::Figure {
    private:
        Coordinates startPoint;
        Coordinates endPoint;
    };
}



