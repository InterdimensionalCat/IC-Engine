#pragma once

#include "AngularType.h"

namespace Space2D {

    class Point2;
    class Vec2;
    class NormalizedVec2;
    class Rect2;
    class AffineMatrix;
    class Dimension2;
    class Poly2;


    using Point = Point2;
    using Vec = Vec2;
    using NormalVec = NormalizedVec2;
    using Rectangle = Rect2;
    using Poly = Poly2;
    using Matrix = AffineMatrix;
    using Dimension = Dimension2;
}

//alias for Space2D
namespace s2d {
    using namespace Space2D;
}

#include "AngularType.h"
#include "AffineMatrix.h"
#include "Point2.h"
#include "Vec2.h"
#include "Dimension2.h"
#include "NormalizedVec2.h"
#include "Rect2.h"
#include "Poly2.h"

