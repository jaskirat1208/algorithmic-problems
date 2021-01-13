#include "rectangle.h"

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

