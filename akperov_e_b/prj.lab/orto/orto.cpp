
#include <iostream>


namespace geo2d{
  namespace orto {
    class Quad {
    public:
      Quad() = default;
      Quad(const Quad&) = default;
      ~Quad() = default;

      void Scale(double& alpha);
      void Intersect(Quad& fig);
      void Unite(Quad& fig);

      // Поля для координат центра фигуры
    public:
        double x_center_{0.0};
        double y_center_{0.0};
        double height_{0.0};
        double width_{ 0.0 };
    };

    class Rect : public Quad {
    public:
      Rect() = default;
      Rect(const Rect&) = default;
      ~Rect() = default;

      Rect(double& x0, double& y0, double& height, double& width) {
        x_center_ = x0;
        y_center_ = y0;
        height_ = height;
        width_ = width;
      };
    };

    class Square : public Quad {
    public:
      Square() = default;
      Square(const Square&) = default;
      ~Square() = default;

      Square(const double& x0, const double& y0, const double& height) {
        x_center_ = x0;
        y_center_ = y0;
        height_ = height;
        width_ = height;
      }
    };

    void Quad::Scale(double& alpha) {
      height_ *= alpha;
      width_ *= alpha;
    }

    void Quad::Intersect(Quad& fig) {
        double left1 = x_center_ - width_ / 2.0;
        double right1 = x_center_ + width_ / 2.0;
        double top1 = y_center_ - height_ / 2.0;
        double bottom1 = y_center_ + height_ / 2.0;

        double left2 = fig.x_center_ - fig.width_ / 2.0;
        double right2 = fig.x_center_ + fig.width_ / 2.0;
        double top2 = fig.y_center_ - fig.height_ / 2.0;
        double bottom2 = fig.y_center_ + fig.height_ / 2.0;

        double left = std::max(left1, left2);
        double right = std::min(right1, right2);

        double top = std::max(top1, top2);
        double bottom = std::min(bottom1, bottom2);

        if (left < right && top < bottom) {
            x_center_ = (left + right) / 2.0;
            y_center_ = (top + bottom) / 2.0;
            width_ = right - left;
            height_ = bottom - top;
        }
        else {
            x_center_ = 0.0;
            y_center_ = 0.0;
            width_ = 0.0;
            height_ = 0.0;
        }
    }

    void Quad::Unite(Quad& fig) {
        double left1 = x_center_ - width_ / 2.0;
        double right1 = x_center_ + width_ / 2.0;
        double top1 = y_center_ - height_ / 2.0;
        double bottom1 = y_center_ + height_ / 2.0;

        double left2 = fig.x_center_ - fig.width_ / 2.0;
        double right2 = fig.x_center_ + fig.width_ / 2.0;
        double top2 = fig.y_center_ - fig.height_ / 2.0;
        double bottom2 = fig.y_center_ + fig.height_ / 2.0;

        double left = std::min(left1, left2);
        double right = std::max(right1, right2);

        double top = std::min(top1, top2);
        double bottom = std::max(bottom1, bottom2);

        double x_center = (left + right) / 2.0;
        double y_center = (top + bottom) / 2.0;
        double width = right - left;
        double height = bottom - top;

        x_center_ = x_center;
        y_center_ = y_center;
        width_ = width;
        height_ = height;
    }
  }
}

int main()
{
	double x0 = 5.0;
	double y0 = 5.0;
	double height = 2.0;
	double width = 3.0;
	//Constructors
	geo2d::orto::Rect rectan1(x0,y0,height,width);
	geo2d::orto::Square square1(x0, y0, height);
	std::cout << rectan1.x_center_ << " " <<  rectan1.y_center_ << " " << rectan1.height_ << " " << rectan1.width_ << std::endl;
	std::cout << square1.x_center_ << " " << square1.y_center_ << " " << square1.height_  << " "<< square1.width_ << std::endl;
	std::cout << std::endl;
	//Constructor copy
	geo2d::orto::Rect rectan2(rectan1);
	geo2d::orto::Square square2(square1);
	std::cout << rectan2.x_center_ << " " << rectan2.y_center_ << " " << rectan2.height_ << " " << rectan2.width_ << std::endl;
	std::cout << square2.x_center_ << " " << square2.y_center_ << " " << square2.height_ << " " << square2.width_ << std::endl;
	std::cout << std::endl;
	//Scale
	double alpha = 3.0;
	rectan1.Scale(alpha);
	square1.Scale(alpha);
	std::cout << rectan1.x_center_ << " " << rectan1.y_center_ << " " << rectan1.height_ << " " << rectan1.width_ << std::endl;
	std::cout << square1.x_center_ << " " << square1.y_center_ << " " << square1.height_ << " " << square1.width_ << std::endl;
    std::cout << std::endl;
	//Intersect
    rectan1.Intersect(rectan2);
    std::cout << rectan1.x_center_ << " " << rectan1.y_center_ << " " << rectan1.height_ << " " << rectan1.width_ << std::endl;
    std::cout << std::endl;
    //Unite
    geo2d::orto::Square square3(7.0, 7.0, 8.0);
    square1.Unite(square3);
    std::cout << square1.x_center_ << " " << square1.y_center_ << " " << square1.height_ << " " << square1.width_ << std::endl;
}
