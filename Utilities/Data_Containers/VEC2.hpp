#ifndef __VEC2_HPP__
#define __VEC2_HPP__
class VEC2
{
    public:
        VEC2();

        double x;
        double y;

        //Overloaded operators
        VEC2 operator-(const VEC2& vector);
};
#endif//__VEC2_HPP__
