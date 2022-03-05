#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

const double pi = 3.14;

class Figure {
public:
    virtual std::string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure{
public:
    Triangle(const double& a_, const double& b_, const double& c_) : a(a_), b(b_), c(c_) {}
    std::string Name() const override;
    double Perimeter() const override;
    double Area() const override;

private:
    double b;
    double a;
    double c;
};

class Rect : public Figure{
public:
    Rect(const double& width_, const double& height_) : width(width_), height(height_) {}
    std::string Name() const override;
    double Perimeter() const override;
    double Area() const override;
private:
    double width;
    double height;
};

class Circle : public Figure{
public:
    explicit Circle(const double& radius_) : radius(radius_) {}
    std::string Name() const override;
    double Perimeter() const override;
    double Area() const override;
private:
    double radius;
};

shared_ptr<Figure> CreateFigure(std::istream & is){
    std::string name;
    getline(is, name, ' ');
    if(name == "TRIANGLE"){
        double a, b, c;
        is >> a >> b >> c;
        return make_shared<Triangle>(a, b, c);
    } else if(name == "RECT"){
        double width, height;
        is >> width >> height;
        return make_shared<Rect>(width, height);
    } else if(name == "CIRCLE"){
        double radius;
        is >> radius;
        return make_shared<Circle>(radius);
    } else throw invalid_argument("Invalid request: " + name);
}

int main() {
    vector<shared_ptr<Figure>> figures;
    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "ADD") {
            is >> ws;
            figures.push_back(CreateFigure(is));
        } else if (command == "PRINT") {
            for (const auto& current_figure : figures) {
                cout << fixed << setprecision(3)
                     << current_figure->Name() << " "
                     << current_figure->Perimeter() << " "
                     << current_figure->Area() << endl;
            }
        }
    }
    return 0;
}

std::string Triangle::Name() const {return "TRIANGLE";}
std::string Rect::Name() const {return "RECT";}
std::string Circle::Name() const {return "CIRCLE";}

double Triangle::Perimeter() const {return (a + b + c);}
double Rect::Perimeter() const {return (2 * width + 2 * height);}
double Circle::Perimeter() const {return (2 * pi * radius);}

double Triangle::Area() const {
    double p = Perimeter() / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}

double Rect::Area() const {return width * height;}
double Circle::Area() const {return pi * radius * radius;}

