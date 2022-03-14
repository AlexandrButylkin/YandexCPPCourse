#ifndef INC_3_RECTANGLE_RECTANGLE_H
#define INC_3_RECTANGLE_RECTANGLE_H

#include <stdexcept>

class Rectangle final {
public:
    Rectangle(int width, int height);

    int GetArea() const;
    int GetPerimeter() const;

    int GetWidth() const;
    int GetHeight() const;

private:
    int width_, height_;
};


#endif //INC_3_RECTANGLE_RECTANGLE_H
