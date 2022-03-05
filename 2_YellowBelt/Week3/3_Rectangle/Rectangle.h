//
// Created by cobak on 05.03.2022.
//

#ifndef INC_3_RECTANGLE_RECTANGLE_H
#define INC_3_RECTANGLE_RECTANGLE_H


class Rectangle {
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
