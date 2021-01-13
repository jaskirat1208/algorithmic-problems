#include <cmath>

#include "shape.h"
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
