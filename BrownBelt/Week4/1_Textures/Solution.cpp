#include "Common.h"

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

class Shape : public IShape{
public:

    explicit Shape(Point p, Size s, std::shared_ptr<ITexture> t) : position(p), size(s), texture(t) {}

    void SetPosition(Point p) override{
        position = p;
    }

    Point GetPosition() const override{
        return position;
    }

    void SetSize(Size s) override{
        size = s;
    }

    Size GetSize() const override{
        return size;
    }

    void SetTexture(std::shared_ptr<ITexture> t) override{
        texture = std::move(t);
    }

    ITexture * GetTexture() const override{
        return texture.get();
    }

    /*std::unique_ptr<IShape> Clone() const override{
        return std::make_unique<Shape>(position, size, texture);
    }*/
    std::unique_ptr<IShape> Clone() const override = 0;

    void Draw(Image &img) const final{
        for(int i = 0; i < size.height; ++i){
            for(int j = 0; j < size.width; ++j){
                char pixel = '.';
                if(texture && IsPointInTexture(Point{i, j})){
                    pixel = texture->GetImage()[i][j];
                }
                Point p;
                p = {position.x + i, position.y + j};
                if(){

                }
            }
        }
    }

protected:
    bool IsPointInTexture(Point p) const{
        return p.x < texture->GetSize().width && p.y < texture->GetSize().height;
    }

    Point position;
    Size size;
    std::shared_ptr<ITexture> texture;
};

class Rectangle : public Shape {
public:
    void Draw(Image &img) const final{
        for(int i = 0; i < size.height; ++i){
            for(int j = 0; j < size.width; ++j){
                char pixel = '.';
                if(texture && IsPointInTexture(Point{i, j})){
                    pixel = texture->GetImage()[i][j];
                }
                Point p;
                p = {position.x + i, position.y + j};
                if()
            }
        }
    }

private:

};

class Ellipse : public Shape {
public:
    void Draw(Image &im) const final{
        for(int i = 0; i < size.height; ++i){

        }
    }

private:

};


// Напишите реализацию функции
unique_ptr<IShape> MakeShape(ShapeType shape_type) {

}