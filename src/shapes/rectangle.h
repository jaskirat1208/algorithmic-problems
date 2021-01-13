#include "shape.h"

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