#include <cmath>

#include "shape.h"

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
