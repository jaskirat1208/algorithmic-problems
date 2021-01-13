#include "circle.h"

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
