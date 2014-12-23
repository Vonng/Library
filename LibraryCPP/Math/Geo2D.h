/****************************** Module Header ******************************\
Filename:		V_Geo2D.h
Project:		Vonng::Geo2D
Digest:			Basic 2D geometry element definition
Author:			Feng Ruohang
Create:			2014/11/18 22:36
LastModify:		2014/11/18 22:36
\****************************** Module Header ******************************/

#ifndef _V_GEO2D
#define _V_GEO2D

#ifdef NDEBUG
#define _V_DISABLE_ALL_DEBUG_MARCO
#endif

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include<cmath>
#include<vector>
#include"..\Basic.h"

namespace Vonng
{
    namespace Geo2D
    {
        struct Matrix;

        struct Point;
        struct Vector;

        struct Line;
        struct Segment;
        struct Beam;
        struct Zig;

        struct Sphere;
        struct AABB;
        struct Triangle;
        struct Polygon;

        struct Matrix
        {
            double m11, m12, m13, m21, m22, m23, m31, m32, m33;

            Matrix(Matrix& other);
            Matrix(double[9]);
            Matrix(double[3][3]);
            Matrix(double theta);
            Matrix(double dx, double dy);
            Matrix(double x11, double x12, double x13, double x21, double x22, double x23, double x31, double x32, double x33);
        };

        struct Point
        {
            double x;
            double y;

            Point(Point& other);
            Point(double ix = 0.0, double iy = 0.0);
            Point(Point& s, Vector& d);

            double length(Point& other);
        };

        struct Vector
        {
            double x;
            double y;
        };

        struct Line
        {
            Point s;
            Vector u;
        };

        struct Segment
        {
            Point s;
            Point e;
        };

        struct Beam
        {
            Point s;
            Vector u;

            Beam(Beam& other);
            Beam(Line& other, Point& start, bool cocurrent = true);
            Beam(Point& start, Vector& direction);
            Beam(double x, double y, double dx, double dy);
        };

        struct Sphere
        {
            Point O;
            double radius;

            Sphere(Sphere& other);
            Sphere(Point& center, double iradius);
            Sphere(double ox, double oy, double iradius);
        };

        //Axially Aligned Bounding Box
        struct AABB
        {
            Point pmin;
            Point pmax;

            AABB(AABB& other);
            AABB(Point& ipmin, Point& ipmax);
            AABB(double left, double right, double bottom, double up);
        };

        struct Triangle
        {
            Point a;
            Point b;
            Point c;

            Triangle(Triangle& other);
            Triangle(Point& ia, Point& ib, Point& ic);
            Triangle(double ax, double ay, double bx, double by, double cx, double cy);
        };

        struct Polygon
        {
            vint cnt;
        };
    }
}

#endif