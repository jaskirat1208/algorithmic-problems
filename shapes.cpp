#include <iostream>
#include <memory>
#include <numeric>
#include <vector>
#include <cmath>
/**
 * @brief      Declaration for interface Shape
 */
class Shape {
    public:
        virtual int GetArea() = 0; 
};

/**
 * @brief      Rectangle class, inheriting Shape
 */
class Rectangle: public Shape {
    public:
        Rectangle(int, int);
        int GetArea();
    
    private:
        int length, width; 
};
    
/**
 * @brief      Constructor of rectangle
 *
 * @param[in]  length  The length
 * @param[in]  width   The width
 */
Rectangle::Rectangle(int length, int width) {
    this->length = length;
    this->width = width;
};

/**
 * Computes the area of the rectangle
 * Area of rectangle = length * width
 */
int Rectangle::GetArea() {
    return this->length * this->width;
};


/**
 * @brief      Circle class, inheriting Shape
 */
class Circle: public Shape {
    public:
        Circle(int);
        int GetArea();

    private:
        int radius;
};

/**
 * @brief      Constructor of circle, sets its radius
 *
 * @param[in]  radius  The radius
 */
Circle::Circle(int radius) {
    this->radius = radius;
}

/**
 * @brief      Gets the area of the circle
 * Area of circle = pi * r * r
 * @return     The area.
 */
int Circle::GetArea() {
    return round(3.14*this->radius * this-> radius);
}

/**
 * @brief      Triangle class, inheriting Shape
 */
class Triangle: public Shape {
    public:
        Triangle(int, int);
        int GetArea();
    private:
        int height, width;
};

/**
 * @brief      Initialize a triangle with its width and height
 *
 * @param[in]  height  The height
 * @param[in]  width   The width
 */
Triangle::Triangle(int height, int width) {
    this->height = height;
    this->width = width;
}

/**
 * @brief      Get the area of the triangle
 * Area of triangle = 1/2* width * height
 *
 * @return     The area.
 */
int Triangle::GetArea() {
    return round((this->height * this->width)/2);
}

/**
 * @brief      Driver program
 *
 * @return     
 */
int main() {
    int rectangleHeight = 0, rectangleWidth = 0;
    int triangleHeight = 0, triangleWidth = 0;
    int circleRadius = 0;

    std::cin >> rectangleHeight >> rectangleWidth >> triangleHeight >> triangleWidth >> circleRadius;

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Rectangle>(rectangleHeight, rectangleWidth));
    shapes.emplace_back(std::make_unique<Triangle>(triangleHeight, triangleWidth));
    shapes.emplace_back(std::make_unique<Circle>(circleRadius));

    const int totalArea = std::accumulate(shapes.begin(), shapes.end(), 0, [](int total, const auto& shape)
            { return total + shape->GetArea(); });
    std::cout << totalArea << "\n";

    return 0;
}