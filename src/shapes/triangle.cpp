#include <cmath>

#include "triangle.h"

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

