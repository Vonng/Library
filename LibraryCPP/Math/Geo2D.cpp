#include "Geo2D.h"

#ifdef NDEBUG
#define _V_DISABLE_ALL_DEBUG_MARCO
#endif // NDEBUG



namespace Vonng
{
    namespace Geo2D
    {
        Point::Point(Point& other) :x(other.x), y(other.y)
        {
        }; 

        Point::Point(double ix, double iy) :x(ix), y(iy) {};

        double Vonng::Geo2D::Point::length(Point & other)
        {
            return sqrt((other.x - x) * (other.x - x) + (other.y - y)*(other.y - y));
        }
    }
}


#ifndef _V_DISABLE_ALL_DEBUG_MARCO
#include "..\UnitTest.h"
#include <iostream>
TEST_CASE(TestPoint)
{
    Vonng::Geo2D::Point p1(3, 4);
    Vonng::Geo2D::Point p2(0, 0);
    
    ASSERT(p1.length(p2)== 5.0);
        std::cout << "TestComplete" << std::endl;
    
}



#endif